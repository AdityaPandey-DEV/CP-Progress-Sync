'use client';

import React from 'react';
import { FilterOptions } from '@/types';
import { Search, X, SlidersHorizontal } from 'lucide-react';

interface FilterBarProps {
  filters: FilterOptions;
  topics: { name: string; count: number }[];
  patterns: { name: string; count: number }[];
  onFilterChange: (newFilters: FilterOptions) => void;
  totalFilteredCount: number;
}

export const FilterBar: React.FC<FilterBarProps> = ({
  filters,
  topics,
  patterns,
  onFilterChange,
  totalFilteredCount,
}) => {
  const hasActiveFilters = Boolean(
    filters.search ||
    (filters.topic && filters.topic !== 'all') ||
    (filters.pattern && filters.pattern !== 'all') ||
    (filters.difficulty && filters.difficulty !== 'all') ||
    (filters.platform && filters.platform !== 'all') ||
    (filters.status && filters.status !== 'all')
  );

  const resetFilters = () => {
    onFilterChange({
      search: '',
      topic: 'all',
      pattern: 'all',
      difficulty: 'all',
      platform: 'all',
      status: 'all',
    });
  };

  return (
    <div className="glass-panel rounded-2xl p-4 space-y-3.5 border border-slate-800/80 shadow-lg">
      {/* Search & Main Row */}
      <div className="flex flex-col md:flex-row items-stretch md:items-center gap-3">
        {/* Search Input */}
        <div className="relative flex-1">
          <Search className="w-4 h-4 text-slate-400 absolute left-3.5 top-1/2 -translate-y-1/2 pointer-events-none" />
          <input
            type="text"
            value={filters.search || ''}
            onChange={(e) => onFilterChange({ ...filters, search: e.target.value })}
            placeholder="Search questions by name, number (#1), topic, or pattern..."
            className="w-full pl-10 pr-9 py-2.5 rounded-xl bg-slate-900/90 border border-slate-800 text-slate-200 placeholder-slate-500 text-xs sm:text-sm focus:outline-none focus:border-indigo-500 focus:ring-1 focus:ring-indigo-500/50 transition font-sans"
          />
          {filters.search && (
            <button
              onClick={() => onFilterChange({ ...filters, search: '' })}
              className="absolute right-3 top-1/2 -translate-y-1/2 text-slate-400 hover:text-white"
            >
              <X className="w-4 h-4" />
            </button>
          )}
        </div>

        {/* Difficulty Segment Buttons */}
        <div className="flex items-center rounded-xl bg-slate-900/90 border border-slate-800 p-1 text-xs shrink-0">
          {['all', 'Easy', 'Medium', 'Hard'].map((diff) => {
            const isActive = (filters.difficulty || 'all') === diff;
            return (
              <button
                key={diff}
                onClick={() => onFilterChange({ ...filters, difficulty: diff })}
                className={`px-3 py-1.5 rounded-lg font-medium transition ${
                  isActive
                    ? diff === 'Easy'
                      ? 'bg-emerald-950/80 text-emerald-400 border border-emerald-800/40 shadow-sm'
                      : diff === 'Medium'
                      ? 'bg-amber-950/80 text-amber-400 border border-amber-800/40 shadow-sm'
                      : diff === 'Hard'
                      ? 'bg-rose-950/80 text-rose-400 border border-rose-800/40 shadow-sm'
                      : 'bg-indigo-900/80 text-indigo-200 border border-indigo-700/50 shadow-sm'
                    : 'text-slate-400 hover:text-slate-200'
                }`}
              >
                {diff === 'all' ? 'All Diff' : diff}
              </button>
            );
          })}
        </div>

        {/* Platform Selector */}
        <div className="flex items-center rounded-xl bg-slate-900/90 border border-slate-800 p-1 text-xs shrink-0">
          {['all', 'LeetCode', 'Codeforces'].map((plat) => {
            const isActive = (filters.platform || 'all') === plat;
            return (
              <button
                key={plat}
                onClick={() => onFilterChange({ ...filters, platform: plat })}
                className={`px-3 py-1.5 rounded-lg font-medium transition ${
                  isActive
                    ? 'bg-blue-900/80 text-blue-200 border border-blue-700/50 shadow-sm'
                    : 'text-slate-400 hover:text-slate-200'
                }`}
              >
                {plat === 'all' ? 'All Platforms' : plat}
              </button>
            );
          })}
        </div>
      </div>

      {/* Second Row: Topic and Pattern Dropdowns + Active Filter Counts */}
      <div className="flex flex-col sm:flex-row items-stretch sm:items-center justify-between gap-3 pt-1 border-t border-slate-800/50">
        <div className="flex flex-wrap items-center gap-2.5">
          {/* Topic Dropdown */}
          <div className="relative">
            <select
              value={filters.topic || 'all'}
              onChange={(e) => onFilterChange({ ...filters, topic: e.target.value })}
              className="appearance-none bg-slate-900/90 text-slate-200 border border-slate-800 hover:border-slate-700 rounded-xl px-3.5 py-1.5 pr-8 text-xs font-medium focus:outline-none focus:border-indigo-500 cursor-pointer"
            >
              <option value="all">📂 All Topics ({topics.reduce((acc, t) => acc + t.count, 0)})</option>
              {topics.map((t) => (
                <option key={t.name} value={t.name}>
                  {t.name} ({t.count})
                </option>
              ))}
            </select>
            <div className="pointer-events-none absolute right-2.5 top-1/2 -translate-y-1/2 text-slate-400 text-[10px]">
              ▼
            </div>
          </div>

          {/* Pattern Dropdown */}
          <div className="relative">
            <select
              value={filters.pattern || 'all'}
              onChange={(e) => onFilterChange({ ...filters, pattern: e.target.value })}
              className="appearance-none bg-slate-900/90 text-slate-200 border border-slate-800 hover:border-slate-700 rounded-xl px-3.5 py-1.5 pr-8 text-xs font-medium focus:outline-none focus:border-purple-500 cursor-pointer"
            >
              <option value="all">⚡ All Patterns ({patterns.reduce((acc, p) => acc + p.count, 0)})</option>
              {patterns.map((p) => (
                <option key={p.name} value={p.name}>
                  {p.name} ({p.count})
                </option>
              ))}
            </select>
            <div className="pointer-events-none absolute right-2.5 top-1/2 -translate-y-1/2 text-slate-400 text-[10px]">
              ▼
            </div>
          </div>

          {/* Status Dropdown */}
          <div className="relative">
            <select
              value={filters.status || 'all'}
              onChange={(e) => onFilterChange({ ...filters, status: e.target.value })}
              className="appearance-none bg-slate-900/90 text-slate-200 border border-slate-800 hover:border-slate-700 rounded-xl px-3.5 py-1.5 pr-8 text-xs font-medium focus:outline-none focus:border-emerald-500 cursor-pointer"
            >
              <option value="all">📋 All Statuses</option>
              <option value="mastered">✅ Mastered</option>
              <option value="reviewing">🔄 Reviewing</option>
              <option value="unrevised">⏳ Unrevised</option>
              <option value="starred">⭐ Starred</option>
            </select>
            <div className="pointer-events-none absolute right-2.5 top-1/2 -translate-y-1/2 text-slate-400 text-[10px]">
              ▼
            </div>
          </div>
        </div>

        {/* Right: Results count & Reset */}
        <div className="flex items-center space-x-2 justify-between sm:justify-end text-xs">
          <span className="text-slate-400 font-medium">
            Showing <strong className="text-white font-bold">{totalFilteredCount}</strong> questions
          </span>

          {hasActiveFilters && (
            <button
              onClick={resetFilters}
              className="flex items-center space-x-1 text-slate-400 hover:text-rose-400 px-2 py-1 rounded-md hover:bg-rose-950/30 transition"
              title="Reset all filters"
            >
              <X className="w-3.5 h-3.5" />
              <span>Reset</span>
            </button>
          )}
        </div>
      </div>
    </div>
  );
};
