# Argosy Tides 🌊

> A maritime trading simulation game built with Unreal Engine 5.

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
- Visual Studio 2022 or JetBrains Rider
- Rust 1.78+ (for data pipeline tools)
- Python 3.11+ (for prototyping and one-off scripts)
- Git LFS

### Build

```bash
# Clone the repo
git clone https://github.com/egkristi/ArgosyTides.git
cd ArgosyTides

# Initialize Git LFS
git lfs install
git lfs pull

# Build the project
# Windows:
ArgosyTides.uproject  # Opens in Unreal Editor

# Or command line:
# UE5\Engine\Build\BatchFiles\Build.bat ArgosyTidesEditor Win64 Development
```

### Run

Open `ArgosyTides.uproject` in Unreal Editor and click Play.

---

## Documentation

| Document | Description |
|----------|-------------|
| [GDD](docs/GDD.md) | Comprehensive Game Design Document |
| [TAD](docs/TAD.md) | Technical Architecture Document |
| [ROADMAP](docs/ROADMAP.md) | Implementation roadmap with phased milestones |
| [API_INTEGRATION](docs/API_INTEGRATION.md) | Real-world data sources and integration guide |
| [MODDING_GUIDE](docs/MODDING_GUIDE.md) | Creating mods and scenarios |

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
