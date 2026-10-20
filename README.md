# 🚀 Competitive Programming — AI Revision Hub & Solver Archive

> **Full-stack Next.js web application for revising 630+ LeetCode & Codeforces problems with AI-powered intuitive breakdowns, step-by-step algorithms, complexities, active recall hints, pitfalls, and Mongoose database caching.**

[![Next.js](https://img.shields.io/badge/Next.js-16.4-black?style=flat-square&logo=next.js&logoColor=white)](https://nextjs.org/)
[![React](https://img.shields.io/badge/React-19.3-blue?style=flat-square&logo=react&logoColor=white)](https://react.dev/)
[![TypeScript](https://img.shields.io/badge/TypeScript-5-blue?style=flat-square&logo=typescript&logoColor=white)](https://www.typescriptlang.org/)
[![MongoDB](https://img.shields.io/badge/MongoDB-Mongoose-green?style=flat-square&logo=mongodb&logoColor=white)](https://mongoosejs.com/)
[![Google Gemini](https://img.shields.io/badge/Gemini-2.0%20Flash-4285F4?style=flat-square&logo=google&logoColor=white)](https://aistudio.google.com/)
[![Groq](https://img.shields.io/badge/Groq-LLaMA%203.3%2070B-F05A28?style=flat-square)](https://groq.com/)
[![Vercel Ready](https://img.shields.io/badge/Deploy-Vercel-black?style=flat-square&logo=vercel&logoColor=white)](https://vercel.com/)

---

## 🌟 Key Features

1. **Continuous Revision Feed**:
   - Continuous stream of questions, problem statements, C++ solutions, and AI explanations for effortless binge-revising before contests and interviews.
2. **AI-Powered Explanations (Free Tier via Gemini & Groq)**:
   - 💡 **Core Intuition**: Mental model and underlying invariant that unlocks the problem.
   - 🧒 **ELI5 Analogy**: "Explain Like I'm 5" real-world analogy.
   - 🪜 **Step-by-Step Algorithm**: Clean recipe for writing the solution.
   - ⏱️ **Complexity Analysis**: Time and Space bounds with mathematical justifications.
   - 🎯 **Active Recall Hints**: Hidden hints revealed progressively to test your thinking.
   - ⚠️ **Traps & Common Pitfalls**: Edge cases, 0-indexing bugs, and integer overflow traps.
   - 📝 **Code Walkthrough**: Line-by-line guide of the C++ implementation.
3. **Mongoose / MongoDB Auto-Caching**:
   - Explanations are cached in MongoDB upon generation so they are never re-requested from the AI API again, ensuring $0 recurring cost and instant responses.
   - Seamless offline fallback: If MongoDB is not yet configured, the app runs smoothly with bundled seed data in memory.
4. **Pattern & Topic Categorization**:
   - Filter instantly by **17 Topics** (*Arrays & Hashing, Dynamic Programming, Two Pointers, Graphs, Trees, Binary Search, Sliding Window, etc.*).
   - Filter by **17 Algorithmic Patterns** (*Converging Pointers, Monotonic Stack, BFS/DFS, Min/Max Heap, State Transitions, etc.*).
   - Filter by **Difficulty** (*Easy, Medium, Hard*) and **Platform** (*LeetCode, Codeforces*).
5. **Interactive Revision Modes**:
   - 📜 **Continuous Feed Mode**: Continuous list of questions with code and AI tabs.
   - 🗂️ **Split Focus Mode**: Master-detail view with sidebar problem index and focused study workspace.
   - 🃏 **Active Recall Flashcards**: Question first, test yourself, reveal pattern & hints, reveal solution code, and rate yourself (*Mastered / Reviewing / Hard*).
6. **C++ Solution Viewer**:
   - Syntax-highlighted code with line numbers, copy button, and language tag.
7. **Personal Notes & Bookmarking**:
   - Add inline revision notes per question that persist to MongoDB.
   - Star favorite or tricky problems for rapid revision before interviews.

---

## 🏗️ Architecture

```
GitHub Solutions (LeetCode / CF)  ──►  Next.js Full Stack App (Vercel)
               │                                      │
               ▼                                      ▼
      Data Pre-loader / API                 API Routes & Mongoose
               │                                      │
               ├──────────────────┬───────────────────┤
               ▼                  ▼                   ▼
       MongoDB Caching      Gemini 2.0 Flash    Groq LLaMA 3.3
       (Zero Recurring       (1500 req/day       (Ultra-fast
           Cost)                 Free)              Free)
```

---

## ⚡ Quick Start (Local Development)

### Prerequisites
- Node.js 18+ (tested on Node 20 & 25)
- npm / yarn / pnpm

### 1. Clone & Install
```bash
git clone https://github.com/AdityaPandey-DEV/CP-Progress-Sync.git "Competitive Programming"
cd "Competitive Programming"
npm install
```

### 2. Configure Environment Variables (Optional)
Create `.env.local` based on `.env.example`:
```bash
cp .env.example .env.local
```

Fill in your free API keys and MongoDB connection string:
```env
MONGODB_URI=mongodb+srv://<user>:<password>@cluster0.mongodb.net/competitive-programming?retryWrites=true&w=majority
GEMINI_API_KEY=AIzaSy...
GROQ_API_KEY=gsk_...
```
*(Note: You can also input your Gemini or Groq API keys directly inside the web UI via the **AI Settings** modal!)*

### 3. Run Development Server
```bash
npm run dev
```
Open [http://localhost:3000](http://localhost:3000) in your browser.

### 4. Build for Production
```bash
npm run build
npm run start
```

---

## 🚀 Deploying to Vercel (1-Click)

1. Push your repository to GitHub (`AdityaPandey-DEV/CP-Progress-Sync` or your renamed repo `Competitive-Programming`).
2. Log into [Vercel](https://vercel.com) and click **"Add New Project"**.
3. Import your repository. Vercel will automatically detect **Next.js** at the root.
4. Add the following **Environment Variables** in project settings:
   - `MONGODB_URI`: Your MongoDB Atlas connection string.
   - `GEMINI_API_KEY`: Your free Gemini API key from [Google AI Studio](https://aistudio.google.com/app/apikey).
   - `GROQ_API_KEY`: (Optional) Free Groq API key from [Groq Console](https://console.groq.com/keys).
5. Click **Deploy**. Your competitive programming revision hub will be live with full serverless functionality!

---

## 📂 Repository Structure

```
├── leetcode/               # Categorized LeetCode C++ solutions (easy/medium/hard)
├── codeforces/             # Codeforces contest & practice solutions
├── notes/                  # Topic-wise revision markdown notes (dp, graphs, trees, etc.)
├── scripts/                # Python sync & README generator scripts
├── src/
│   ├── app/                # Next.js App Router pages and API routes
│   │   ├── api/problems/   # Filtered & paginated problem fetching
│   │   ├── api/explain/    # Gemini & Groq AI explanation generator with Mongo caching
│   │   ├── api/stats/      # Real-time mastery & difficulty statistics
│   │   ├── api/filters/    # Topics, patterns, and platform counts
│   │   ├── api/sync/       # MongoDB seed & sync endpoint
│   │   ├── page.tsx        # Main full-stack revision application
│   │   └── layout.tsx      # App layout & SEO metadata
│   ├── components/         # React UI Components (ContinuousFeed, SplitFocus, Flashcards, etc.)
│   ├── lib/                # MongoDB client, AI service (Gemini/Groq), problem data helper
│   ├── models/             # Mongoose schemas (Problem & AIExplanation)
│   ├── types/              # TypeScript definitions
│   └── data/               # Seed dataset (632 questions & solutions)
├── .env.example            # Environment variables template
├── package.json            # Dependencies and build scripts
└── README.md
```

---

<div align="center">

*Architected & built by [Aditya Pandey](https://github.com/AdityaPandey-DEV) • AI-Augmented Competitive Programming*

</div>
