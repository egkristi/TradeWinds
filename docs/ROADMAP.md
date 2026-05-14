# Argosy Tides — Implementation Roadmap

> *"Your mind is tossing on the ocean; There, where your argosies with portly sail, Like signiors and rich burghers on the flood... Do overpeer the petty traffickers..."*  
> — *The Merchant of Venice*, Shakespeare

> **Version:** 1.0  
> **Date:** 2026-05-14  
> **Jira:** MUNIN-70  

---

## Overview

Phased development approach: MVP first, then iterate. Each phase is a vertical slice — playable, testable, shippable.

| Phase | Duration | Goal | Deliverable |
|-------|----------|------|-------------|
| **Phase 0** | 1 week | Foundation | Repo, UE5 project, CI/CD |
| **Phase 1** | 2 weeks | MVP — Modern Mode | Playable single-player trading loop |
| **Phase 2** | 2 weeks | Data & Depth | Rust data pipeline, real APIs, weather, advanced trading |
| **Phase 3** | 2 weeks | Visual Polish | All visual styles, UI, audio |
| **Phase 4** | 2 weeks | Historical Eras | Age of Sail + Steam Era |
| **Phase 5** | 2 weeks | Multiplayer | Local + online MP |
| **Phase 6** | 2 weeks | AI & Balance | AI opponents, difficulty, balance |
| **Phase 7** | 2 weeks | Modding & Content | Mod support, scenarios, extras |
| **Phase 8** | 1 week | Release Prep | Testing, packaging, distribution |

**Total: ~15 weeks to full release** (adjustable based on team size)

---

## Phase 0: Foundation (Week 1)

### 0.1 Repository Setup
- [ ] Create GitHub repo: `github.com/egkristi/Argosy Tides`
- [ ] Set up branch protection, issue templates
- [ ] Configure Git LFS for assets
- [ ] Set up project board (GitHub Projects or Jira integration)

### 0.2 Unreal Engine Project
- [ ] Initialize UE5.4 C++ project
- [ ] Configure build settings (Shipping, Development, Editor)
- [ ] Set up folder structure (Content, Source, Config, Docs)
- [ ] Configure .gitignore for UE5

### 0.3 CI/CD
- [ ] GitHub Actions: automated builds for Win/Mac/Linux
- [ ] GitHub Actions: automated tests
- [ ] Artifact storage for builds

### 0.4 Documentation
- [ ] README.md with build instructions
- [ ] CONTRIBUTING.md for collaborators
- [ ] License file (see GDD Section 12)

**Milestone:** `git clone` → `ue5-build` → playable empty project

---

## Phase 1: MVP — Modern Mode (Weeks 2–3)

### 1.1 Core Systems
- [ ] GameInstance with save/load
- [ ] DataManager with SQLite cache
- [ ] Basic market simulation (static prices)
- [ ] Ship system (3 modern ship classes)
- [ ] Port system (10 starter ports)
- [ ] Commodity system (5 commodities)

### 1.2 Game Loop
- [ ] Buy ship → Load cargo → Sail → Sell → Profit
- [ ] Basic route planning (great circle)
- [ ] Fuel/crew costs
- [ ] Simple events (storms, delays)

### 1.3 UI
- [ ] Main menu (New Game, Continue, Options)
- [ ] Port screen (market, shipyard)
- [ ] Navigation screen (map, route)
- [ ] Fleet screen (ship status)
- [ ] Finance screen (balance, P&L)

### 1.4 Visual Style
- [ ] Top-down 2D as default
- [ ] Simple ship sprites
- [ ] Port icons on world map
- [ ] Basic UI styling

**Milestone:** Can start game, buy ship, trade between 10 ports, make profit

---

## Phase 2: Data & Depth (Weeks 4–5)

### 2.1 Real-World Data Integration
- [ ] Python fetcher: commodity prices (World Bank / Trading Economics)
- [ ] Python fetcher: weather data (Open-Meteo)
- [ ] Python fetcher: port data (World Port Index)
- [ ] Data pipeline: automated updates
- [ ] Offline fallback: cached data

### 2.2 Advanced Market
- [ ] Dynamic prices based on supply/demand
- [ ] Price history graphs
- [ ] Commodity categories (containers, bulk, liquid)
- [ ] Seasonal price modifiers
- [ ] News/events affecting prices

### 2.3 Weather System
- [ ] Real-time weather on map
- [ ] Weather affecting routes (storms = delay/damage)
- [ ] Seasonal weather patterns
- [ ] Ice routes (seasonal)

### 2.4 Expanded Content
- [ ] 20+ port locations
- [ ] 10+ ship classes
- [ ] 15+ commodities
- [ ] Canal routes (Suez, Panama)

### 2.5 Contracts
- [ ] Delivery contracts with deadlines
- [ ] Charter contracts
- [ ] Reputation system

**Milestone:** Live commodity prices, weather affecting gameplay, 20+ ports

---

## Phase 3: Visual Polish (Weeks 6–7)

### 3.1 Visual Styles
- [ ] Top-down 2D (complete)
- [ ] Isometric 3D
- [ ] Full 3D with UE5 Nanite/Lumen
- [ ] Paper map style
- [ ] Data dashboard style
- [ ] Cinematic style
- [ ] Style switcher in settings

### 3.2 Ship Models
- [ ] 3D models for all ship classes
- [ ] LOD system
- [ ] Ship customization (paint, flags)

### 3.3 Port Environments
- [ ] 3D port scenes (selectable for detail view)
- [ ] Animated cranes, ships, water
- [ ] Port-specific architecture

### 3.4 UI Polish
- [ ] Animated transitions
- [ ] Sound feedback
- [ ] Tutorial system
- [ ] Encyclopedia / help

### 3.5 Audio
- [ ] Ambient port sounds
- [ ] Ship sounds (engine, water, wind)
- [ ] UI sounds
- [ ] Background music (5 tracks)

**Milestone:** All visual styles playable, professional look and feel

---

## Phase 4: Historical Eras (Weeks 8–9)

### 4.1 Age of Sail (1650–1850)
- [ ] Historical ship classes (sloop, brig, clipper, etc.)
- [ ] Historical commodities (spices, tea, silk, rum)
- [ ] Historical ports (major trading posts)
- [ ] Pirate encounters
- [ ] Mutiny events
- [ ] Scurvy / crew health
- [ ] Naval press gangs

### 4.2 Steam Era (1850–1950)
- [ ] Steam ship classes
- [ ] Coal as fuel
- [ ] Telegraph for faster market info
- [ ] Refrigerated ships (meat trade)
- [ ] Passenger/mail contracts
- [ ] Suez and Panama canals

### 4.3 Era Framework
- [ ] Era selection at game start
- [ ] Era-specific UI styling
- [ ] Era-appropriate music
- [ ] Historical accuracy mode (optional)

### 4.4 Data
- [ ] Historical commodity prices
- [ ] Historical port data
- [ ] Historical ship specs
- [ ] CLIWOC weather data integration

**Milestone:** Playable Age of Sail and Steam Era modes

---

## Phase 5: Multiplayer (Weeks 10–11)

### 5.1 Local Multiplayer
- [ ] Hotseat mode (pass-and-play)
- [ ] LAN mode (same network)
- [ ] Shared screen vs. split screen options

### 5.2 Online Multiplayer
- [ ] Dedicated server setup
- [ ] Client-server architecture
- [ ] Server browser / matchmaking
- [ ] Player accounts (optional)

### 5.3 Multiplayer Modes
- [ ] Cooperative (shared company)
- [ ] Competitive (separate companies)
- [ ] Versus AI + players
- [ ] Turn-based (async-friendly)
- [ ] Real-time

### 5.4 Sync & Anti-Cheat
- [ ] Authoritative server
- [ ] State validation
- [ ] Desync detection

**Milestone:** 2+ players can trade, compete, cooperate online

---

## Phase 6: AI & Balance (Weeks 12–13)

### 6.1 AI Opponents
- [ ] AI personality types (aggressive, cautious, speculator)
- [ ] AI trading logic
- [ ] AI route planning
- [ ] AI ship purchasing
- [ ] Difficulty levels

### 6.2 Game Balance
- [ ] Ship cost balancing
- [ ] Profit margins tuning
- [ ] Event frequency tuning
- [ ] Difficulty curve testing

### 6.3 Advanced AI
- [ ] AI learning from player strategies
- [ ] AI alliances / rivalries
- [ ] AI market manipulation

**Milestone:** Challenging AI opponents, balanced gameplay

---

## Phase 7: Modding & Content (Weeks 14–15)

### 7.1 Modding Support
- [ ] Mod loading system
- [ ] Mod API (Blueprint + C++)
- [ ] Steam Workshop integration
- [ ] Mod documentation

### 7.2 Scenario Editor
- [ ] Create custom scenarios
- [ ] Share scenarios
- [ ] Scenario scripting

### 7.3 Extra Content
- [ ] Achievements
- [ ] Leaderboards
- [ ] Statistics tracking
- [ ] Photo mode

### 7.4 Scenarios
- [ ] Gold Rush scenario
- [ ] Spice Wars scenario
- [ ] Containerization scenario
- [ ] Community scenarios

**Milestone:** Players can create and share mods/scenarios

---

## Phase 8: Release Prep (Week 16)

### 8.1 Testing
- [ ] Full test pass (all platforms)
- [ ] Performance testing
- [ ] Multiplayer stress test
- [ ] Data pipeline reliability test

### 8.2 Polish
- [ ] Bug fixes
- [ ] UI final pass
- [ ] Audio final pass
- [ ] Localization prep (i18n framework)

### 8.3 Distribution
- [ ] Steam page setup
- [ ] Build packaging (Win/Mac/Linux)
- [ ] Trailer / screenshots
- [ ] Press kit

### 8.4 Documentation
- [ ] Player manual
- [ ] Modding guide
- [ ] API documentation
- [ ] Changelog

**Milestone:** Game ready for public release

---

## Post-Launch (Ongoing)

### Bug Fixes & Patches
- Week 1–2: Hotfix critical issues
- Month 1: Balance patch
- Month 2: QoL update

### Content Updates
- Free: New ports, commodities, events
- Paid: Expansion packs (see GDD Section 15)

### Community
- Discord server
- Modding contests
- Community spotlights

---

## Jira Task Breakdown

| Jira Key | Summary | Phase | Status |
|----------|---------|-------|--------|
| MUNIN-70 | Argosy Tides: Project setup + GDD | 0 | In Progress |
| MUNIN-71 | Argosy Tides: UE5 project initialization | 0 | TODO |
| MUNIN-72 | Argosy Tides: CI/CD pipeline | 0 | TODO |
| MUNIN-73 | Argosy Tides: Core game systems (MVP) | 1 | TODO |
| MUNIN-74 | Argosy Tides: Market simulation | 1 | TODO |
| MUNIN-75 | Argosy Tides: Ship system | 1 | TODO |
| MUNIN-76 | Argosy Tides: Port system | 1 | TODO |
| MUNIN-77 | Argosy Tides: Basic UI | 1 | TODO |
| MUNIN-78 | Argosy Tides: Data pipeline | 2 | TODO |
| MUNIN-79 | Argosy Tides: Weather system | 2 | TODO |
| MUNIN-80 | Argosy Tides: Advanced trading | 2 | TODO |
| MUNIN-81 | Argosy Tides: Visual styles | 3 | TODO |
| MUNIN-82 | Argosy Tides: Ship/port 3D models | 3 | TODO |
| MUNIN-83 | Argosy Tides: Audio | 3 | TODO |
| MUNIN-84 | Argosy Tides: Age of Sail mode | 4 | TODO |
| MUNIN-85 | Argosy Tides: Steam Era mode | 4 | TODO |
| MUNIN-86 | Argosy Tides: Local multiplayer | 5 | TODO |
| MUNIN-87 | Argosy Tides: Online multiplayer | 5 | TODO |
| MUNIN-88 | Argosy Tides: AI opponents | 6 | TODO |
| MUNIN-89 | Argosy Tides: Balance tuning | 6 | TODO |
| MUNIN-90 | Argosy Tides: Modding support | 7 | TODO |
| MUNIN-91 | Argosy Tides: Scenario editor | 7 | TODO |
| MUNIN-92 | Argosy Tides: Release prep | 8 | TODO |

---

*Document owner: Munin 🐦‍⬛*  
*Updated: 2026-05-14*

## Project Tracking Convention (2026-05-14)

**Argosy Tides tracking:**
- **GitHub Issues** — Primary: bugs, features, plans, discussion, implementation tasks
- **GitHub Projects** — Sprint/phase planning
- **Jira (MUNIN-70)** — High-level umbrella only; all detail in GitHub Issues

