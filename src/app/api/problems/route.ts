import { NextRequest, NextResponse } from 'next/server';
import { getProblems } from '@/lib/problemData';

export async function GET(request: NextRequest) {
  try {
    const { searchParams } = new URL(request.url);

    const search = searchParams.get('search') || undefined;
    const topic = searchParams.get('topic') || undefined;
    const pattern = searchParams.get('pattern') || undefined;
    const difficulty = searchParams.get('difficulty') || undefined;
    const platform = searchParams.get('platform') || undefined;
    const status = searchParams.get('status') || undefined;
    const page = parseInt(searchParams.get('page') || '1', 10);
    const limit = parseInt(searchParams.get('limit') || '25', 10);

    const result = await getProblems(
      { search, topic, pattern, difficulty, platform, status },
      page,
      limit
    );

    return NextResponse.json(result);
  } catch (error) {
    console.error('API Error in /api/problems:', error);
    return NextResponse.json(
      { error: 'Failed to fetch problems', details: (error as Error).message },
      { status: 500 }
    );
  }
}
