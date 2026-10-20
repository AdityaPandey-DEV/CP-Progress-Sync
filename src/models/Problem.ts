import mongoose, { Schema, Document, Model } from 'mongoose';
import { Problem as IProblem } from '@/types';

export interface IProblemDocument extends Document, Omit<IProblem, 'id'> {
  id: number;
}

const SolutionSchema = new Schema({
  filename: { type: String, default: '' },
  lang: { type: String, default: 'cpp' },
  code: { type: String, required: true },
}, { _id: false });

const AIExplanationSchema = new Schema({
  intuition: { type: String, default: '' },
  eli5: { type: String, default: '' },
  algorithmSteps: { type: [String], default: [] },
  timeComplexity: { type: String, default: '' },
  spaceComplexity: { type: String, default: '' },
  hints: { type: [String], default: [] },
  pitfalls: { type: [String], default: [] },
  codeWalkthrough: { type: String, default: '' },
  generatedBy: { type: String, enum: ['gemini', 'groq', 'seed', 'custom'], default: 'seed' },
  generatedAt: { type: Date, default: Date.now },
  model: { type: String, default: '' },
}, { _id: false });

const ProblemSchema = new Schema<IProblemDocument>({
  id: { type: Number, required: true, index: true },
  problemId: { type: String, unique: true, sparse: true, index: true },
  title: { type: String, required: true, index: true },
  slug: { type: String, required: true, index: true },
  platform: { type: String, enum: ['LeetCode', 'Codeforces', 'GFG', 'Other'], default: 'LeetCode', index: true },
  difficulty: { type: String, enum: ['Easy', 'Medium', 'Hard'], default: 'Medium', index: true },
  topic: { type: String, default: 'General', index: true },
  pattern: { type: String, default: 'General', index: true },
  url: { type: String, default: '' },
  description: { type: String, default: '' },
  solutions: { type: [SolutionSchema], default: [] },
  aiExplanation: { type: AIExplanationSchema, default: null },
  revisionStatus: { type: String, enum: ['unrevised', 'reviewing', 'mastered'], default: 'unrevised', index: true },
  isBookmarked: { type: Boolean, default: false, index: true },
  personalNotes: { type: String, default: '' },
  lastReviewedAt: { type: Date, default: null },
}, {
  timestamps: true,
});

ProblemSchema.index({ topic: 1, pattern: 1 });
ProblemSchema.index({ difficulty: 1, platform: 1 });

export const ProblemModel: Model<IProblemDocument> =
  (mongoose.models.Problem as Model<IProblemDocument>) ||
  mongoose.model<IProblemDocument>('Problem', ProblemSchema);
