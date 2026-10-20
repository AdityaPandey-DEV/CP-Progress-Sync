import { Problem, AIExplanation } from '@/types';
import { GoogleGenAI } from '@google/genai';
import Groq from 'groq-sdk';

export interface GenerateExplanationParams {
  problem: Problem;
  provider?: 'gemini' | 'groq';
  apiKey?: string;
  model?: string;
  customPrompt?: string;
}

function cleanHtmlToText(html: string): string {
  if (!html) return '';
  return html
    .replace(/<[^>]*>/g, ' ')
    .replace(/&nbsp;/g, ' ')
    .replace(/&lt;/g, '<')
    .replace(/&gt;/g, '>')
    .replace(/&amp;/g, '&')
    .replace(/&quot;/g, '"')
    .replace(/\s+/g, ' ')
    .trim();
}

function buildSystemPrompt(problem: Problem, customPrompt?: string): string {
  const code = problem.solutions[0]?.code || '// Solution in repo';
  const plainDesc = cleanHtmlToText(problem.description);

  return `You are a world-class Competitive Programming Master and expert algorithms educator.
Your mission is to explain this coding problem and its solution in an intuitive, crystal-clear, and memorable way so the student can revise and master it.

Problem: "${problem.title}" (${problem.platform})
Difficulty: ${problem.difficulty}
Topic: ${problem.topic}
Pattern: ${problem.pattern}

Problem Statement:
${plainDesc.slice(0, 1500)}

Actual Solution Code (C++):
\`\`\`cpp
${code.slice(0, 2000)}
\`\`\`

${customPrompt ? `Special Student Instruction: "${customPrompt}"` : ''}

You MUST return ONLY a valid JSON object with the following structure (no other markdown or text outside JSON):
{
  "intuition": "Deep intuitive mental model. Why does this approach make sense? What insight unlocks it?",
  "eli5": "Explain Like I'm 5 analogy using a real-world concept (e.g. library books, train tracks, flashlight).",
  "algorithmSteps": [
    "Step 1: ...",
    "Step 2: ...",
    "Step 3: ..."
  ],
  "timeComplexity": "O(...) - explain why",
  "spaceComplexity": "O(...) - explain why",
  "hints": [
    "Hint 1 (Gentle nudge about the pattern)...",
    "Hint 2 (Specific observation about state/invariants)...",
    "Hint 3 (Final piece to assemble the algorithm)..."
  ],
  "pitfalls": [
    "Pitfall 1 (e.g., integer overflow with long long)",
    "Pitfall 2 (e.g., edge cases like empty array, single element, negative numbers)",
    "Pitfall 3 (e.g., off-by-one or pointer bounds)"
  ],
  "codeWalkthrough": "Concise step-by-step breakdown of how the C++ code executes each phase of the algorithm."
}`;
}

export async function generateExplanationWithGemini(
  problem: Problem,
  apiKey: string,
  modelName = 'gemini-2.0-flash',
  customPrompt?: string
): Promise<AIExplanation> {
  const ai = new GoogleGenAI({ apiKey });
  const prompt = buildSystemPrompt(problem, customPrompt);

  const response = await ai.models.generateContent({
    model: modelName,
    contents: prompt,
    config: {
      responseMimeType: 'application/json',
      temperature: 0.2,
    },
  });

  const text = response.text?.trim() || '{}';
  const parsed = JSON.parse(text);

  return {
    intuition: parsed.intuition || 'Core insight into this problem.',
    eli5: parsed.eli5 || 'Simple real-world analogy.',
    algorithmSteps: Array.isArray(parsed.algorithmSteps) ? parsed.algorithmSteps : [],
    timeComplexity: parsed.timeComplexity || 'O(N)',
    spaceComplexity: parsed.spaceComplexity || 'O(1)',
    hints: Array.isArray(parsed.hints) ? parsed.hints : [],
    pitfalls: Array.isArray(parsed.pitfalls) ? parsed.pitfalls : [],
    codeWalkthrough: parsed.codeWalkthrough || '',
    generatedBy: 'gemini',
    generatedAt: new Date().toISOString(),
    model: modelName,
  };
}

export async function generateExplanationWithGroq(
  problem: Problem,
  apiKey: string,
  modelName = 'llama-3.3-70b-versatile',
  customPrompt?: string
): Promise<AIExplanation> {
  const groq = new Groq({ apiKey });
  const prompt = buildSystemPrompt(problem, customPrompt);

  const completion = await groq.chat.completions.create({
    messages: [
      {
        role: 'system',
        content: 'You are an expert competitive programming tutor. Return strictly valid JSON with no markdown wrapping.',
      },
      {
        role: 'user',
        content: prompt,
      },
    ],
    model: modelName,
    temperature: 0.2,
    response_format: { type: 'json_object' },
  });

  const content = completion.choices[0]?.message?.content?.trim() || '{}';
  const parsed = JSON.parse(content);

  return {
    intuition: parsed.intuition || 'Core insight into this problem.',
    eli5: parsed.eli5 || 'Simple real-world analogy.',
    algorithmSteps: Array.isArray(parsed.algorithmSteps) ? parsed.algorithmSteps : [],
    timeComplexity: parsed.timeComplexity || 'O(N)',
    spaceComplexity: parsed.spaceComplexity || 'O(1)',
    hints: Array.isArray(parsed.hints) ? parsed.hints : [],
    pitfalls: Array.isArray(parsed.pitfalls) ? parsed.pitfalls : [],
    codeWalkthrough: parsed.codeWalkthrough || '',
    generatedBy: 'groq',
    generatedAt: new Date().toISOString(),
    model: modelName,
  };
}

export async function generateAIExplanation(params: GenerateExplanationParams): Promise<AIExplanation> {
  const { problem, provider = 'gemini', apiKey, model, customPrompt } = params;

  // Resolve key from param or env
  const geminiKey = apiKey || process.env.GEMINI_API_KEY;
  const groqKey = apiKey || process.env.GROQ_API_KEY;

  if (provider === 'gemini') {
    if (!geminiKey) {
      throw new Error('Gemini API key is missing. Please provide it in Settings or set GEMINI_API_KEY in your environment.');
    }
    return await generateExplanationWithGemini(
      problem,
      geminiKey,
      model || 'gemini-2.0-flash',
      customPrompt
    );
  } else {
    if (!groqKey) {
      throw new Error('Groq API key is missing. Please provide it in Settings or set GROQ_API_KEY in your environment.');
    }
    return await generateExplanationWithGroq(
      problem,
      groqKey,
      model || 'llama-3.3-70b-versatile',
      customPrompt
    );
  }
}
