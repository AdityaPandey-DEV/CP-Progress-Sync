import { NextRequest, NextResponse } from 'next/server';
import { getProblemByIdOrSlug, updateProblemRevision } from '@/lib/problemData';
import { generateAIExplanation } from '@/lib/aiService';

export async function POST(request: NextRequest) {
  try {
    const body = await request.json();
    const {
      problemId,
      provider = 'gemini',
      model,
      forceRegenerate = false,
      userApiKey,
      customPrompt,
    } = body;

    if (!problemId) {
      return NextResponse.json({ error: 'problemId is required' }, { status: 400 });
    }

    const problem = await getProblemByIdOrSlug(String(problemId));
    if (!problem) {
      return NextResponse.json({ error: 'Problem not found' }, { status: 404 });
    }

    // 1. Check if explanation already exists and forceRegenerate is not requested
    if (!forceRegenerate && problem.aiExplanation && problem.aiExplanation.intuition) {
      return NextResponse.json({
        success: true,
        cached: true,
        explanation: problem.aiExplanation,
        source: 'database-cache',
      });
    }

    // 2. Generate with Gemini or Groq
    const explanation = await generateAIExplanation({
      problem,
      provider,
      apiKey: userApiKey,
      model,
      customPrompt,
    });

    // 3. Cache/Save in MongoDB database
    await updateProblemRevision(String(problemId), {
      aiExplanation: explanation,
    });

    return NextResponse.json({
      success: true,
      cached: false,
      explanation,
      source: provider,
    });
  } catch (error) {
    console.error('API Error in /api/explain:', error);
    return NextResponse.json(
      { error: (error as Error).message || 'Failed to generate explanation' },
      { status: 500 }
    );
  }
}
