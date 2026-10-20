'use client';

import React, { useState, useEffect } from 'react';
import {
  X,
  Sparkles,
  Database,
  ExternalLink,
  Check,
  RefreshCw,
  KeyRound,
  Zap,
  Bot,
  AlertCircle,
} from 'lucide-react';

interface AISettingsModalProps {
  isOpen: boolean;
  onClose: () => void;
}

export const AISettingsModal: React.FC<AISettingsModalProps> = ({ isOpen, onClose }) => {
  const [provider, setProvider] = useState<'gemini' | 'groq'>('gemini');
  const [geminiKey, setGeminiKey] = useState('');
  const [groqKey, setGroqKey] = useState('');
  const [geminiModel, setGeminiModel] = useState('gemini-2.0-flash');
  const [groqModel, setGroqModel] = useState('llama-3.3-70b-versatile');
  const [savedSuccess, setSavedSuccess] = useState(false);

  // Sync state
  const [isSyncing, setIsSyncing] = useState(false);
  const [syncResult, setSyncResult] = useState<string | null>(null);

  useEffect(() => {
    if (typeof window !== 'undefined') {
      setGeminiKey(localStorage.getItem('gemini_api_key') || '');
      setGroqKey(localStorage.getItem('groq_api_key') || '');
      setProvider((localStorage.getItem('default_ai_provider') as 'gemini' | 'groq') || 'gemini');
      setGeminiModel(localStorage.getItem('gemini_model') || 'gemini-2.0-flash');
      setGroqModel(localStorage.getItem('groq_model') || 'llama-3.3-70b-versatile');
    }
  }, [isOpen]);

  const handleSave = () => {
    if (typeof window !== 'undefined') {
      localStorage.setItem('gemini_api_key', geminiKey.trim());
      localStorage.setItem('groq_api_key', groqKey.trim());
      localStorage.setItem('default_ai_provider', provider);
      localStorage.setItem('gemini_model', geminiModel);
      localStorage.setItem('groq_model', groqModel);
    }
    setSavedSuccess(true);
    setTimeout(() => {
      setSavedSuccess(false);
      onClose();
    }, 1200);
  };

  const handleSyncDatabase = async () => {
    setIsSyncing(true);
    setSyncResult(null);
    try {
      const res = await fetch('/api/sync', { method: 'POST' });
      const data = await res.json();
      if (res.ok) {
        setSyncResult(data.message || 'Synced successfully with MongoDB!');
      } else {
        setSyncResult(`⚠️ ${data.error || 'Sync failed'}`);
      }
    } catch (e) {
      setSyncResult(`⚠️ ${(e as Error).message}`);
    } finally {
      setIsSyncing(false);
    }
  };

  if (!isOpen) return null;

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/75 backdrop-blur-sm animate-in fade-in duration-200">
      <div className="relative w-full max-w-xl rounded-2xl glass-panel bg-slate-900 border border-slate-700/80 p-6 shadow-2xl space-y-5 max-h-[90vh] overflow-y-auto">
        {/* Header */}
        <div className="flex items-center justify-between pb-3 border-b border-slate-800">
          <div className="flex items-center space-x-2.5">
            <div className="p-2 rounded-xl bg-indigo-600/20 text-indigo-400 border border-indigo-500/30">
              <KeyRound className="w-5 h-5" />
            </div>
            <div>
              <h3 className="text-base font-bold text-white">AI & Database Settings</h3>
              <p className="text-xs text-slate-400">Configure free API keys for Gemini & Groq, and MongoDB cache</p>
            </div>
          </div>
          <button
            onClick={onClose}
            className="p-1 rounded-lg text-slate-400 hover:text-white hover:bg-slate-800 transition"
          >
            <X className="w-5 h-5" />
          </button>
        </div>

        {/* Provider Toggle */}
        <div className="space-y-2">
          <label className="text-xs font-semibold text-slate-300">Default AI Provider</label>
          <div className="grid grid-cols-2 gap-3">
            <button
              type="button"
              onClick={() => setProvider('gemini')}
              className={`flex items-center space-x-2.5 p-3 rounded-xl border text-left transition ${
                provider === 'gemini'
                  ? 'bg-indigo-950/60 border-indigo-500 text-white shadow-md shadow-indigo-950/50'
                  : 'bg-slate-950/40 border-slate-800 text-slate-400 hover:text-slate-200'
              }`}
            >
              <Bot className="w-5 h-5 text-indigo-400 shrink-0" />
              <div>
                <div className="text-xs font-bold">Google Gemini</div>
                <div className="text-[11px] text-slate-400">Generous free tier (1500 req/day)</div>
              </div>
            </button>

            <button
              type="button"
              onClick={() => setProvider('groq')}
              className={`flex items-center space-x-2.5 p-3 rounded-xl border text-left transition ${
                provider === 'groq'
                  ? 'bg-orange-950/60 border-orange-500 text-white shadow-md shadow-orange-950/50'
                  : 'bg-slate-950/40 border-slate-800 text-slate-400 hover:text-slate-200'
              }`}
            >
              <Zap className="w-5 h-5 text-orange-400 shrink-0" />
              <div>
                <div className="text-xs font-bold">Groq (LLaMA 3.3)</div>
                <div className="text-[11px] text-slate-400">Ultra-fast inference (Free)</div>
              </div>
            </button>
          </div>
        </div>

        {/* Gemini Settings */}
        <div className="p-4 rounded-xl bg-slate-950/60 border border-slate-800 space-y-3">
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-2">
              <Bot className="w-4 h-4 text-indigo-400" />
              <span className="text-xs font-bold text-slate-200">Google Gemini API Key</span>
            </div>
            <a
              href="https://aistudio.google.com/app/apikey"
              target="_blank"
              rel="noopener noreferrer"
              className="text-[11px] text-indigo-400 hover:underline flex items-center space-x-1"
            >
              <span>Get Free Key</span>
              <ExternalLink className="w-3 h-3" />
            </a>
          </div>

          <input
            type="password"
            value={geminiKey}
            onChange={(e) => setGeminiKey(e.target.value)}
            placeholder="AIzaSy... (or set GEMINI_API_KEY in .env.local)"
            className="w-full px-3 py-2 rounded-lg bg-slate-900 border border-slate-800 text-xs text-slate-200 placeholder-slate-600 focus:outline-none focus:border-indigo-500 font-mono"
          />

          <div className="flex items-center justify-between text-xs text-slate-400">
            <span>Model:</span>
            <select
              value={geminiModel}
              onChange={(e) => setGeminiModel(e.target.value)}
              className="bg-slate-900 text-slate-200 border border-slate-800 rounded px-2 py-1 text-xs"
            >
              <option value="gemini-2.0-flash">gemini-2.0-flash (Recommended)</option>
              <option value="gemini-1.5-flash">gemini-1.5-flash</option>
              <option value="gemini-1.5-pro">gemini-1.5-pro</option>
            </select>
          </div>
        </div>

        {/* Groq Settings */}
        <div className="p-4 rounded-xl bg-slate-950/60 border border-slate-800 space-y-3">
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-2">
              <Zap className="w-4 h-4 text-orange-400" />
              <span className="text-xs font-bold text-slate-200">Groq API Key</span>
            </div>
            <a
              href="https://console.groq.com/keys"
              target="_blank"
              rel="noopener noreferrer"
              className="text-[11px] text-orange-400 hover:underline flex items-center space-x-1"
            >
              <span>Get Free Key</span>
              <ExternalLink className="w-3 h-3" />
            </a>
          </div>

          <input
            type="password"
            value={groqKey}
            onChange={(e) => setGroqKey(e.target.value)}
            placeholder="gsk_... (or set GROQ_API_KEY in .env.local)"
            className="w-full px-3 py-2 rounded-lg bg-slate-900 border border-slate-800 text-xs text-slate-200 placeholder-slate-600 focus:outline-none focus:border-orange-500 font-mono"
          />

          <div className="flex items-center justify-between text-xs text-slate-400">
            <span>Model:</span>
            <select
              value={groqModel}
              onChange={(e) => setGroqModel(e.target.value)}
              className="bg-slate-900 text-slate-200 border border-slate-800 rounded px-2 py-1 text-xs"
            >
              <option value="llama-3.3-70b-versatile">llama-3.3-70b-versatile (State-of-the-art)</option>
              <option value="llama-3.1-8b-instant">llama-3.1-8b-instant (Fastest)</option>
            </select>
          </div>
        </div>

        {/* MongoDB Database Caching Section */}
        <div className="p-4 rounded-xl bg-slate-950/60 border border-slate-800 space-y-3">
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-2">
              <Database className="w-4 h-4 text-emerald-400" />
              <span className="text-xs font-bold text-slate-200">Mongoose / MongoDB Database</span>
            </div>
            <span className="text-[10px] px-2 py-0.5 rounded bg-emerald-950/60 text-emerald-400 border border-emerald-800/40 font-mono">
              Auto-Caching
            </span>
          </div>

          <p className="text-[11px] text-slate-400 leading-relaxed">
            All AI explanations are permanently cached in MongoDB so they only generate once and are reused instantly with zero recurring cost.
            Configure <code className="text-slate-300 font-mono bg-slate-900 px-1 py-0.5 rounded">MONGODB_URI</code> in your <code className="text-slate-300 font-mono bg-slate-900 px-1 py-0.5 rounded">.env.local</code> or Vercel Environment Variables.
          </p>

          <div className="flex items-center justify-between pt-1">
            <button
              onClick={handleSyncDatabase}
              disabled={isSyncing}
              className="flex items-center space-x-1.5 px-3 py-1.5 rounded-lg bg-slate-800 hover:bg-slate-700 text-slate-200 text-xs font-medium transition disabled:opacity-50"
            >
              <RefreshCw className={`w-3.5 h-3.5 ${isSyncing ? 'animate-spin' : ''}`} />
              <span>{isSyncing ? 'Syncing...' : 'Seed / Sync MongoDB'}</span>
            </button>
          </div>

          {syncResult && (
            <div className="p-2 rounded bg-slate-900 border border-slate-800 text-[11px] text-slate-300 font-mono">
              {syncResult}
            </div>
          )}
        </div>

        {/* Footer Actions */}
        <div className="flex items-center justify-end space-x-3 pt-2 border-t border-slate-800">
          <button
            onClick={onClose}
            className="px-4 py-2 rounded-xl text-xs font-medium text-slate-400 hover:text-white transition"
          >
            Cancel
          </button>
          <button
            onClick={handleSave}
            className="flex items-center space-x-1.5 px-5 py-2 rounded-xl bg-indigo-600 hover:bg-indigo-500 text-white text-xs font-semibold shadow-lg shadow-indigo-600/30 transition"
          >
            {savedSuccess ? (
              <>
                <Check className="w-4 h-4 text-emerald-300" />
                <span>Saved!</span>
              </>
            ) : (
              <>
                <Sparkles className="w-4 h-4" />
                <span>Save Preferences</span>
              </>
            )}
          </button>
        </div>
      </div>
    </div>
  );
};
