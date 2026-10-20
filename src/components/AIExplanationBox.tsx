'use client';

import React, { useState } from 'react';
import { AIExplanation, Problem } from '@/types';
import {
  Sparkles,
  Lightbulb,
  Footprints,
  Clock,
  AlertTriangle,
  FileCode2,
  RefreshCw,
  Eye,
  EyeOff,
  Bot,
  Zap,
} from 'lucide-react';

interface AIExplanationBoxProps {
  problem: Problem;
  onOpenSettings?: () => void;
  onExplanationUpdated?: (newExplanation: AIExplanation) => void;
}

export const AIExplanationBox: React.FC<AIExplanationBoxProps> = ({
  problem,
  onOpenSettings,
  onExplanationUpdated,
}) => {
  const [activeTab, setActiveTab] = useState<'intuition' | 'algorithm' | 'complexity' | 'hints' | 'pitfalls' | 'walkthrough'>('intuition');
  const [revealedHints, setRevealedHints] = useState<Record<number, boolean>>({});
  const [isGenerating, setIsGenerating] = useState(false);
  const [errorMsg, setErrorMsg] = useState<string | null>(null);

  const explanation = problem.aiExplanation;

  const toggleHint = (index: number) => {
    setRevealedHints(prev => ({ ...prev, [index]: !prev[index] }));
  };

  const handleRegenerate = async (provider: 'gemini' | 'groq' = 'gemini', customPrompt?: string) => {
    setIsGenerating(true);
    setErrorMsg(null);

    // Retrieve saved keys from localStorage if present
    const geminiKey = typeof window !== 'undefined' ? localStorage.getItem('gemini_api_key') || undefined : undefined;
    const groqKey = typeof window !== 'undefined' ? localStorage.getItem('groq_api_key') || undefined : undefined;
    const apiKey = provider === 'gemini' ? geminiKey : groqKey;

    try {
      const res = await fetch('/api/explain', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          problemId: problem.problemId || problem.slug || problem.id,
          provider,
          forceRegenerate: true,
          userApiKey: apiKey,
          customPrompt,
        }),
      });

      const data = await res.json();

      if (!res.ok) {
        throw new Error(data.error || 'Failed to generate explanation');
      }

      if (data.explanation && onExplanationUpdated) {
        onExplanationUpdated(data.explanation);
      }
    } catch (err) {
      console.error(err);
      setErrorMsg((err as Error).message);
    } finally {
      setIsGenerating(false);
    }
  };

  if (!explanation && !isGenerating) {
    return (
      <div className="rounded-xl border border-dashed border-slate-700/80 p-6 bg-slate-900/40 text-center">
        <Sparkles className="w-8 h-8 text-indigo-400 mx-auto mb-2 animate-pulse" />
        <h4 className="text-sm font-semibold text-slate-200">No AI Explanation Generated Yet</h4>
        <p className="text-xs text-slate-400 max-w-md mx-auto mt-1 mb-4">
          Generate an intuitive step-by-step mental model, ELI5 analogy, complexity breakdown, and hints using free Gemini or Groq API.
        </p>
        <div className="flex items-center justify-center space-x-3">
          <button
            onClick={() => handleRegenerate('gemini')}
            className="flex items-center space-x-1.5 px-3.5 py-1.5 rounded-lg bg-indigo-600 hover:bg-indigo-500 text-white text-xs font-medium transition shadow-lg shadow-indigo-600/20"
          >
            <Bot className="w-3.5 h-3.5" />
            <span>Generate with Gemini</span>
          </button>
          <button
            onClick={() => handleRegenerate('groq')}
            className="flex items-center space-x-1.5 px-3.5 py-1.5 rounded-lg bg-orange-600 hover:bg-orange-500 text-white text-xs font-medium transition shadow-lg shadow-orange-600/20"
          >
            <Zap className="w-3.5 h-3.5" />
            <span>Generate with Groq</span>
          </button>
        </div>
      </div>
    );
  }

  return (
    <div className="rounded-xl border border-indigo-950/60 bg-gradient-to-b from-slate-900/90 to-slate-950/90 shadow-xl overflow-hidden">
      {/* Header Bar */}
      <div className="px-4 py-3 bg-slate-900/90 border-b border-indigo-950/60 flex flex-wrap items-center justify-between gap-2">
        <div className="flex items-center space-x-2">
          <div className="p-1 rounded-md bg-indigo-500/20 text-indigo-400">
            <Sparkles className="w-4 h-4" />
          </div>
          <span className="text-xs font-semibold tracking-wide text-slate-200 uppercase">
            AI Revision Master
          </span>
          {explanation?.generatedBy && (
            <span className="text-[10px] px-2 py-0.5 rounded-full bg-slate-800 text-slate-300 border border-slate-700/60 font-mono">
              {explanation.generatedBy === 'gemini' ? '✨ Gemini' : explanation.generatedBy === 'groq' ? '⚡ Groq' : '📦 Seed'}
            </span>
          )}
        </div>

        {/* Action Controls */}
        <div className="flex items-center space-x-2">
          <button
            disabled={isGenerating}
            onClick={() => handleRegenerate('gemini')}
            className="flex items-center space-x-1 text-xs px-2.5 py-1 rounded-md bg-indigo-950/80 hover:bg-indigo-900/80 text-indigo-300 border border-indigo-800/40 transition disabled:opacity-50"
            title="Regenerate with Google Gemini"
          >
            <RefreshCw className={`w-3 h-3 ${isGenerating ? 'animate-spin' : ''}`} />
            <span>{isGenerating ? 'Thinking...' : 'Regenerate'}</span>
          </button>

          <button
            disabled={isGenerating}
            onClick={() => handleRegenerate('groq')}
            className="flex items-center space-x-1 text-xs px-2.5 py-1 rounded-md bg-orange-950/60 hover:bg-orange-900/60 text-orange-300 border border-orange-800/40 transition disabled:opacity-50"
            title="Fast regeneration with Groq LLaMA 3.3"
          >
            <Zap className="w-3 h-3" />
            <span>Groq</span>
          </button>
        </div>
      </div>

      {/* Error alert if missing key */}
      {errorMsg && (
        <div className="p-3 bg-rose-950/50 border-b border-rose-900/50 flex items-center justify-between text-xs text-rose-300">
          <div className="flex items-center space-x-2">
            <AlertTriangle className="w-4 h-4 text-rose-400 shrink-0" />
            <span>{errorMsg}</span>
          </div>
          {onOpenSettings && (
            <button
              onClick={onOpenSettings}
              className="px-2 py-0.5 rounded bg-rose-900/60 hover:bg-rose-800 text-rose-200 underline font-medium"
            >
              Add API Key
            </button>
          )}
        </div>
      )}

      {/* Tabs */}
      <div className="flex border-b border-slate-800/80 px-2 overflow-x-auto text-xs bg-slate-950/40">
        <button
          onClick={() => setActiveTab('intuition')}
          className={`flex items-center space-x-1.5 py-2.5 px-3 border-b-2 font-medium transition whitespace-nowrap ${
            activeTab === 'intuition'
              ? 'border-indigo-500 text-indigo-400'
              : 'border-transparent text-slate-400 hover:text-slate-200'
          }`}
        >
          <Lightbulb className="w-3.5 h-3.5" />
          <span>Intuition & ELI5</span>
        </button>

        <button
          onClick={() => setActiveTab('algorithm')}
          className={`flex items-center space-x-1.5 py-2.5 px-3 border-b-2 font-medium transition whitespace-nowrap ${
            activeTab === 'algorithm'
              ? 'border-indigo-500 text-indigo-400'
              : 'border-transparent text-slate-400 hover:text-slate-200'
          }`}
        >
          <Footprints className="w-3.5 h-3.5" />
          <span>Step-by-Step</span>
        </button>

        <button
          onClick={() => setActiveTab('complexity')}
          className={`flex items-center space-x-1.5 py-2.5 px-3 border-b-2 font-medium transition whitespace-nowrap ${
            activeTab === 'complexity'
              ? 'border-indigo-500 text-indigo-400'
              : 'border-transparent text-slate-400 hover:text-slate-200'
          }`}
        >
          <Clock className="w-3.5 h-3.5" />
          <span>Complexity</span>
        </button>

        <button
          onClick={() => setActiveTab('hints')}
          className={`flex items-center space-x-1.5 py-2.5 px-3 border-b-2 font-medium transition whitespace-nowrap ${
            activeTab === 'hints'
              ? 'border-indigo-500 text-indigo-400'
              : 'border-transparent text-slate-400 hover:text-slate-200'
          }`}
        >
          <Eye className="w-3.5 h-3.5" />
          <span>Revision Hints</span>
        </button>

        <button
          onClick={() => setActiveTab('pitfalls')}
          className={`flex items-center space-x-1.5 py-2.5 px-3 border-b-2 font-medium transition whitespace-nowrap ${
            activeTab === 'pitfalls'
              ? 'border-indigo-500 text-indigo-400'
              : 'border-transparent text-slate-400 hover:text-slate-200'
          }`}
        >
          <AlertTriangle className="w-3.5 h-3.5" />
          <span>Traps & Pitfalls</span>
        </button>

        {explanation?.codeWalkthrough && (
          <button
            onClick={() => setActiveTab('walkthrough')}
            className={`flex items-center space-x-1.5 py-2.5 px-3 border-b-2 font-medium transition whitespace-nowrap ${
              activeTab === 'walkthrough'
                ? 'border-indigo-500 text-indigo-400'
                : 'border-transparent text-slate-400 hover:text-slate-200'
            }`}
          >
            <FileCode2 className="w-3.5 h-3.5" />
            <span>Code Walkthrough</span>
          </button>
        )}
      </div>

      {/* Tab Content Body */}
      <div className="p-4 text-xs leading-relaxed text-slate-300">
        {isGenerating ? (
          <div className="space-y-3 py-6 text-center animate-pulse">
            <Sparkles className="w-7 h-7 text-indigo-400 mx-auto animate-spin" />
            <p className="text-slate-400 text-xs">Consulting AI for the clearest intuition and breakdown...</p>
          </div>
        ) : (
          <>
            {/* INTUITION & ELI5 */}
            {activeTab === 'intuition' && (
              <div className="space-y-4">
                <div className="p-3 rounded-lg bg-indigo-950/30 border border-indigo-900/40">
                  <div className="flex items-center space-x-1.5 text-indigo-300 font-semibold mb-1">
                    <Lightbulb className="w-3.5 h-3.5" />
                    <span>Core Intuition</span>
                  </div>
                  <p className="text-slate-200">{explanation?.intuition}</p>
                </div>

                {explanation?.eli5 && (
                  <div className="p-3 rounded-lg bg-amber-950/20 border border-amber-900/30">
                    <div className="flex items-center space-x-1.5 text-amber-300 font-semibold mb-1">
                      <span>🧒 Explain Like I&apos;m 5 (Analogy)</span>
                    </div>
                    <p className="text-slate-300 italic">{explanation.eli5}</p>
                  </div>
                )}
              </div>
            )}

            {/* ALGORITHM STEPS */}
            {activeTab === 'algorithm' && (
              <div className="space-y-2.5">
                <p className="text-slate-400 mb-2">Step-by-step approach to solve this problem:</p>
                {explanation?.algorithmSteps && explanation.algorithmSteps.length > 0 ? (
                  <ol className="space-y-2">
                    {explanation.algorithmSteps.map((step, idx) => (
                      <li key={idx} className="flex items-start space-x-2.5 p-2 rounded-lg bg-slate-900/60 border border-slate-800/60">
                        <span className="flex items-center justify-center w-5 h-5 rounded-full bg-indigo-900/80 text-indigo-300 text-[11px] font-bold shrink-0 mt-0.5">
                          {idx + 1}
                        </span>
                        <span className="text-slate-200">{step}</span>
                      </li>
                    ))}
                  </ol>
                ) : (
                  <p className="text-slate-500">No steps recorded.</p>
                )}
              </div>
            )}

            {/* COMPLEXITY */}
            {activeTab === 'complexity' && (
              <div className="grid grid-cols-1 md:grid-cols-2 gap-3">
                <div className="p-3 rounded-lg bg-slate-900/80 border border-slate-800">
                  <div className="flex items-center justify-between mb-1">
                    <span className="text-slate-400 font-medium">Time Complexity</span>
                    <span className="px-2 py-0.5 rounded bg-emerald-950/80 text-emerald-400 border border-emerald-800/40 font-mono font-bold">
                      {explanation?.timeComplexity.split(' ')[0] || 'O(N)'}
                    </span>
                  </div>
                  <p className="text-slate-300 text-[11px] mt-1.5">{explanation?.timeComplexity}</p>
                </div>

                <div className="p-3 rounded-lg bg-slate-900/80 border border-slate-800">
                  <div className="flex items-center justify-between mb-1">
                    <span className="text-slate-400 font-medium">Space Complexity</span>
                    <span className="px-2 py-0.5 rounded bg-blue-950/80 text-blue-400 border border-blue-800/40 font-mono font-bold">
                      {explanation?.spaceComplexity.split(' ')[0] || 'O(1)'}
                    </span>
                  </div>
                  <p className="text-slate-300 text-[11px] mt-1.5">{explanation?.spaceComplexity}</p>
                </div>
              </div>
            )}

            {/* HINTS FOR ACTIVE RECALL */}
            {activeTab === 'hints' && (
              <div className="space-y-2.5">
                <div className="flex items-center justify-between mb-2">
                  <p className="text-slate-400 text-xs">
                    Reveal hints progressively to test your active recall:
                  </p>
                  <button
                    onClick={() => {
                      const allRevealed = Object.keys(revealedHints).length === (explanation?.hints.length || 0);
                      if (allRevealed) {
                        setRevealedHints({});
                      } else {
                        const newHints: Record<number, boolean> = {};
                        (explanation?.hints || []).forEach((_, i) => (newHints[i] = true));
                        setRevealedHints(newHints);
                      }
                    }}
                    className="text-[11px] text-indigo-400 hover:text-indigo-300 underline"
                  >
                    {Object.keys(revealedHints).length === (explanation?.hints.length || 0) ? 'Hide All' : 'Reveal All'}
                  </button>
                </div>

                {explanation?.hints && explanation.hints.length > 0 ? (
                  explanation.hints.map((hint, idx) => {
                    const isRevealed = Boolean(revealedHints[idx]);
                    return (
                      <div
                        key={idx}
                        className={`rounded-lg border p-3 transition cursor-pointer ${
                          isRevealed
                            ? 'bg-indigo-950/20 border-indigo-900/40 text-slate-200'
                            : 'bg-slate-900/40 border-slate-800 text-slate-500 hover:bg-slate-900/80'
                        }`}
                        onClick={() => toggleHint(idx)}
                      >
                        <div className="flex items-center justify-between">
                          <span className="font-semibold text-slate-400 text-xs">Hint {idx + 1}</span>
                          <span className="flex items-center space-x-1 text-[11px] text-indigo-400">
                            {isRevealed ? <EyeOff className="w-3 h-3" /> : <Eye className="w-3 h-3" />}
                            <span>{isRevealed ? 'Hide' : 'Reveal hint'}</span>
                          </span>
                        </div>
                        {isRevealed ? (
                          <p className="mt-2 text-xs text-indigo-200">{hint}</p>
                        ) : (
                          <p className="mt-1 text-[11px] italic text-slate-500">Click to reveal clue...</p>
                        )}
                      </div>
                    );
                  })
                ) : (
                  <p className="text-slate-500">No hints available.</p>
                )}
              </div>
            )}

            {/* PITFALLS */}
            {activeTab === 'pitfalls' && (
              <div className="space-y-2">
                <p className="text-slate-400 mb-2">Watch out for these common interview and contest traps:</p>
                {explanation?.pitfalls && explanation.pitfalls.length > 0 ? (
                  explanation.pitfalls.map((pitfall, idx) => (
                    <div key={idx} className="flex items-start space-x-2 p-2.5 rounded-lg bg-rose-950/20 border border-rose-900/30 text-rose-200">
                      <AlertTriangle className="w-4 h-4 text-rose-400 shrink-0 mt-0.5" />
                      <span>{pitfall}</span>
                    </div>
                  ))
                ) : (
                  <p className="text-slate-500">No pitfalls recorded.</p>
                )}
              </div>
            )}

            {/* CODE WALKTHROUGH */}
            {activeTab === 'walkthrough' && explanation?.codeWalkthrough && (
              <div className="p-3 rounded-lg bg-slate-900/80 border border-slate-800 text-slate-200 leading-relaxed whitespace-pre-line font-mono text-[11px]">
                {explanation.codeWalkthrough}
              </div>
            )}
          </>
        )}
      </div>
    </div>
  );
};
