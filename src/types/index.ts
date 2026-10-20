export interface ProblemSolution {
  filename: string;
  lang: string;
  code: string;
}

export interface AIExplanation {
  intuition: string;
  eli5: string;
  algorithmSteps: string[];
  timeComplexity: string;
  spaceComplexity: string;
  hints: string[];
  pitfalls: string[];
  codeWalkthrough?: string;
  generatedBy?: 'gemini' | 'groq' | 'seed';
  generatedAt?: string;
  model?: string;
}

export interface Problem {
  id: number | string;
  problemId?: string;
  title: string;
  slug: string;
  platform: 'LeetCode' | 'Codeforces' | string;
  difficulty: 'Easy' | 'Medium' | 'Hard' | string;
  topic: string;
  pattern: string;
  url: string;
  description: string;
  solutions: ProblemSolution[];
  aiExplanation?: AIExplanation;
  revisionStatus?: 'unrevised' | 'reviewing' | 'mastered';
  isBookmarked?: boolean;
  personalNotes?: string;
  lastReviewedAt?: string;
}

export interface FilterOptions {
  search?: string;
  topic?: string;
  pattern?: string;
  difficulty?: string;
  platform?: string;
  status?: string;
  sortBy?: 'id' | 'difficulty' | 'title';
  sortOrder?: 'asc' | 'desc';
}

export interface RevisionStats {
  total: number;
  mastered: number;
  reviewing: number;
  unrevised: number;
  starred: number;
  byDifficulty: {
    Easy: number;
    Medium: number;
    Hard: number;
  };
  byPlatform: {
    LeetCode: number;
    Codeforces: number;
  };
}

export interface AIProviderConfig {
  provider: 'gemini' | 'groq';
  geminiApiKey?: string;
  groqApiKey?: string;
  geminiModel?: string;
  groqModel?: string;
}
