import { NextRequest, NextResponse } from 'next/server';
import { getProblemByIdOrSlug, updateProblemRevision } from '@/lib/problemData';

export async function GET(
  request: NextRequest,
  context: { params: Promise<{ id: string }> }
) {
  try {
    const { id } = await context.params;
    const problem = await getProblemByIdOrSlug(id);

    if (!problem) {
      return NextResponse.json({ error: 'Problem not found' }, { status: 404 });
    }

    return NextResponse.json(problem);
  } catch (error) {
    console.error('API Error in /api/problems/[id]:', error);
    return NextResponse.json(
      { error: 'Failed to fetch problem', details: (error as Error).message },
      { status: 500 }
    );
  }
}

export async function PATCH(
  request: NextRequest,
  context: { params: Promise<{ id: string }> }
) {
  try {
    const { id } = await context.params;
    const body = await request.json();

    const allowedUpdates = {
      ...(body.revisionStatus !== undefined && { revisionStatus: body.revisionStatus }),
      ...(body.isBookmarked !== undefined && { isBookmarked: body.isBookmarked }),
      ...(body.personalNotes !== undefined && { personalNotes: body.personalNotes }),
    };

    const updated = await updateProblemRevision(id, allowedUpdates);

    if (!updated) {
      return NextResponse.json({ error: 'Problem not found' }, { status: 404 });
    }

    return NextResponse.json(updated);
  } catch (error) {
    console.error('API Error in PATCH /api/problems/[id]:', error);
    return NextResponse.json(
      { error: 'Failed to update problem revision', details: (error as Error).message },
      { status: 500 }
    );
  }
}
