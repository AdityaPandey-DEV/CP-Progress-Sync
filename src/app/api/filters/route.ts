import { NextResponse } from 'next/server';
import { getTopicsAndPatterns } from '@/lib/problemData';

export async function GET() {
  try {
    const data = await getTopicsAndPatterns();
    return NextResponse.json(data);
  } catch (error) {
    console.error('API Error in /api/filters:', error);
    return NextResponse.json(
      { error: 'Failed to fetch filters', details: (error as Error).message },
      { status: 500 }
    );
  }
}
