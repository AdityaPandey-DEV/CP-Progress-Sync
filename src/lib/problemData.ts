import { Problem, FilterOptions, RevisionStats } from '@/types';
import seedProblemsRaw from '@/data/problems.json';
import { connectToDatabase } from '@/lib/mongodb';
import { ProblemModel } from '@/models/Problem';

const seedProblems: Problem[] = (seedProblemsRaw as unknown[]).map((p, index) => {
  const item = p as Record<string, unknown>;
  const slug = String(item.slug || `problem-${index + 1}`);
  const platform = String(item.platform || 'LeetCode');
  const idNum = typeof item.id === 'number' ? item.id : index + 1;
  const problemId = String(item.problemId || `${platform.toLowerCase()}-${slug}`);

  return {
    id: idNum,
    problemId,
    title: String(item.title || slug),
    slug,
    platform: platform as 'LeetCode' | 'Codeforces',
    difficulty: String(item.difficulty || 'Medium') as 'Easy' | 'Medium' | 'Hard',
    topic: String(item.topic || 'General'),
    pattern: String(item.pattern || 'General'),
    url: String(item.url || ''),
    description: String(item.description || ''),
    solutions: Array.isArray(item.solutions) ? (item.solutions as Problem['solutions']) : [],
    aiExplanation: item.aiExplanation as Problem['aiExplanation'] || undefined,
    revisionStatus: (item.revisionStatus as Problem['revisionStatus']) || 'unrevised',
    isBookmarked: Boolean(item.isBookmarked),
    personalNotes: String(item.personalNotes || ''),
    lastReviewedAt: item.lastReviewedAt ? String(item.lastReviewedAt) : undefined,
  };
});

let isSeeding = false;

async function ensureMongoSeeded() {
  if (isSeeding) return;
  try {
    const mongooseConn = await connectToDatabase();
    if (!mongooseConn) return;

    const count = await ProblemModel.countDocuments();
    if (count === 0) {
      isSeeding = true;
      console.log('Seeding MongoDB with seed problems...');
      const docs = seedProblems.map(p => ({
        id: p.id,
        problemId: p.problemId,
        title: p.title,
        slug: p.slug,
        platform: p.platform,
        difficulty: p.difficulty,
        topic: p.topic,
        pattern: p.pattern,
        url: p.url,
        description: p.description,
        solutions: p.solutions,
        aiExplanation: p.aiExplanation || null,
        revisionStatus: p.revisionStatus || 'unrevised',
        isBookmarked: p.isBookmarked || false,
        personalNotes: p.personalNotes || '',
      }));
      await ProblemModel.insertMany(docs, { ordered: false }).catch(() => {});
      console.log(`Seeded MongoDB with ${docs.length} problems.`);
      isSeeding = false;
    }
  } catch (err) {
    isSeeding = false;
    console.warn('MongoDB seed warning:', err);
  }
}

export async function getProblems(filter: FilterOptions = {}, page = 1, limit = 20): Promise<{
  problems: Problem[];
  total: number;
  page: number;
  totalPages: number;
  isFromDb: boolean;
}> {
  try {
    const mongooseConn = await connectToDatabase();
    if (mongooseConn) {
      await ensureMongoSeeded();

      // Build MongoDB query
      // eslint-disable-next-line @typescript-eslint/no-explicit-any
      const query: any = {};

      if (filter.search) {
        const regex = new RegExp(filter.search, 'i');
        query.$or = [
          { title: regex },
          { slug: regex },
          { topic: regex },
          { pattern: regex },
        ];
      }

      if (filter.topic && filter.topic !== 'all') {
        query.topic = filter.topic;
      }

      if (filter.pattern && filter.pattern !== 'all') {
        query.pattern = filter.pattern;
      }

      if (filter.difficulty && filter.difficulty !== 'all') {
        query.difficulty = filter.difficulty;
      }

      if (filter.platform && filter.platform !== 'all') {
        query.platform = filter.platform;
      }

      if (filter.status && filter.status !== 'all') {
        if (filter.status === 'starred') {
          query.isBookmarked = true;
        } else {
          query.revisionStatus = filter.status;
        }
      }

      const total = await ProblemModel.countDocuments(query);
      const skip = (page - 1) * limit;

      const docs = await ProblemModel.find(query)
        .sort({ id: 1 })
        .skip(skip)
        .limit(limit)
        .lean();

      const problems: Problem[] = docs.map((doc) => ({
        id: doc.id,
        problemId: doc.problemId || `${doc.platform?.toLowerCase()}-${doc.slug}`,
        title: doc.title,
        slug: doc.slug,
        platform: doc.platform as Problem['platform'],
        difficulty: doc.difficulty as Problem['difficulty'],
        topic: doc.topic,
        pattern: doc.pattern,
        url: doc.url,
        description: doc.description,
        solutions: doc.solutions || [],
        aiExplanation: doc.aiExplanation || undefined,
        revisionStatus: doc.revisionStatus || 'unrevised',
        isBookmarked: Boolean(doc.isBookmarked),
        personalNotes: doc.personalNotes || '',
        lastReviewedAt: doc.lastReviewedAt ? new Date(doc.lastReviewedAt).toISOString() : undefined,
      }));

      return {
        problems,
        total,
        page,
        totalPages: Math.ceil(total / limit) || 1,
        isFromDb: true,
      };
    }
  } catch (err) {
    console.warn('Error reading from MongoDB, falling back to local dataset:', err);
  }

  // Local In-Memory Fallback
  let filtered = [...seedProblems];

  if (filter.search) {
    const q = filter.search.toLowerCase();
    filtered = filtered.filter(p =>
      p.title.toLowerCase().includes(q) ||
      p.slug.toLowerCase().includes(q) ||
      p.topic.toLowerCase().includes(q) ||
      p.pattern.toLowerCase().includes(q)
    );
  }

  if (filter.topic && filter.topic !== 'all') {
    filtered = filtered.filter(p => p.topic.toLowerCase() === filter.topic?.toLowerCase());
  }

  if (filter.pattern && filter.pattern !== 'all') {
    filtered = filtered.filter(p => p.pattern.toLowerCase() === filter.pattern?.toLowerCase());
  }

  if (filter.difficulty && filter.difficulty !== 'all') {
    filtered = filtered.filter(p => p.difficulty.toLowerCase() === filter.difficulty?.toLowerCase());
  }

  if (filter.platform && filter.platform !== 'all') {
    filtered = filtered.filter(p => p.platform.toLowerCase() === filter.platform?.toLowerCase());
  }

  if (filter.status && filter.status !== 'all') {
    if (filter.status === 'starred') {
      filtered = filtered.filter(p => p.isBookmarked);
    } else {
      filtered = filtered.filter(p => p.revisionStatus === filter.status);
    }
  }

  const total = filtered.length;
  const skip = (page - 1) * limit;
  const problems = filtered.slice(skip, skip + limit);

  return {
    problems,
    total,
    page,
    totalPages: Math.ceil(total / limit) || 1,
    isFromDb: false,
  };
}

export async function getProblemByIdOrSlug(idOrSlug: string): Promise<Problem | null> {
  try {
    const mongooseConn = await connectToDatabase();
    if (mongooseConn) {
      const isNum = !isNaN(Number(idOrSlug));
      // eslint-disable-next-line @typescript-eslint/no-explicit-any
      const query: any = isNum
        ? { $or: [{ id: Number(idOrSlug) }, { slug: idOrSlug }, { problemId: idOrSlug }] }
        : { $or: [{ slug: idOrSlug }, { problemId: idOrSlug }] };

      const doc = await ProblemModel.findOne(query).lean();
      if (doc) {
        return {
          id: doc.id,
          problemId: doc.problemId || `${doc.platform?.toLowerCase()}-${doc.slug}`,
          title: doc.title,
          slug: doc.slug,
          platform: doc.platform as Problem['platform'],
          difficulty: doc.difficulty as Problem['difficulty'],
          topic: doc.topic,
          pattern: doc.pattern,
          url: doc.url,
          description: doc.description,
          solutions: doc.solutions || [],
          aiExplanation: doc.aiExplanation || undefined,
          revisionStatus: doc.revisionStatus || 'unrevised',
          isBookmarked: Boolean(doc.isBookmarked),
          personalNotes: doc.personalNotes || '',
          lastReviewedAt: doc.lastReviewedAt ? new Date(doc.lastReviewedAt).toISOString() : undefined,
        };
      }
    }
  } catch (err) {
    console.warn('MongoDB single fetch fallback:', err);
  }

  // Fallback to local
  const isNum = !isNaN(Number(idOrSlug));
  return seedProblems.find(p =>
    (isNum && p.id === Number(idOrSlug)) ||
    p.slug === idOrSlug ||
    p.problemId === idOrSlug
  ) || null;
}

export async function updateProblemRevision(
  idOrSlug: string,
  updates: Partial<Pick<Problem, 'revisionStatus' | 'isBookmarked' | 'personalNotes' | 'aiExplanation'>>
): Promise<Problem | null> {
  const isNum = !isNaN(Number(idOrSlug));
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  const query: any = isNum
    ? { $or: [{ id: Number(idOrSlug) }, { slug: idOrSlug }, { problemId: idOrSlug }] }
    : { $or: [{ slug: idOrSlug }, { problemId: idOrSlug }] };

  try {
    const mongooseConn = await connectToDatabase();
    if (mongooseConn) {
      const doc = await ProblemModel.findOneAndUpdate(
        query,
        {
          ...updates,
          lastReviewedAt: updates.revisionStatus ? new Date() : undefined,
        },
        { new: true }
      ).lean();

      if (doc) {
        return {
          id: doc.id,
          problemId: doc.problemId,
          title: doc.title,
          slug: doc.slug,
          platform: doc.platform as Problem['platform'],
          difficulty: doc.difficulty as Problem['difficulty'],
          topic: doc.topic,
          pattern: doc.pattern,
          url: doc.url,
          description: doc.description,
          solutions: doc.solutions || [],
          aiExplanation: doc.aiExplanation || undefined,
          revisionStatus: doc.revisionStatus || 'unrevised',
          isBookmarked: Boolean(doc.isBookmarked),
          personalNotes: doc.personalNotes || '',
          lastReviewedAt: doc.lastReviewedAt ? new Date(doc.lastReviewedAt).toISOString() : undefined,
        };
      }
    }
  } catch (err) {
    console.warn('MongoDB update fallback:', err);
  }

  // Local update in memory
  const problem = seedProblems.find(p =>
    (isNum && p.id === Number(idOrSlug)) ||
    p.slug === idOrSlug ||
    p.problemId === idOrSlug
  );

  if (problem) {
    if (updates.revisionStatus !== undefined) problem.revisionStatus = updates.revisionStatus;
    if (updates.isBookmarked !== undefined) problem.isBookmarked = updates.isBookmarked;
    if (updates.personalNotes !== undefined) problem.personalNotes = updates.personalNotes;
    if (updates.aiExplanation !== undefined) problem.aiExplanation = updates.aiExplanation;
    problem.lastReviewedAt = new Date().toISOString();
    return problem;
  }

  return null;
}

export async function getTopicsAndPatterns(): Promise<{
  topics: { name: string; count: number }[];
  patterns: { name: string; count: number }[];
  platforms: { name: string; count: number }[];
  difficulties: { name: string; count: number }[];
}> {
  const topicCounts: Record<string, number> = {};
  const patternCounts: Record<string, number> = {};
  const platformCounts: Record<string, number> = {};
  const difficultyCounts: Record<string, number> = {};

  try {
    const mongooseConn = await connectToDatabase();
    if (mongooseConn) {
      const [topicAgg, patternAgg] = await Promise.all([
        ProblemModel.aggregate([{ $group: { _id: '$topic', count: { $sum: 1 } } }]),
        ProblemModel.aggregate([{ $group: { _id: '$pattern', count: { $sum: 1 } } }]),
      ]);

      if (topicAgg.length > 0) {
        return {
          topics: topicAgg.map(t => ({ name: t._id || 'General', count: t.count })).sort((a, b) => b.count - a.count),
          patterns: patternAgg.map(p => ({ name: p._id || 'General', count: p.count })).sort((a, b) => b.count - a.count),
          platforms: [
            { name: 'LeetCode', count: seedProblems.filter(p => p.platform === 'LeetCode').length },
            { name: 'Codeforces', count: seedProblems.filter(p => p.platform === 'Codeforces').length },
          ],
          difficulties: [
            { name: 'Easy', count: seedProblems.filter(p => p.difficulty === 'Easy').length },
            { name: 'Medium', count: seedProblems.filter(p => p.difficulty === 'Medium').length },
            { name: 'Hard', count: seedProblems.filter(p => p.difficulty === 'Hard').length },
          ],
        };
      }
    }
  } catch (err) {
    console.warn('MongoDB aggregate fallback:', err);
  }

  // Count from local
  seedProblems.forEach(p => {
    topicCounts[p.topic] = (topicCounts[p.topic] || 0) + 1;
    patternCounts[p.pattern] = (patternCounts[p.pattern] || 0) + 1;
    platformCounts[p.platform] = (platformCounts[p.platform] || 0) + 1;
    difficultyCounts[p.difficulty] = (difficultyCounts[p.difficulty] || 0) + 1;
  });

  return {
    topics: Object.entries(topicCounts).map(([name, count]) => ({ name, count })).sort((a, b) => b.count - a.count),
    patterns: Object.entries(patternCounts).map(([name, count]) => ({ name, count })).sort((a, b) => b.count - a.count),
    platforms: Object.entries(platformCounts).map(([name, count]) => ({ name, count })).sort((a, b) => b.count - a.count),
    difficulties: ['Easy', 'Medium', 'Hard'].map(d => ({ name: d, count: difficultyCounts[d] || 0 })),
  };
}

export async function getRevisionStats(): Promise<RevisionStats> {
  try {
    const mongooseConn = await connectToDatabase();
    if (mongooseConn) {
      const [total, mastered, reviewing, starred] = await Promise.all([
        ProblemModel.countDocuments(),
        ProblemModel.countDocuments({ revisionStatus: 'mastered' }),
        ProblemModel.countDocuments({ revisionStatus: 'reviewing' }),
        ProblemModel.countDocuments({ isBookmarked: true }),
      ]);

      const [easy, med, hard] = await Promise.all([
        ProblemModel.countDocuments({ difficulty: 'Easy' }),
        ProblemModel.countDocuments({ difficulty: 'Medium' }),
        ProblemModel.countDocuments({ difficulty: 'Hard' }),
      ]);

      const [lc, cf] = await Promise.all([
        ProblemModel.countDocuments({ platform: 'LeetCode' }),
        ProblemModel.countDocuments({ platform: 'Codeforces' }),
      ]);

      return {
        total,
        mastered,
        reviewing,
        unrevised: Math.max(0, total - (mastered + reviewing)),
        starred,
        byDifficulty: { Easy: easy, Medium: med, Hard: hard },
        byPlatform: { LeetCode: lc, Codeforces: cf },
      };
    }
  } catch (err) {
    console.warn('MongoDB stats fallback:', err);
  }

  const total = seedProblems.length;
  const mastered = seedProblems.filter(p => p.revisionStatus === 'mastered').length;
  const reviewing = seedProblems.filter(p => p.revisionStatus === 'reviewing').length;
  const starred = seedProblems.filter(p => p.isBookmarked).length;

  return {
    total,
    mastered,
    reviewing,
    unrevised: total - (mastered + reviewing),
    starred,
    byDifficulty: {
      Easy: seedProblems.filter(p => p.difficulty === 'Easy').length,
      Medium: seedProblems.filter(p => p.difficulty === 'Medium').length,
      Hard: seedProblems.filter(p => p.difficulty === 'Hard').length,
    },
    byPlatform: {
      LeetCode: seedProblems.filter(p => p.platform === 'LeetCode').length,
      Codeforces: seedProblems.filter(p => p.platform === 'Codeforces').length,
    },
  };
}
