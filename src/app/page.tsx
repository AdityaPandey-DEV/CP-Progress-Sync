'use client';

import React, { useState, useEffect, useCallback } from 'react';
import { Problem, FilterOptions, RevisionStats } from '@/types';
import { Navbar } from '@/components/Navbar';
import { StatsBanner } from '@/components/StatsBanner';
import { FilterBar } from '@/components/FilterBar';
import { ContinuousFeedView } from '@/components/ContinuousFeedView';
import { SplitFocusView } from '@/components/SplitFocusView';
import { FlashcardView } from '@/components/FlashcardView';
import { AISettingsModal } from '@/components/AISettingsModal';

export default function Home() {
  const [viewMode, setViewMode] = useState<'feed' | 'split' | 'flashcard'>('feed');
  const [problems, setProblems] = useState<Problem[]>([]);
  const [total, setTotal] = useState(0);
  const [page, setPage] = useState(1);
  const [hasMore, setHasMore] = useState(true);
  const [isLoading, setIsLoading] = useState(true);
  const [isLoadingMore, setIsLoadingMore] = useState(false);

  // Filters
  const [filters, setFilters] = useState<FilterOptions>({
    search: '',
    topic: 'all',
    pattern: 'all',
    difficulty: 'all',
    platform: 'all',
    status: 'all',
  });

  const [topics, setTopics] = useState<{ name: string; count: number }[]>([]);
  const [patterns, setPatterns] = useState<{ name: string; count: number }[]>([]);
  const [stats, setStats] = useState<RevisionStats | null>(null);
  const [isSettingsOpen, setIsSettingsOpen] = useState(false);

  // Fetch Filter metadata & Stats
  const loadMetadata = async () => {
    try {
      const [filterRes, statRes] = await Promise.all([
        fetch('/api/filters'),
        fetch('/api/stats'),
      ]);
      if (filterRes.ok) {
        const data = await filterRes.json();
        setTopics(data.topics || []);
        setPatterns(data.patterns || []);
      }
      if (statRes.ok) {
        const data = await statRes.json();
        setStats(data);
      }
    } catch (e) {
      console.error('Failed to load initial metadata:', e);
    }
  };

  useEffect(() => {
    loadMetadata();
  }, []);

  // Fetch problems when filters change or page resets
  const fetchProblems = useCallback(async (currentFilters: FilterOptions, pageNum: number, append = false) => {
    if (append) {
      setIsLoadingMore(true);
    } else {
      setIsLoading(true);
    }

    try {
      const params = new URLSearchParams();
      if (currentFilters.search) params.append('search', currentFilters.search);
      if (currentFilters.topic && currentFilters.topic !== 'all') params.append('topic', currentFilters.topic);
      if (currentFilters.pattern && currentFilters.pattern !== 'all') params.append('pattern', currentFilters.pattern);
      if (currentFilters.difficulty && currentFilters.difficulty !== 'all') params.append('difficulty', currentFilters.difficulty);
      if (currentFilters.platform && currentFilters.platform !== 'all') params.append('platform', currentFilters.platform);
      if (currentFilters.status && currentFilters.status !== 'all') params.append('status', currentFilters.status);

      const limit = viewMode === 'split' || viewMode === 'flashcard' ? 100 : 25;
      params.append('page', String(pageNum));
      params.append('limit', String(limit));

      const res = await fetch(`/api/problems?${params.toString()}`);
      if (res.ok) {
        const data = await res.json();
        const incoming: Problem[] = data.problems || [];
        setTotal(data.total || 0);
        setHasMore(pageNum < (data.totalPages || 1));

        if (append) {
          setProblems(prev => [...prev, ...incoming]);
        } else {
          setProblems(incoming);
        }
      }
    } catch (e) {
      console.error('Failed to load problems:', e);
    } finally {
      setIsLoading(false);
      setIsLoadingMore(false);
    }
  }, [viewMode]);

  // Trigger problem fetch whenever filters change
  useEffect(() => {
    setPage(1);
    fetchProblems(filters, 1, false);
  }, [filters, fetchProblems]);

  const handleLoadMore = () => {
    if (!hasMore || isLoadingMore) return;
    const nextPage = page + 1;
    setPage(nextPage);
    fetchProblems(filters, nextPage, true);
  };

  const handleUpdateProblem = (updated: Problem) => {
    setProblems(prev =>
      prev.map(p => (p.id === updated.id ? { ...p, ...updated } : p))
    );
    // Refresh stats in background
    fetch('/api/stats')
      .then(res => res.json())
      .then(data => setStats(data))
      .catch(() => {});
  };

  return (
    <div className="min-h-screen flex flex-col bg-[#090d16] text-slate-100">
      {/* Navigation Bar */}
      <Navbar
        viewMode={viewMode}
        onChangeViewMode={setViewMode}
        onOpenSettings={() => setIsSettingsOpen(true)}
        masteredCount={stats?.mastered || 0}
        totalCount={stats?.total || 632}
      />

      {/* Main Container */}
      <main className="flex-1 max-w-7xl w-full mx-auto px-4 sm:px-6 py-6 space-y-6">
        {/* Revision Stats Banner */}
        <StatsBanner
          stats={stats}
          activeStatusFilter={filters.status}
          onSelectStatus={(status) => setFilters({ ...filters, status })}
          onSelectDifficulty={(diff) => setFilters({ ...filters, difficulty: diff })}
        />

        {/* Filter Bar (Topic, Pattern, Platform, Search) */}
        <FilterBar
          filters={filters}
          topics={topics}
          patterns={patterns}
          onFilterChange={setFilters}
          totalFilteredCount={total}
        />

        {/* Active Study View */}
        {viewMode === 'feed' && (
          <ContinuousFeedView
            problems={problems}
            total={total}
            isLoading={isLoading}
            isLoadingMore={isLoadingMore}
            hasMore={hasMore}
            onLoadMore={handleLoadMore}
            onUpdateProblem={handleUpdateProblem}
            onOpenSettings={() => setIsSettingsOpen(true)}
          />
        )}

        {viewMode === 'split' && (
          <SplitFocusView
            problems={problems}
            onUpdateProblem={handleUpdateProblem}
            onOpenSettings={() => setIsSettingsOpen(true)}
          />
        )}

        {viewMode === 'flashcard' && (
          <FlashcardView
            problems={problems}
            onUpdateProblem={handleUpdateProblem}
            onOpenSettings={() => setIsSettingsOpen(true)}
          />
        )}
      </main>

      {/* AI & Database Settings Modal */}
      <AISettingsModal
        isOpen={isSettingsOpen}
        onClose={() => setIsSettingsOpen(false)}
      />

      {/* Footer */}
      <footer className="border-t border-slate-900 py-6 text-center text-xs text-slate-500">
        <p>
          Competitive Programming AI Revision Hub • Built with Next.js, Mongoose, Gemini & Groq •{' '}
          <a
            href="https://github.com/AdityaPandey-DEV/CP-Progress-Sync"
            target="_blank"
            rel="noopener noreferrer"
            className="text-slate-400 hover:text-white underline"
          >
            AdityaPandey-DEV/CP-Progress-Sync
          </a>
        </p>
      </footer>
    </div>
  );
}
