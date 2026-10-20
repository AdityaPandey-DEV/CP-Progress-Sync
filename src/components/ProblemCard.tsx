'use client';

import React, { useState } from 'react';
import { Problem, AIExplanation } from '@/types';
import { CodeViewer } from './CodeViewer';
import { AIExplanationBox } from './AIExplanationBox';
import {
  ExternalLink,
  Star,
  CheckCircle2,
  Clock,
  Sparkles,
  BookOpen,
  Code2,
  ChevronDown,
  ChevronUp,
  Save,
} from 'lucide-react';

interface ProblemCardProps {
  problem: Problem;
  onUpdateProblem?: (updated: Problem) => void;
  onOpenSettings?: () => void;
  defaultExpanded?: boolean;
}

export const ProblemCard: React.FC<ProblemCardProps> = ({
  problem,
  onUpdateProblem,
  onOpenSettings,
  defaultExpanded = true,
}) => {
  const [currentProblem, setCurrentProblem] = useState<Problem>(problem);
  const [showStatement, setShowStatement] = useState(defaultExpanded);
  const [showCode, setShowCode] = useState(true);
  const [showAI, setShowAI] = useState(true);
  const [notes, setNotes] = useState(problem.personalNotes || '');
  const [isSavingNotes, setIsSavingNotes] = useState(false);
  const [notesSavedAlert, setNotesSavedAlert] = useState(false);

  const difficultyColors = {
    Easy: 'bg-emerald-950/80 text-emerald-400 border-emerald-800/50',
    Medium: 'bg-amber-950/80 text-amber-400 border-amber-800/50',
    Hard: 'bg-rose-950/80 text-rose-400 border-rose-800/50',
  };

  const platformColors = {
    LeetCode: 'bg-yellow-950/40 text-yellow-300 border-yellow-800/40',
    Codeforces: 'bg-blue-950/40 text-blue-300 border-blue-800/40',
  };

  const updateBackend = async (updates: Partial<Problem>) => {
    try {
      const res = await fetch(`/api/problems/${currentProblem.slug || currentProblem.id}`, {
        method: 'PATCH',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(updates),
      });
      if (res.ok) {
        const updated = await res.json();
        setCurrentProblem(prev => ({ ...prev, ...updated }));
        if (onUpdateProblem) onUpdateProblem({ ...currentProblem, ...updated });
      }
    } catch (e) {
      console.error('Failed to update problem status:', e);
    }
  };

  const toggleBookmark = () => {
    const newVal = !currentProblem.isBookmarked;
    setCurrentProblem(prev => ({ ...prev, isBookmarked: newVal }));
    updateBackend({ isBookmarked: newVal });
  };

  const setRevisionStatus = (status: 'unrevised' | 'reviewing' | 'mastered') => {
    setCurrentProblem(prev => ({ ...prev, revisionStatus: status }));
    updateBackend({ revisionStatus: status });
  };

  const savePersonalNotes = async () => {
    setIsSavingNotes(true);
    await updateBackend({ personalNotes: notes });
    setIsSavingNotes(false);
    setNotesSavedAlert(true);
    setTimeout(() => setNotesSavedAlert(false), 2000);
  };

  const handleExplanationUpdated = (newExp: AIExplanation) => {
    const updated = { ...currentProblem, aiExplanation: newExp };
    setCurrentProblem(updated);
    if (onUpdateProblem) onUpdateProblem(updated);
  };

  return (
    <article
      id={`problem-${currentProblem.id}`}
      className="rounded-2xl glass-panel p-5 space-y-4 transition-all duration-200 hover:border-slate-700/80"
    >
      {/* Top Bar / Meta */}
      <div className="flex flex-wrap items-center justify-between gap-2.5">
        <div className="flex flex-wrap items-center gap-2">
          {/* ID */}
          <span className="text-xs font-mono font-bold px-2.5 py-1 rounded-md bg-slate-800 text-slate-300 border border-slate-700/80">
            #{currentProblem.id}
          </span>

          {/* Platform */}
          <span
            className={`text-xs px-2.5 py-1 rounded-md border font-medium ${
              platformColors[currentProblem.platform as keyof typeof platformColors] ||
              'bg-slate-800 text-slate-300 border-slate-700'
            }`}
          >
            {currentProblem.platform}
          </span>

          {/* Difficulty */}
          <span
            className={`text-xs px-2.5 py-1 rounded-md border font-semibold ${
              difficultyColors[currentProblem.difficulty as keyof typeof difficultyColors] ||
              'bg-slate-800 text-slate-300'
            }`}
          >
            {currentProblem.difficulty}
          </span>

          {/* Topic Badge */}
          <span className="text-xs px-2.5 py-1 rounded-md bg-indigo-950/40 text-indigo-300 border border-indigo-900/40 font-medium">
            📂 {currentProblem.topic}
          </span>

          {/* Pattern Badge */}
          <span className="text-xs px-2.5 py-1 rounded-md bg-purple-950/40 text-purple-300 border border-purple-900/40 font-medium">
            ⚡ {currentProblem.pattern}
          </span>
        </div>

        {/* Right Action Icons: Star & Status */}
        <div className="flex items-center space-x-2">
          {/* Bookmark Button */}
          <button
            onClick={toggleBookmark}
            className={`p-1.5 rounded-lg border transition ${
              currentProblem.isBookmarked
                ? 'bg-amber-950/60 border-amber-600/80 text-amber-400 shadow-sm'
                : 'bg-slate-800/80 border-slate-700/80 text-slate-400 hover:text-amber-400'
            }`}
            title={currentProblem.isBookmarked ? 'Starred for revision' : 'Star problem'}
          >
            <Star className={`w-4 h-4 ${currentProblem.isBookmarked ? 'fill-amber-400' : ''}`} />
          </button>

          {/* Revision Status Pill Group */}
          <div className="flex items-center rounded-lg bg-slate-900/90 border border-slate-800 p-0.5 text-xs">
            <button
              onClick={() => setRevisionStatus('unrevised')}
              className={`px-2 py-1 rounded-md flex items-center space-x-1 transition ${
                currentProblem.revisionStatus === 'unrevised'
                  ? 'bg-slate-800 text-slate-200 font-semibold shadow'
                  : 'text-slate-400 hover:text-slate-200'
              }`}
              title="Mark Unrevised"
            >
              <Clock className="w-3 h-3" />
              <span className="hidden sm:inline">Unrevised</span>
            </button>

            <button
              onClick={() => setRevisionStatus('reviewing')}
              className={`px-2 py-1 rounded-md flex items-center space-x-1 transition ${
                currentProblem.revisionStatus === 'reviewing'
                  ? 'bg-amber-900/60 text-amber-300 font-semibold shadow'
                  : 'text-slate-400 hover:text-amber-300'
              }`}
              title="Mark Reviewing"
            >
              <Sparkles className="w-3 h-3 text-amber-400" />
              <span className="hidden sm:inline">Reviewing</span>
            </button>

            <button
              onClick={() => setRevisionStatus('mastered')}
              className={`px-2 py-1 rounded-md flex items-center space-x-1 transition ${
                currentProblem.revisionStatus === 'mastered'
                  ? 'bg-emerald-900/60 text-emerald-300 font-semibold shadow'
                  : 'text-slate-400 hover:text-emerald-300'
              }`}
              title="Mark Mastered"
            >
              <CheckCircle2 className="w-3 h-3 text-emerald-400" />
              <span className="hidden sm:inline">Mastered</span>
            </button>
          </div>
        </div>
      </div>

      {/* Problem Title & External Link */}
      <div className="flex items-start justify-between gap-4">
        <h3 className="text-lg font-bold text-white tracking-tight flex items-center gap-2">
          <span>{currentProblem.title}</span>
        </h3>

        {currentProblem.url && (
          <a
            href={currentProblem.url}
            target="_blank"
            rel="noopener noreferrer"
            className="flex items-center space-x-1 text-xs text-blue-400 hover:text-blue-300 bg-blue-950/40 hover:bg-blue-900/50 border border-blue-900/50 px-2.5 py-1 rounded-lg transition shrink-0"
          >
            <span>Solve</span>
            <ExternalLink className="w-3 h-3" />
          </a>
        )}
      </div>

      {/* Collapsible Problem Statement */}
      <div className="rounded-xl border border-slate-800/80 bg-slate-900/40 overflow-hidden">
        <button
          onClick={() => setShowStatement(!showStatement)}
          className="w-full flex items-center justify-between px-4 py-2.5 bg-slate-900/70 hover:bg-slate-800/50 text-xs font-semibold text-slate-300 transition"
        >
          <div className="flex items-center space-x-2">
            <BookOpen className="w-3.5 h-3.5 text-blue-400" />
            <span>Problem Description</span>
          </div>
          <div className="flex items-center space-x-1 text-slate-400">
            <span>{showStatement ? 'Collapse' : 'Expand'}</span>
            {showStatement ? <ChevronUp className="w-3.5 h-3.5" /> : <ChevronDown className="w-3.5 h-3.5" />}
          </div>
        </button>

        {showStatement && (
          <div className="p-4 text-xs text-slate-300 leading-relaxed border-t border-slate-800/80 bg-slate-950/40">
            {currentProblem.description ? (
              <div
                className="prose prose-invert prose-xs max-w-none space-y-2"
                dangerouslySetInnerHTML={{ __html: currentProblem.description }}
              />
            ) : (
              <p className="text-slate-500 italic">No description provided in problem archive.</p>
            )}
          </div>
        )}
      </div>

      {/* Code Solution Section */}
      {currentProblem.solutions && currentProblem.solutions.length > 0 && (
        <div className="space-y-2">
          <div className="flex items-center justify-between">
            <button
              onClick={() => setShowCode(!showCode)}
              className="flex items-center space-x-1.5 text-xs font-semibold text-slate-300 hover:text-white transition"
            >
              <Code2 className="w-3.5 h-3.5 text-emerald-400" />
              <span>Solution Code ({currentProblem.solutions[0]?.lang.toUpperCase() || 'C++'})</span>
              {showCode ? <ChevronUp className="w-3 h-3 text-slate-400" /> : <ChevronDown className="w-3 h-3 text-slate-400" />}
            </button>
          </div>

          {showCode && (
            <CodeViewer
              code={currentProblem.solutions[0]?.code || ''}
              lang={currentProblem.solutions[0]?.lang || 'cpp'}
              filename={currentProblem.solutions[0]?.filename}
              defaultExpanded={false}
            />
          )}
        </div>
      )}

      {/* AI Explanation Box */}
      <div className="space-y-2">
        <div className="flex items-center justify-between">
          <button
            onClick={() => setShowAI(!showAI)}
            className="flex items-center space-x-1.5 text-xs font-semibold text-indigo-300 hover:text-indigo-200 transition"
          >
            <Sparkles className="w-3.5 h-3.5 text-indigo-400" />
            <span>AI Revision Explanation (Intuition, ELI5, Complexity, Hints)</span>
            {showAI ? <ChevronUp className="w-3 h-3 text-slate-400" /> : <ChevronDown className="w-3 h-3 text-slate-400" />}
          </button>
        </div>

        {showAI && (
          <AIExplanationBox
            problem={currentProblem}
            onOpenSettings={onOpenSettings}
            onExplanationUpdated={handleExplanationUpdated}
          />
        )}
      </div>

      {/* Personal Revision Notes Collapsible */}
      <div className="pt-2 border-t border-slate-800/60">
        <div className="flex items-center justify-between mb-1.5">
          <label className="text-[11px] font-medium text-slate-400 flex items-center space-x-1">
            <span>📝 Personal Revision Note:</span>
            {notesSavedAlert && <span className="text-emerald-400 font-semibold ml-2">✓ Saved</span>}
          </label>
          <button
            onClick={savePersonalNotes}
            disabled={isSavingNotes}
            className="flex items-center space-x-1 text-[11px] px-2 py-0.5 rounded bg-slate-800 hover:bg-slate-700 text-slate-300 transition"
          >
            <Save className="w-3 h-3" />
            <span>{isSavingNotes ? 'Saving...' : 'Save Note'}</span>
          </button>
        </div>
        <textarea
          rows={2}
          value={notes}
          onChange={(e) => setNotes(e.target.value)}
          placeholder="Jot down notes (e.g. key invariant, edge case on n=0, tricky pointer update)..."
          className="w-full text-xs p-2.5 rounded-lg bg-slate-900/90 border border-slate-800 text-slate-200 placeholder-slate-600 focus:outline-none focus:border-indigo-500 transition resize-y font-sans"
        />
      </div>
    </article>
  );
};
