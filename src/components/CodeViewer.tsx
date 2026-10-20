'use client';

import React, { useState } from 'react';
import { Check, Copy, ChevronDown, ChevronUp, Code2 } from 'lucide-react';

interface CodeViewerProps {
  code: string;
  lang?: string;
  filename?: string;
  maxHeight?: string;
  defaultExpanded?: boolean;
}

export const CodeViewer: React.FC<CodeViewerProps> = ({
  code,
  lang = 'cpp',
  filename,
  defaultExpanded = true,
}) => {
  const [copied, setCopied] = useState(false);
  const [isExpanded, setIsExpanded] = useState(defaultExpanded);

  const handleCopy = async () => {
    try {
      await navigator.clipboard.writeText(code);
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    } catch (e) {
      console.error('Copy failed:', e);
    }
  };

  const lines = code.trim().split('\n');
  const displayLines = isExpanded ? lines : lines.slice(0, 10);

  // Syntax highlighting for C++ code
  const highlightCpp = (line: string) => {
    const tokens: React.ReactNode[] = [];
    // Basic tokenizer for C++
    const regex = /(\/\/.*$|\/\*[\s\S]*?\*\/|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\b(?:int|long|double|float|char|bool|void|auto|string|vector|set|map|unordered_map|unordered_set|queue|stack|pair|priority_queue)\b|\b(?:class|struct|public|private|protected|template|typename|return|if|else|for|while|do|switch|case|break|continue|const|static|new|delete|namespace|using|std)\b|\b\d+\b|[{}()[\];,.<>+\-*\/%=!&|^~?:])/g;

    let lastIndex = 0;
    let match;

    while ((match = regex.exec(line)) !== null) {
      if (match.index > lastIndex) {
        tokens.push(line.substring(lastIndex, match.index));
      }

      const matchText = match[0];

      if (matchText.startsWith('//') || matchText.startsWith('/*')) {
        tokens.push(<span key={match.index} className="text-slate-500 italic">{matchText}</span>);
      } else if (matchText.startsWith('"') || matchText.startsWith("'")) {
        tokens.push(<span key={match.index} className="text-emerald-400">{matchText}</span>);
      } else if (['int', 'long', 'double', 'float', 'char', 'bool', 'void', 'auto', 'string', 'vector', 'set', 'map', 'unordered_map', 'unordered_set', 'queue', 'stack', 'pair', 'priority_queue'].includes(matchText)) {
        tokens.push(<span key={match.index} className="text-amber-400 font-medium">{matchText}</span>);
      } else if (['class', 'struct', 'public', 'private', 'protected', 'template', 'typename', 'return', 'if', 'else', 'for', 'while', 'do', 'switch', 'case', 'break', 'continue', 'const', 'static', 'new', 'delete', 'namespace', 'using', 'std'].includes(matchText)) {
        tokens.push(<span key={match.index} className="text-purple-400 font-semibold">{matchText}</span>);
      } else if (/^\d+$/.test(matchText)) {
        tokens.push(<span key={match.index} className="text-cyan-400">{matchText}</span>);
      } else if (['{', '}', '(', ')', '[', ']'].includes(matchText)) {
        tokens.push(<span key={match.index} className="text-sky-300 font-bold">{matchText}</span>);
      } else {
        tokens.push(<span key={match.index} className="text-slate-300">{matchText}</span>);
      }

      lastIndex = regex.lastIndex;
    }

    if (lastIndex < line.length) {
      tokens.push(line.substring(lastIndex));
    }

    return tokens.length > 0 ? tokens : line;
  };

  return (
    <div className="rounded-xl overflow-hidden border border-slate-800 bg-[#070b12] shadow-inner text-sm">
      {/* Header Bar */}
      <div className="flex items-center justify-between px-4 py-2.5 bg-slate-900/90 border-b border-slate-800/80">
        <div className="flex items-center space-x-2">
          <div className="flex space-x-1.5 mr-2">
            <span className="w-2.5 h-2.5 rounded-full bg-rose-500/80 inline-block"></span>
            <span className="w-2.5 h-2.5 rounded-full bg-amber-500/80 inline-block"></span>
            <span className="w-2.5 h-2.5 rounded-full bg-emerald-500/80 inline-block"></span>
          </div>
          <Code2 className="w-3.5 h-3.5 text-blue-400" />
          <span className="text-xs font-mono text-slate-400">
            {filename || `solution.${lang}`}
          </span>
          <span className="text-[10px] px-1.5 py-0.5 rounded bg-blue-950/60 text-blue-400 border border-blue-800/50 uppercase font-semibold">
            {lang}
          </span>
        </div>

        <div className="flex items-center space-x-2">
          <button
            onClick={handleCopy}
            className="flex items-center space-x-1 text-xs px-2.5 py-1 rounded-md bg-slate-800 hover:bg-slate-700 text-slate-300 hover:text-white transition"
            title="Copy code"
          >
            {copied ? (
              <>
                <Check className="w-3.5 h-3.5 text-emerald-400" />
                <span className="text-emerald-400 font-medium">Copied</span>
              </>
            ) : (
              <>
                <Copy className="w-3.5 h-3.5" />
                <span>Copy</span>
              </>
            )}
          </button>
        </div>
      </div>

      {/* Code Area */}
      <div className="p-3 font-mono text-xs leading-relaxed overflow-x-auto select-text">
        <div className="table w-full">
          {displayLines.map((line, idx) => (
            <div key={idx} className="table-row hover:bg-slate-800/30">
              <span className="table-cell select-none pr-4 text-right text-slate-600 text-[11px] w-8">
                {idx + 1}
              </span>
              <span className="table-cell whitespace-pre text-slate-200">
                {highlightCpp(line) || ' '}
              </span>
            </div>
          ))}
        </div>
      </div>

      {/* Expand/Collapse Toggle if long */}
      {lines.length > 10 && (
        <div className="px-4 py-1.5 bg-slate-900/60 border-t border-slate-800/60 flex justify-center">
          <button
            onClick={() => setIsExpanded(!isExpanded)}
            className="text-xs text-slate-400 hover:text-slate-200 flex items-center space-x-1 transition"
          >
            {isExpanded ? (
              <>
                <ChevronUp className="w-3.5 h-3.5" />
                <span>Collapse code ({lines.length} lines)</span>
              </>
            ) : (
              <>
                <ChevronDown className="w-3.5 h-3.5" />
                <span>Show full code ({lines.length} lines)</span>
              </>
            )}
          </button>
        </div>
      )}
    </div>
  );
};
