'use client';

import React from 'react';
import {
  Code2,
  Sparkles,
  ScrollText,
  Columns2,
  Layers,
  Settings,
  Trophy,
} from 'lucide-react';

interface NavbarProps {
  viewMode: 'feed' | 'split' | 'flashcard';
  onChangeViewMode: (mode: 'feed' | 'split' | 'flashcard') => void;
  onOpenSettings: () => void;
  masteredCount: number;
  totalCount: number;
}

export const Navbar: React.FC<NavbarProps> = ({
  viewMode,
  onChangeViewMode,
  onOpenSettings,
  masteredCount,
  totalCount,
}) => {
  return (
    <header className="sticky top-0 z-40 w-full glass-panel border-b border-slate-800/80 bg-slate-950/80 backdrop-blur-md">
      <div className="max-w-7xl mx-auto px-4 sm:px-6 h-16 flex items-center justify-between gap-4">
        {/* Brand / Logo */}
        <div className="flex items-center space-x-3">
          <div className="p-2 rounded-xl bg-gradient-to-tr from-blue-600 via-indigo-600 to-purple-600 text-white shadow-lg shadow-indigo-600/30 flex items-center justify-center">
            <Code2 className="w-5 h-5" />
          </div>
          <div>
            <div className="flex items-center space-x-2">
              <span className="font-extrabold text-sm sm:text-base text-white tracking-tight">
                Competitive Programming
              </span>
              <span className="hidden sm:inline-flex text-[10px] font-bold px-2 py-0.5 rounded-full bg-indigo-950/80 text-indigo-300 border border-indigo-700/60 uppercase tracking-wider">
                AI Revision
              </span>
            </div>
            <p className="hidden md:block text-[11px] text-slate-400">
              LeetCode & Codeforces Solutions • Groq & Gemini Insights
            </p>
          </div>
        </div>

        {/* View Mode Switcher */}
        <div className="flex items-center rounded-xl bg-slate-900 border border-slate-800 p-1 text-xs">
          <button
            onClick={() => onChangeViewMode('feed')}
            className={`flex items-center space-x-1.5 px-3 py-1.5 rounded-lg font-medium transition ${
              viewMode === 'feed'
                ? 'bg-indigo-600 text-white shadow-md'
                : 'text-slate-400 hover:text-slate-200'
            }`}
            title="Continuous Feed Mode"
          >
            <ScrollText className="w-3.5 h-3.5" />
            <span className="hidden sm:inline">Continuous Feed</span>
          </button>

          <button
            onClick={() => onChangeViewMode('split')}
            className={`flex items-center space-x-1.5 px-3 py-1.5 rounded-lg font-medium transition ${
              viewMode === 'split'
                ? 'bg-indigo-600 text-white shadow-md'
                : 'text-slate-400 hover:text-slate-200'
            }`}
            title="Split Focus Mode"
          >
            <Columns2 className="w-3.5 h-3.5" />
            <span className="hidden sm:inline">Split Focus</span>
          </button>

          <button
            onClick={() => onChangeViewMode('flashcard')}
            className={`flex items-center space-x-1.5 px-3 py-1.5 rounded-lg font-medium transition ${
              viewMode === 'flashcard'
                ? 'bg-indigo-600 text-white shadow-md'
                : 'text-slate-400 hover:text-slate-200'
            }`}
            title="Flashcard Active Recall Mode"
          >
            <Layers className="w-3.5 h-3.5" />
            <span className="hidden sm:inline">Flashcards</span>
          </button>
        </div>

        {/* Right Actions: Mastery Pill, Settings, GitHub */}
        <div className="flex items-center space-x-2.5">
          {totalCount > 0 && (
            <div className="hidden lg:flex items-center space-x-1.5 px-3 py-1.5 rounded-xl bg-emerald-950/40 border border-emerald-800/40 text-emerald-400 text-xs font-semibold">
              <Trophy className="w-3.5 h-3.5" />
              <span>{masteredCount}/{totalCount} Mastered</span>
            </div>
          )}

          <button
            onClick={onOpenSettings}
            className="flex items-center space-x-1.5 px-3 py-1.5 rounded-xl bg-slate-900 hover:bg-slate-800 text-slate-300 border border-slate-800 text-xs font-medium transition"
            title="AI & Database Settings"
          >
            <Settings className="w-4 h-4 text-indigo-400" />
            <span className="hidden sm:inline">AI Settings</span>
          </button>

          <a
            href="https://github.com/AdityaPandey-DEV/CP-Progress-Sync"
            target="_blank"
            rel="noopener noreferrer"
            className="p-2 rounded-xl bg-slate-900 hover:bg-slate-800 text-slate-400 hover:text-white border border-slate-800 transition"
            title="GitHub Repository"
          >
            <svg className="w-4 h-4 fill-current" viewBox="0 0 24 24">
              <path fillRule="evenodd" clipRule="evenodd" d="M12 2C6.477 2 2 6.484 2 12.017c0 4.425 2.865 8.18 6.839 9.504.5.092.682-.217.682-.483 0-.237-.008-.868-.013-1.703-2.782.605-3.369-1.343-3.369-1.343-.454-1.158-1.11-1.466-1.11-1.466-.908-.62.069-.608.069-.608 1.003.07 1.53 1.032 1.53 1.032.892 1.53 2.341 1.088 2.91.832.092-.647.35-1.088.636-1.338-2.22-.253-4.555-1.113-4.555-4.951 0-1.093.39-1.988 1.029-2.688-.103-.253-.446-1.272.098-2.65 0 0 .84-.27 2.75 1.026A9.564 9.564 0 0112 6.844c.85.004 1.705.115 2.504.337 1.909-1.296 2.747-1.027 2.747-1.027.546 1.379.202 2.398.1 2.651.64.7 1.028 1.595 1.028 2.688 0 3.848-2.339 4.695-4.566 4.943.359.309.678.92.678 1.855 0 1.338-.012 2.419-.012 2.747 0 .268.18.58.688.482A10.019 10.019 0 0022 12.017C22 6.484 17.522 2 12 2z" />
            </svg>
          </a>
        </div>
      </div>
    </header>
  );
};
