import { NextResponse } from 'next/server';
import { getRevisionStats } from '@/lib/problemData';

export async function GET() {
  try {
    const stats = await getRevisionStats();
    return NextResponse.json(stats);
  } catch (error) {
    console.error('API Error in /api/stats:', error);
    return NextResponse.json(
      { error: 'Failed to fetch revision stats', details: (error as Error).message },
      { status: 500 }
    );
  }
}
