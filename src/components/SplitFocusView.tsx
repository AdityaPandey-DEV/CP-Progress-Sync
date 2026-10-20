'use client';

import React, { useState } from 'react';
import { Problem } from '@/types';
import { ProblemCard } from './ProblemCard';
import { Star, CheckCircle2, Clock, Sparkles } from 'lucide-react';

interface SplitFocusViewProps {
  problems: Problem[];
  onUpdateProblem: (updated: Problem) => void;
  onOpenSettings: () => void;
}

export const SplitFocusView: React.FC<SplitFocusViewProps> = ({
  problems,
  onUpdateProblem,
  onOpenSettings,
}) => {
  const [selectedId, setSelectedId] = useState<string | number>(problems[0]?.id || 1);

  const selectedProblem = problems.find(p => p.id === selectedId) || problems[0];

  const difficultyColors = {
    Easy: 'text-emerald-400 bg-emerald-950/60 border-emerald-800/40',
    Medium: 'text-amber-400 bg-amber-950/60 border-amber-800/40',
    Hard: 'text-rose-400 bg-rose-950/60 border-rose-800/40',
  };

  return (
    <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 items-start">
      {/* Left Column: Problem List */}
      <div className="lg:col-span-5 glass-panel rounded-2xl border border-slate-800/80 p-3 space-y-2 max-h-[82vh] overflow-y-auto">
        <div className="px-3 py-2 text-xs font-semibold text-slate-400 border-b border-slate-800/80 flex items-center justify-between">
          <span>QUESTIONS LIST ({problems.length})</span>
          <span className="text-[11px] text-slate-500">Click to study</span>
        </div>

        <div className="space-y-1.5">
          {problems.map((p) => {
            const isSelected = p.id === selectedProblem?.id;
            return (
              <button
                key={p.id}
                onClick={() => setSelectedId(p.id)}
                className={`w-full text-left p-3 rounded-xl transition border flex items-center justify-between gap-2.5 ${
                  isSelected
                    ? 'bg-indigo-950/70 border-indigo-500/80 text-white shadow-md shadow-indigo-950/40'
                    : 'bg-slate-900/60 border-slate-800/60 hover:bg-slate-800/60 text-slate-300'
                }`}
              >
                <div className="flex items-center space-x-2.5 min-w-0">
                  <span className="text-[11px] font-mono font-bold text-slate-400 shrink-0">
                    #{p.id}
                  </span>
                  <div className="truncate">
                    <div className="text-xs font-medium truncate">{p.title}</div>
                    <div className="text-[10px] text-slate-400 truncate flex items-center space-x-1.5 mt-0.5">
                      <span>{p.topic}</span>
                      <span>•</span>
                      <span className="text-slate-500">{p.platform}</span>
                    </div>
                  </div>
                </div>

                <div className="flex items-center space-x-1.5 shrink-0">
                  <span
                    className={`text-[10px] font-bold px-1.5 py-0.5 rounded border ${
                      difficultyColors[p.difficulty as keyof typeof difficultyColors] || 'text-slate-400'
                    }`}
                  >
                    {p.difficulty[0]}
                  </span>

                  {p.isBookmarked && <Star className="w-3.5 h-3.5 text-amber-400 fill-amber-400" />}

                  {p.revisionStatus === 'mastered' && (
                    <CheckCircle2 className="w-3.5 h-3.5 text-emerald-400" />
                  )}
                  {p.revisionStatus === 'reviewing' && (
                    <Sparkles className="w-3.5 h-3.5 text-amber-400" />
                  )}
                </div>
              </button>
            );
          })}
        </div>
      </div>

      {/* Right Column: Deep Study Workspace */}
      <div className="lg:col-span-7 sticky top-20">
        {selectedProblem ? (
          <ProblemCard
            key={selectedProblem.id}
            problem={selectedProblem}
            onUpdateProblem={onUpdateProblem}
            onOpenSettings={onOpenSettings}
          />
        ) : (
          <div className="glass-panel rounded-2xl p-12 text-center text-slate-400">
            Select a question from the left panel to study
          </div>
        )}
      </div>
    </div>
  );
};
