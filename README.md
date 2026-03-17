<div align="center">

# 🚀 CP Progress Sync

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![GitHub Actions](https://img.shields.io/badge/GitHub%20Actions-Automated-blue.svg)](.github/workflows)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.md)

> **A powerful, automated tool to track and sync competitive programming and coding activity from platforms like LeetCode and Codeforces directly to GitHub.**

This repository is an automated, live portfolio of my problem-solving journey. It features optimized solutions in **C++** and **Python** synchronized flawlessly from top coding platforms.

---

</div>

## 📊 Live Stats & Rating Graphs

Watch my progress in real-time through these auto-updating statistic cards.

<p align="center">
  <img src="https://leetcard.jacoblin.cool/AdityaPandey-DEV?theme=dark&font=baloo&ext=activity" alt="LeetCode Stats" width="400"/>
  <img src="https://github-readme-stats.vercel.app/api?username=AdityaPandey-DEV&show_icons=true&theme=radical" alt="GitHub Stats" width="400"/>
</p>

---

## ✨ Supercharged Features

- 🤖 **Auto Commits**: Solutions are fetched and committed to this repository entirely hands-free using GitHub Actions.
- 📈 **Dynamic Dashboards**: A monthly progress dashboard tracking problems solved over time. _([View Dashboard](dashboard.md))_
- 🏆 **Multi-Platform Support**: Seamlessly syncs from **LeetCode**, **Codeforces**, and **GeeksforGeeks**.
- 📊 **Live Rating Graphs**: Embedded stats cards updating automatically with every new submission.
- 💡 **Clean Code Principles**: Every pushed solution is linted, formatted, and optimized for space and time complexity.

---

## 📂 Repository Architecture

```bash
.
├── codeforces/      # Codeforces contest solutions & explanations
├── leetcode/        # Categorized LeetCode solutions (Easy/Medium/Hard)
├── geeksforgeeks/   # GFG problem of the day and practice solutions
├── scripts/         # Engine: Python scripts powering the dashboard & stats
└── .github/         # CI/CD: Automated Sync & Linting workflows
```

---

## 🚀 Quick Setup & Usage

To explore the solutions or run the sync scripts locally:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/AdityaPandey-DEV/cp-progress-sync.git
   ```
2. **Navigate to the directory**:
   ```bash
   cd cp-progress-sync
   ```
3. **Explore specific categories**:
   ```bash
   cd leetcode/medium
   ```

---

## 🤖 How the Automation Works

This repo leverages **GitHub Actions** (`.github/workflows/`) to run scheduled cron jobs. 
- `dashboard.yml`: Scans the repository for new files and automatically updates `dashboard.md` with beautiful markdown tables and lists.
- `leetcode-sync.yml`: Automates reaching out to APIs to pull newly accepted solutions and commit them on your behalf.

---

## 🤝 Contributing

We welcome community contributions! Whether it's adding better solutions, optimizing scripts, or improving docs.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Please read our [Contributing Guide](CONTRIBUTING.md) for details.

---

## 📜 License

Distributed under the MIT License. See `LICENSE` for more information.

---

<p align="center">
  Built with ❤️ and ☕ by <a href="https://github.com/AdityaPandey-DEV">Aditya Pandey</a>
</p>