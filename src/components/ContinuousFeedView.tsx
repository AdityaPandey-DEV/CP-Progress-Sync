'use client';

import React from 'react';
import { Problem } from '@/types';
import { ProblemCard } from './ProblemCard';
import { ArrowUp, Loader2 } from 'lucide-react';

interface ContinuousFeedViewProps {
  problems: Problem[];
  total: number;
  isLoading: boolean;
  isLoadingMore: boolean;
  hasMore: boolean;
  onLoadMore: () => void;
  onUpdateProblem: (updated: Problem) => void;
  onOpenSettings: () => void;
}

export const ContinuousFeedView: React.FC<ContinuousFeedViewProps> = ({
  problems,
  total,
  isLoading,
  isLoadingMore,
  hasMore,
  onLoadMore,
  onUpdateProblem,
  onOpenSettings,
}) => {
  const scrollToTop = () => {
    window.scrollTo({ top: 0, behavior: 'smooth' });
  };

  if (isLoading && problems.length === 0) {
    return (
      <div className="py-20 text-center space-y-3">
        <Loader2 className="w-8 h-8 text-indigo-400 animate-spin mx-auto" />
        <p className="text-slate-400 text-sm">Loading competitive programming archive & AI notes...</p>
      </div>
    );
  }

  if (problems.length === 0) {
    return (
      <div className="glass-panel rounded-2xl p-12 text-center space-y-3 border border-slate-800">
        <div className="w-12 h-12 rounded-full bg-slate-800/80 text-slate-400 flex items-center justify-center mx-auto text-xl">
          🔍
        </div>
        <h3 className="text-base font-bold text-white">No questions matched your filters</h3>
        <p className="text-xs text-slate-400 max-w-sm mx-auto">
          Try resetting some filters or searching for different topics, patterns, or difficulty.
        </p>
      </div>
    );
  }

  return (
    <div className="space-y-6">
      {/* Continuous Feed Stream */}
      <div className="space-y-6">
        {problems.map((problem) => (
          <ProblemCard
            key={problem.problemId || `${problem.platform}-${problem.id}`}
            problem={problem}
            onUpdateProblem={onUpdateProblem}
            onOpenSettings={onOpenSettings}
          />
        ))}
      </div>

      {/* Infinite Scroll / Load More Footer */}
      <div className="py-6 flex flex-col items-center justify-center space-y-3">
        {hasMore ? (
          <button
            onClick={onLoadMore}
            disabled={isLoadingMore}
            className="flex items-center space-x-2 px-6 py-2.5 rounded-xl bg-slate-900/90 hover:bg-slate-800 border border-slate-700/80 text-slate-200 text-xs font-semibold shadow-lg hover:border-indigo-500/50 transition disabled:opacity-50"
          >
            {isLoadingMore ? (
              <>
                <Loader2 className="w-4 h-4 animate-spin text-indigo-400" />
                <span>Loading more questions...</span>
              </>
            ) : (
              <span>Load More Questions ({problems.length} of {total})</span>
            )}
          </button>
        ) : (
          <div className="text-xs text-slate-500 flex items-center space-x-2">
            <span>🎉 You have scrolled through all {total} questions!</span>
          </div>
        )}

        <button
          onClick={scrollToTop}
          className="flex items-center space-x-1 text-xs text-slate-400 hover:text-slate-200 pt-2 transition"
        >
          <ArrowUp className="w-3.5 h-3.5" />
          <span>Back to Top</span>
        </button>
      </div>
    </div>
  );
};
