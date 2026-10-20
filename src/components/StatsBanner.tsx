'use client';

import React from 'react';
import { RevisionStats } from '@/types';
import { CheckCircle2, Clock, Star, Trophy, Layers } from 'lucide-react';

interface StatsBannerProps {
  stats: RevisionStats | null;
  activeStatusFilter?: string;
  onSelectStatus?: (status: string) => void;
  onSelectDifficulty?: (diff: string) => void;
}

export const StatsBanner: React.FC<StatsBannerProps> = ({
  stats,
  activeStatusFilter = 'all',
  onSelectStatus,
  onSelectDifficulty,
}) => {
  if (!stats) return null;

  const masteredPercent = stats.total > 0 ? Math.round((stats.mastered / stats.total) * 100) : 0;
  const reviewingPercent = stats.total > 0 ? Math.round((stats.reviewing / stats.total) * 100) : 0;

  return (
    <section className="glass-panel rounded-2xl p-4 sm:p-5 border border-slate-800/80 shadow-2xl relative overflow-hidden">
      {/* Background glow decoration */}
      <div className="absolute top-0 right-0 w-80 h-32 bg-indigo-600/10 rounded-full blur-3xl pointer-events-none -mr-20 -mt-10" />

      <div className="flex flex-col lg:flex-row items-stretch lg:items-center justify-between gap-4">
        {/* Left: Overall CP Stats */}
        <div className="space-y-2">
          <div className="flex items-center space-x-2">
            <div className="p-1.5 rounded-lg bg-gradient-to-tr from-indigo-600 to-purple-600 text-white">
              <Trophy className="w-4 h-4" />
            </div>
            <h2 className="text-sm font-bold text-white tracking-wide">
              CP Revision Dashboard
            </h2>
            <span className="text-xs px-2 py-0.5 rounded-full bg-slate-800 text-slate-300 font-mono">
              {stats.total} Solved
            </span>
          </div>

          {/* Progress Bar */}
          <div className="w-full sm:w-72 space-y-1">
            <div className="flex justify-between text-[11px] text-slate-400">
              <span>Mastery Progress</span>
              <span className="text-emerald-400 font-semibold">{masteredPercent}%</span>
            </div>
            <div className="h-2 w-full bg-slate-800 rounded-full overflow-hidden flex">
              <div
                style={{ width: `${masteredPercent}%` }}
                className="bg-emerald-500 transition-all duration-500"
                title={`Mastered: ${stats.mastered}`}
              />
              <div
                style={{ width: `${reviewingPercent}%` }}
                className="bg-amber-500 transition-all duration-500"
                title={`Reviewing: ${stats.reviewing}`}
              />
            </div>
          </div>
        </div>

        {/* Right: Clickable Stat Pills */}
        <div className="flex flex-wrap items-center gap-2 text-xs">
          {/* Mastered */}
          <button
            onClick={() => onSelectStatus && onSelectStatus(activeStatusFilter === 'mastered' ? 'all' : 'mastered')}
            className={`flex items-center space-x-2 px-3 py-2 rounded-xl border transition ${
              activeStatusFilter === 'mastered'
                ? 'bg-emerald-950/80 border-emerald-500 text-emerald-300 font-semibold shadow-md shadow-emerald-950/50'
                : 'bg-slate-900/80 border-slate-800 hover:border-slate-700 text-slate-300'
            }`}
          >
            <CheckCircle2 className="w-4 h-4 text-emerald-400" />
            <div>
              <div className="text-[10px] text-slate-400 font-medium">Mastered</div>
              <div className="font-bold text-emerald-400">{stats.mastered}</div>
            </div>
          </button>

          {/* Reviewing */}
          <button
            onClick={() => onSelectStatus && onSelectStatus(activeStatusFilter === 'reviewing' ? 'all' : 'reviewing')}
            className={`flex items-center space-x-2 px-3 py-2 rounded-xl border transition ${
              activeStatusFilter === 'reviewing'
                ? 'bg-amber-950/80 border-amber-500 text-amber-300 font-semibold shadow-md shadow-amber-950/50'
                : 'bg-slate-900/80 border-slate-800 hover:border-slate-700 text-slate-300'
            }`}
          >
            <Clock className="w-4 h-4 text-amber-400" />
            <div>
              <div className="text-[10px] text-slate-400 font-medium">Reviewing</div>
              <div className="font-bold text-amber-400">{stats.reviewing}</div>
            </div>
          </button>

          {/* Starred */}
          <button
            onClick={() => onSelectStatus && onSelectStatus(activeStatusFilter === 'starred' ? 'all' : 'starred')}
            className={`flex items-center space-x-2 px-3 py-2 rounded-xl border transition ${
              activeStatusFilter === 'starred'
                ? 'bg-yellow-950/80 border-yellow-500 text-yellow-300 font-semibold shadow-md shadow-yellow-950/50'
                : 'bg-slate-900/80 border-slate-800 hover:border-slate-700 text-slate-300'
            }`}
          >
            <Star className="w-4 h-4 text-yellow-400 fill-yellow-400" />
            <div>
              <div className="text-[10px] text-slate-400 font-medium">Starred</div>
              <div className="font-bold text-yellow-400">{stats.starred}</div>
            </div>
          </button>

          {/* Difficulty Breakdown Badges */}
          <div className="flex items-center space-x-1.5 pl-2 border-l border-slate-800">
            <button
              onClick={() => onSelectDifficulty && onSelectDifficulty('Easy')}
              className="px-2.5 py-1.5 rounded-lg bg-slate-900/80 hover:bg-emerald-950/40 border border-slate-800 hover:border-emerald-800/60 text-center transition"
            >
              <div className="text-[10px] text-slate-400">Easy</div>
              <div className="text-xs font-bold text-emerald-400">{stats.byDifficulty.Easy}</div>
            </button>

            <button
              onClick={() => onSelectDifficulty && onSelectDifficulty('Medium')}
              className="px-2.5 py-1.5 rounded-lg bg-slate-900/80 hover:bg-amber-950/40 border border-slate-800 hover:border-amber-800/60 text-center transition"
            >
              <div className="text-[10px] text-slate-400">Med</div>
              <div className="text-xs font-bold text-amber-400">{stats.byDifficulty.Medium}</div>
            </button>

            <button
              onClick={() => onSelectDifficulty && onSelectDifficulty('Hard')}
              className="px-2.5 py-1.5 rounded-lg bg-slate-900/80 hover:bg-rose-950/40 border border-slate-800 hover:border-rose-800/60 text-center transition"
            >
              <div className="text-[10px] text-slate-400">Hard</div>
              <div className="text-xs font-bold text-rose-400">{stats.byDifficulty.Hard}</div>
            </button>
          </div>
        </div>
      </div>
    </section>
  );
};
