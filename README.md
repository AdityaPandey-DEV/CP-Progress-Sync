# CP Progress Sync

**Automated competitive programming tracker — LeetCode, Codeforces, & GFG sync with dynamic markdown dashboards.**

![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![GitHub Actions](https://img.shields.io/badge/GitHub_Actions-2088FF?style=flat-square&logo=githubactions&logoColor=white)

---

## What It Does

Automates the tracking of competitive programming progress across multiple platforms, generating dynamic markdown dashboards and auto-committing daily progress snapshots via GitHub Actions.

**Key Features:**
- **Multi-platform sync** — LeetCode, Codeforces, GeeksforGeeks
- **Automated workflows** — GitHub Actions cron jobs for daily updates
- **Dynamic dashboard** — markdown generator with live stats
- **Solution archive** — categorized C++ solutions and learning notes

## Architecture

```
GitHub Actions (Cron) → Scrape/API Fetch (LeetCode, CF, GFG)
                              ↓
                      Markdown Generator
                              ↓
                      Git Commit & Push
```

## Tech Stack

| Component | Technology |
|---|---|
| Solutions | C++ |
| Automation | GitHub Actions |
| Scripts | Shell scripting |
| Output | Markdown |

## My Role

I designed the multi-platform sync strategy, planned the GitHub Actions schedule, and structured the solution repository. Code generation was accelerated using AI tools; handling API limits and git auto-commit workflows is mine.

## Quick Start

```bash
git clone https://github.com/AdityaPandey-DEV/CP-Progress-Sync.git && cd CP-Progress-Sync
# Workflows run automatically via .github/workflows/
```

---

<div align="center">

*Architected & built by [Aditya Pandey](https://github.com/AdityaPandey-DEV) — AI-augmented development*

</div>
