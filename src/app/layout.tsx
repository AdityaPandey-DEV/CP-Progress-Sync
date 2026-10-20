import type { Metadata } from 'next';
import './globals.css';

export const metadata: Metadata = {
  title: 'Competitive Programming — AI Revision Hub & Code Archive',
  description: 'Continuous revision feed with AI-powered intuition, step-by-step algorithms, complexities, hints, and pitfalls for 600+ LeetCode & Codeforces problems.',
  keywords: [
    'Competitive Programming',
    'LeetCode Solutions',
    'Codeforces Solutions',
    'AI Explanation',
    'Groq',
    'Gemini Flash',
    'Algorithm Revision',
    'Data Structures',
  ],
  authors: [{ name: 'Aditya Pandey' }],
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en" className="dark">
      <body className="min-h-screen bg-[#090d16] text-slate-100 antialiased selection:bg-indigo-500 selection:text-white">
        {children}
      </body>
    </html>
  );
}
