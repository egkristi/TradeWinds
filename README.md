# Argosy Tides 🌊

> *"Your mind is tossing on the ocean; There, where your argosies with portly sail, Like signiors and rich burghers on the flood... Do overpeer the petty traffickers..."*  
> — *The Merchant of Venice*, Shakespeare

[![GitHub](https://img.shields.io/github/license/egkristi/ArgosyTides)](LICENSE)
[![GitHub Issues](https://img.shields.io/github/issues/egkristi/ArgosyTides)](https://github.com/egkristi/ArgosyTides/issues)
[![GitHub Stars](https://img.shields.io/github/stars/egkristi/ArgosyTides)](https://github.com/egkristi/ArgosyTides/stargazers)
[![Build Windows](https://github.com/egkristi/ArgosyTides/actions/workflows/build-win.yml/badge.svg)](https://github.com/egkristi/ArgosyTides/actions/workflows/build-win.yml)
[![Build Pipeline](https://github.com/egkristi/ArgosyTides/actions/workflows/build-pipeline.yml/badge.svg)](https://github.com/egkristi/ArgosyTides/actions/workflows/build-pipeline.yml)

**Status:** Phase 0 Complete - Foundation Ready  
**Next Phase:** Phase 1 (MVP) - One port, one ship, one commodity  
**Engine:** Unreal Engine 5.4+  
**Languages:** C++20, Blueprint, Rust, Python  

**Argosy Tides** is a deep, data-driven trading simulation where you build a shipping empire across eras. Buy ships, trade commodities, navigate real weather, and outsmart competitors in a living global economy powered by real-world data.

---

## Features

### 🚢 Ship Fleet Management
- Modern container ships, bulk carriers, tankers, LNG carriers
- Historical sailing ships (sloops, clippers, East Indiamen)
- Steam-era vessels (paddle-wheelers, refrigerated ships)
- **Global Historical Expeditions:** Viking longships (knarr, skeid, drekar), Chinese treasure junks (Fuchuan, Baochuan), Arab dhows (boom, baghlah), Polynesian double canoes (waka), Mediterranean galleys
- Customize, upgrade, repair, and insure your fleet

### 🌍 Real-World Data
- **Live commodity prices** — Real-time market data from World Bank, Trading Economics
- **Real weather** — Open-Meteo marine forecasts affect your routes
- **Real ports** — 3,700+ ports with accurate locations, facilities, and fees
- **Ocean currents** — Copernicus data for route optimization
- **Historical accuracy** — CLIWOC ship logs and historical trade records

### 🎮 Multiple Eras
- **Modern (2024+)** — Containerization, global supply chains, mega-ships
- **Age of Sail (1650–1850)** — Spice trade, pirates, exploration
- **Steam Era (1850–1950)** — Industrial revolution, canals, telegraphs
- **Global Historical Expeditions (B.C.–1600)** — Viking raids, Chinese treasure fleets (Zheng He), Arab monsoon traders, Polynesian celestial navigators, Mediterranean triremes
- **Custom scenarios** — Community-created challenges

### 🎨 Visual Styles
- **Top-Down** — Classic strategy view
- **Isometric** — Detailed 3D with fixed camera
- **Full 3D** — UE5 Nanite/Lumen cinematic quality
- **Paper Map** — Hand-drawn nautical chart aesthetic
- **Data Dashboard** — Bloomberg-terminal information density
- **Cinematic** — Immersive, minimal-UI roleplay

### 🎲 Game Modes
- **Single-player** — Build your empire at your own pace
- **Local Multiplayer** — Hotseat or LAN with friends
- **Online Multiplayer** — Dedicated servers, up to 16 players
- **AI Opponents** — Smart AI with distinct personalities

### 🏆 Victory Conditions
- **Tycoon** — Amass the greatest fortune
- **Trader** — Complete challenging delivery contracts
- **Explorer** — Visit every port on the map
- **Survival** — Stay profitable against increasing odds
- **Sandbox** — No pressure, infinite play

---

## Quick Start

### Prerequisites
- Unreal Engine 5.4+
- Visual Studio 2022 with C++ workload
- Rust 1.78+ (for data pipeline tools)
- Python 3.11+ (for prototyping and one-off scripts)
- Git LFS

### Setup

**Windows:**

```powershell
# Clone the repo
git clone https://github.com/egkristi/ArgosyTides.git
cd ArgosyTides

# Initialize Git LFS
git lfs install
git lfs pull

# Run setup script
.\setup.bat
```

See [`SETUP.md`](SETUP.md) for detailed installation instructions.

### Build

**Option 1: Unreal Editor (Recommended)**

```powershell
# Double-click to open in Unreal Editor
ArgosyTides.uproject
```

**Option 2: Command Line**

```powershell
# Run build script
.\build.bat

# Or manually:
& "C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\Build.bat" `
  ArgosyTidesEditor Win64 Development `
  -project="ArgosyTides.uproject" -log -wait
```

### Run

Open `ArgosyTides.uproject` in Unreal Editor and click Play.

### Build Data Pipeline (Optional)

```powershell
cd Tools\DataPipeline
cargo build --release

# Run the pipeline
cargo run -- build-all
```

> **Note:** Building the Rust data pipeline requires Visual Studio C++ tools.

---

## Project Status

### ✅ Phase 0: Foundation (Complete)
- Git repository with clean history
- Unreal Engine 5.4+ project structure
- C++ core systems implemented
- Rust data pipeline skeleton
- CI/CD workflows configured
- Comprehensive documentation
- AI agent instructions

### 📋 Phase 1: MVP (Next)
- One port (Oslo)
- One ship (Panamax container)
- One commodity (grain)
- Basic trade loop
- SQLite save system
- Simple UI screens

### ⚠️ Known Blockers
- **Unreal Engine 5.4 Required** - Install via Epic Games Launcher
- **No Visual Assets Yet** - Placeholder geometry only
- **CI/CD Not Tested** - Workflows configured but not validated; first runs failed due to invalid action references

### ✅ Resolved Blockers
- **Visual Studio 2022** - Installed and verified (v17.14.32)
- **Rust MSVC Linker** - Working with VS C++ tools

See [Issues](https://github.com/egkristi/ArgosyTides/issues) for current blockers and planned work.

---

## Documentation

### Core Documents
| Document | Description |
|----------|-------------|
| [GDD](docs/GDD.md) | Comprehensive Game Design Document |
| [TAD](docs/TAD.md) | Technical Architecture Document |
| [ROADMAP](docs/ROADMAP.md) | Implementation roadmap with phased milestones |
| [API_INTEGRATION](docs/API_INTEGRATION.md) | Real-world data sources and integration guide |
| [MODDING_GUIDE](docs/MODDING_GUIDE.md) | Creating mods and scenarios |

### Development Guides
| Document | Description |
|----------|-------------|
| [SETUP.md](SETUP.md) | Installation and environment setup |
| [PHASE0_STATUS.md](PHASE0_STATUS.md) | Phase 0 completion report |
| [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) | Comprehensive project overview |
| [CHANGELOG.md](CHANGELOG.md) | Version history and changes |
| [CONTRIBUTING.md](CONTRIBUTING.md) | Contribution guidelines |

### AI Agent Instructions
| Document | For | Description |
|----------|-----|-------------|
| [`.cursorrules`](.cursorrules) | Cursor IDE | Comprehensive coding standards and patterns |
| [`.github/copilot-instructions.md`](.github/copilot-instructions.md) | GitHub Copilot | Quick reference for Copilot |
| [`.github/AI_INSTRUCTIONS.md`](.github/AI_INSTRUCTIONS.md) | All AI Agents | Detailed architecture and workflows |
| [`CLAUDE.md`](CLAUDE.md) | Claude Code | Claude-specific instructions |
| [`.sourcegraph/cody.json`](.sourcegraph/cody.json) | Cody | Sourcegraph Cody configuration |

---

## AI Agent Setup

This project includes comprehensive AI agent instructions for multiple coding assistants:

- **Cursor IDE:** Automatically loads `.cursorrules`
- **GitHub Copilot:** Reads `.github/copilot-instructions.md`
- **Claude Code:** Reads `CLAUDE.md`
- **Cody:** Reads `.sourcegraph/cody.json`

These files provide context about the project architecture, coding standards, and current development phase.

---

## Screenshots

*Coming soon — early development*

---

## Roadmap

| Phase | Focus | Status |
|-------|-------|--------|
| Phase 0 | Foundation (repo, CI/CD) | 🚧 In Progress |
| Phase 1 | MVP — Modern Mode | ⏳ Planned |
| Phase 2 | Real Data & Weather | ⏳ Planned |
| Phase 3 | Visual Polish | ⏳ Planned |
| Phase 4 | Historical Eras | ⏳ Planned |
| Phase 5 | Multiplayer | ⏳ Planned |
| Phase 6 | AI & Balance | ⏳ Planned |
| Phase 7 | Modding | ⏳ Planned |
| Phase 8 | Release | ⏳ Planned |

See [ROADMAP.md](docs/ROADMAP.md) for detailed breakdown.

---

## Contributing

We welcome contributions! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Ways to Contribute
- 🐛 Bug reports
- 💡 Feature suggestions
- 🎨 Art assets (ships, ports, UI)
- 🎵 Music and sound effects
- 🌍 Data research (ports, commodities, historical records)
- 💻 Code (C++, Blueprint, Python)
- 📝 Documentation

---

## License

| Component | License |
|-----------|---------|
| Game code | Proprietary (Phase 1), potential open-source later |
| Documentation | [CC BY-SA 4.0](LICENSE-DOCS) |
| Data pipeline tools | [MIT](LICENSE-TOOLS) |
| Modding API | Open (see [MODDING_GUIDE](docs/MODDING_GUIDE.md)) |

See [GDD Section 12](docs/GDD.md#12-monetization--licensing) for full licensing strategy.

---

## Data Attribution

Argosy Tides uses real-world data from these sources:

- [World Bank](https://worldbank.org) — Commodity prices (CC BY 4.0)
- [Open-Meteo](https://open-meteo.com) — Weather data (CC BY 4.0)
- [NOAA](https://noaa.gov) — Marine forecasts (Public Domain)
- [Natural Earth](https://naturalearthdata.com) — Geography (Public Domain)
- [Copernicus Marine](https://marine.copernicus.eu) — Ocean data
- [NSIDC](https://nsidc.org) — Sea ice data
- [GEBCO](https://gebco.net) — Bathymetry
- [OpenStreetMap](https://openstreetmap.org) — Port details (ODbL)

See [API_INTEGRATION.md](docs/API_INTEGRATION.md) for complete list and license details.

---

## Community

- 💬 Discord — planned (no link until live)
- 🐦 X/Twitter — planned (no link until live)
- 🎮 Steam — planned (no link until live)

---

## Acknowledgments

- Inspired by classic maritime trading simulations
- Built with [Unreal Engine 5](https://unrealengine.com)
- Real-world data powered by open science and government agencies

---

*Made with 🌊 by the Argosy Tides team*
