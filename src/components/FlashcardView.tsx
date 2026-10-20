'use client';

import React, { useState, useEffect } from 'react';
import { Problem } from '@/types';
import { CodeViewer } from './CodeViewer';
import { AIExplanationBox } from './AIExplanationBox';
import {
  ChevronLeft,
  ChevronRight,
  Sparkles,
  CheckCircle2,
  Clock,
  Eye,
  RotateCw,
  ExternalLink,
} from 'lucide-react';

interface FlashcardViewProps {
  problems: Problem[];
  onUpdateProblem: (updated: Problem) => void;
  onOpenSettings: () => void;
}

export const FlashcardView: React.FC<FlashcardViewProps> = ({
  problems,
  onUpdateProblem,
  onOpenSettings,
}) => {
  const [currentIndex, setCurrentIndex] = useState(0);
  const [revealPattern, setRevealPattern] = useState(false);
  const [revealCode, setRevealCode] = useState(false);
  const [revealAI, setRevealAI] = useState(false);

  const problem = problems[currentIndex] || problems[0];

  useEffect(() => {
    // Reset revealed states on card switch
    setRevealPattern(false);
    setRevealCode(false);
    setRevealAI(false);
  }, [currentIndex]);

  const handleNext = () => {
    if (currentIndex < problems.length - 1) {
      setCurrentIndex(currentIndex + 1);
    }
  };

  const handlePrev = () => {
    if (currentIndex > 0) {
      setCurrentIndex(currentIndex - 1);
    }
  };

  const handleRate = async (status: 'mastered' | 'reviewing' | 'unrevised') => {
    try {
      const res = await fetch(`/api/problems/${problem.slug || problem.id}`, {
        method: 'PATCH',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ revisionStatus: status }),
      });
      if (res.ok) {
        const updated = await res.json();
        onUpdateProblem({ ...problem, ...updated });
      }
    } catch (e) {
      console.error(e);
    }
    handleNext();
  };

  if (!problem) {
    return (
      <div className="glass-panel rounded-2xl p-12 text-center text-slate-400">
        No problems available for flashcards.
      </div>
    );
  }

  return (
    <div className="max-w-4xl mx-auto space-y-6">
      {/* Top Navigation & Counter */}
      <div className="flex items-center justify-between glass-panel px-5 py-3 rounded-2xl border border-slate-800">
        <div className="flex items-center space-x-2">
          <span className="text-xs font-semibold text-slate-400">Flashcard Deck:</span>
          <span className="text-xs font-bold text-white px-2 py-0.5 rounded bg-indigo-950/80 border border-indigo-800/40 font-mono">
            {currentIndex + 1} / {problems.length}
          </span>
        </div>

        <div className="flex items-center space-x-2">
          <button
            onClick={handlePrev}
            disabled={currentIndex === 0}
            className="p-1.5 rounded-lg bg-slate-800 hover:bg-slate-700 text-slate-300 disabled:opacity-40 transition"
            title="Previous card (Left Arrow)"
          >
            <ChevronLeft className="w-4 h-4" />
          </button>
          <button
            onClick={handleNext}
            disabled={currentIndex === problems.length - 1}
            className="p-1.5 rounded-lg bg-slate-800 hover:bg-slate-700 text-slate-300 disabled:opacity-40 transition"
            title="Next card (Right Arrow)"
          >
            <ChevronRight className="w-4 h-4" />
          </button>
        </div>
      </div>

      {/* Main Flashcard Card */}
      <div className="glass-panel rounded-3xl p-6 sm:p-8 border border-slate-700/80 shadow-2xl space-y-6 relative overflow-hidden">
        {/* Card Header */}
        <div className="flex flex-wrap items-center justify-between gap-3 border-b border-slate-800 pb-4">
          <div className="flex items-center space-x-2">
            <span className="text-xs font-mono font-bold px-2.5 py-1 rounded-md bg-slate-800 text-slate-300">
              #{problem.id}
            </span>
            <span className="text-xs px-2.5 py-1 rounded-md bg-blue-950/40 text-blue-300 border border-blue-800/40">
              {problem.platform}
            </span>
            <span className="text-xs px-2.5 py-1 rounded-md bg-emerald-950/40 text-emerald-300 border border-emerald-800/40">
              {problem.difficulty}
            </span>
            <span className="text-xs px-2.5 py-1 rounded-md bg-indigo-950/40 text-indigo-300 border border-indigo-900/40">
              {problem.topic}
            </span>
          </div>

          {problem.url && (
            <a
              href={problem.url}
              target="_blank"
              rel="noopener noreferrer"
              className="text-xs text-blue-400 hover:underline flex items-center space-x-1"
            >
              <span>View Source</span>
              <ExternalLink className="w-3 h-3" />
            </a>
          )}
        </div>

        {/* Title */}
        <h2 className="text-xl sm:text-2xl font-extrabold text-white tracking-tight">
          {problem.title}
        </h2>

        {/* Problem Statement Preview */}
        <div className="p-4 rounded-xl bg-slate-900/60 border border-slate-800 text-xs sm:text-sm text-slate-300 leading-relaxed max-h-60 overflow-y-auto">
          {problem.description ? (
            <div
              className="prose prose-invert prose-xs max-w-none"
              dangerouslySetInnerHTML={{ __html: problem.description }}
            />
          ) : (
            <p className="text-slate-400">Can you recall the optimal approach and algorithm for this problem?</p>
          )}
        </div>

        {/* Stage 1: Reveal Pattern & Intuition */}
        <div className="space-y-3">
          {!revealPattern ? (
            <button
              onClick={() => setRevealPattern(true)}
              className="w-full py-3 rounded-xl bg-gradient-to-r from-purple-900/40 to-indigo-900/40 hover:from-purple-900/60 hover:to-indigo-900/60 border border-purple-700/50 text-purple-200 text-xs sm:text-sm font-semibold flex items-center justify-center space-x-2 transition shadow-lg"
            >
              <Eye className="w-4 h-4" />
              <span>Reveal Core Pattern & Key Invariants</span>
            </button>
          ) : (
            <div className="p-4 rounded-xl bg-purple-950/30 border border-purple-800/40 space-y-2 animate-in fade-in">
              <div className="text-xs font-bold text-purple-300 flex items-center space-x-1.5">
                <Sparkles className="w-4 h-4" />
                <span>Pattern: {problem.pattern}</span>
              </div>
              <p className="text-xs text-slate-300">{problem.aiExplanation?.intuition || 'Think about the pointers/sliding window/state invariants.'}</p>
            </div>
          )}
        </div>

        {/* Stage 2: Reveal Code Solution */}
        {revealPattern && (
          <div className="space-y-3">
            {!revealCode ? (
              <button
                onClick={() => setRevealCode(true)}
                className="w-full py-2.5 rounded-xl bg-slate-800 hover:bg-slate-700 border border-slate-600/60 text-slate-200 text-xs sm:text-sm font-medium flex items-center justify-center space-x-2 transition"
              >
                <Eye className="w-4 h-4 text-emerald-400" />
                <span>Reveal C++ Solution Code</span>
              </button>
            ) : (
              <div className="animate-in fade-in">
                <CodeViewer
                  code={problem.solutions[0]?.code || '// Solution'}
                  lang={problem.solutions[0]?.lang || 'cpp'}
                  filename={problem.solutions[0]?.filename}
                  defaultExpanded={true}
                />
              </div>
            )}
          </div>
        )}

        {/* Stage 3: Reveal Full AI Explanation */}
        {revealCode && (
          <div className="space-y-3">
            {!revealAI ? (
              <button
                onClick={() => setRevealAI(true)}
                className="w-full py-2.5 rounded-xl bg-indigo-950/60 hover:bg-indigo-900/60 border border-indigo-800/50 text-indigo-300 text-xs sm:text-sm font-medium flex items-center justify-center space-x-2 transition"
              >
                <Sparkles className="w-4 h-4" />
                <span>Reveal Full AI Breakdown (ELI5, Complexities, Traps)</span>
              </button>
            ) : (
              <div className="animate-in fade-in">
                <AIExplanationBox
                  problem={problem}
                  onOpenSettings={onOpenSettings}
                  onExplanationUpdated={(newExp) => onUpdateProblem({ ...problem, aiExplanation: newExp })}
                />
              </div>
            )}
          </div>
        )}

        {/* Bottom Rating Bar (Active Recall feedback) */}
        <div className="pt-4 border-t border-slate-800 flex flex-col sm:flex-row items-center justify-between gap-3">
          <span className="text-xs text-slate-400 font-medium">How well did you know this?</span>

          <div className="flex items-center space-x-2.5 w-full sm:w-auto">
            <button
              onClick={() => handleRate('unrevised')}
              className="flex-1 sm:flex-initial px-4 py-2 rounded-xl bg-rose-950/60 hover:bg-rose-900/60 border border-rose-800/50 text-rose-300 text-xs font-semibold flex items-center justify-center space-x-1.5 transition"
            >
              <RotateCw className="w-3.5 h-3.5" />
              <span>Hard / Retry</span>
            </button>

            <button
              onClick={() => handleRate('reviewing')}
              className="flex-1 sm:flex-initial px-4 py-2 rounded-xl bg-amber-950/60 hover:bg-amber-900/60 border border-amber-800/50 text-amber-300 text-xs font-semibold flex items-center justify-center space-x-1.5 transition"
            >
              <Clock className="w-3.5 h-3.5" />
              <span>Medium / Review</span>
            </button>

            <button
              onClick={() => handleRate('mastered')}
              className="flex-1 sm:flex-initial px-4 py-2 rounded-xl bg-emerald-950/60 hover:bg-emerald-900/60 border border-emerald-800/50 text-emerald-300 text-xs font-semibold flex items-center justify-center space-x-1.5 transition"
            >
              <CheckCircle2 className="w-3.5 h-3.5" />
              <span>Easy / Mastered!</span>
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};
