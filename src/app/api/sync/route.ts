import { NextResponse } from 'next/server';
import { connectToDatabase } from '@/lib/mongodb';
import { ProblemModel } from '@/models/Problem';
import seedProblemsRaw from '@/data/problems.json';

export async function POST() {
  try {
    const mongooseConn = await connectToDatabase();
    if (!mongooseConn) {
      return NextResponse.json(
        { error: 'MongoDB URI is not configured in environment (MONGODB_URI)' },
        { status: 400 }
      );
    }

    const items = seedProblemsRaw as unknown[];
    let inserted = 0;
    let updated = 0;

    for (let index = 0; index < items.length; index++) {
      const item = items[index] as Record<string, unknown>;
      const slug = String(item.slug || `problem-${index + 1}`);
      const platform = String(item.platform || 'LeetCode');
      const idNum = typeof item.id === 'number' ? item.id : index + 1;
      const problemId = String(item.problemId || `${platform.toLowerCase()}-${slug}`);

      const res = await ProblemModel.updateOne(
        { problemId },
        {
          $setOnInsert: {
            id: idNum,
            problemId,
            title: String(item.title || slug),
            slug,
            platform,
            difficulty: String(item.difficulty || 'Medium'),
            topic: String(item.topic || 'General'),
            pattern: String(item.pattern || 'General'),
            url: String(item.url || ''),
            description: String(item.description || ''),
            solutions: item.solutions || [],
            aiExplanation: item.aiExplanation || null,
            revisionStatus: 'unrevised',
            isBookmarked: false,
            personalNotes: '',
          },
        },
        { upsert: true }
      );

      if (res.upsertedCount > 0) inserted++;
      else if (res.modifiedCount > 0) updated++;
    }

    const totalInDb = await ProblemModel.countDocuments();

    return NextResponse.json({
      success: true,
      message: `MongoDB synced successfully: ${inserted} inserted, ${updated} updated. Total in DB: ${totalInDb}`,
      totalInDb,
    });
  } catch (error) {
    console.error('API Error in /api/sync:', error);
    return NextResponse.json(
      { error: 'Failed to sync with MongoDB', details: (error as Error).message },
      { status: 500 }
    );
  }
}
