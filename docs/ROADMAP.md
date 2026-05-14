# Argosy Tides — Implementation Roadmap

> *"Your mind is tossing on the ocean; There, where your argosies with portly sail, Like signiors and rich burghers on the flood... Do overpeer the petty traffickers..."*  
> — *The Merchant of Venice*, Shakespeare

> **Version:** 2.0 — Milestone-Based (No Calendar Dates)  
> **Date:** 2026-05-14  
> **Jira:** MUNIN-70  

---

## Overview

**Current Phase:** Phase 0 Complete ✅  
**Next Phase:** Phase 1 (MVP) - Modern Mode  
**Realistic timeline:** 18–36 months for one developer with AI assistance.

Milestone-based approach: Phases complete when criteria are met, not by calendar. Each phase is a vertical slice — playable, testable, shippable.

### Progress Summary

| Phase | Status | Completion |
|-------|--------|------------|
| **Phase 0** | ✅ Complete | Foundation ready |
| **Phase 1** | 📋 Planned | 0% |
| **Phase 2** | 📋 Planned | 0% |
| **Phase 3** | 📋 Planned | 0% |
| **Phase 4** | 📋 Planned | 0% |
| **Phase 5** | 📋 Planned | 0% |
| **Phase 6** | 📋 Planned | 0% |
| **Phase 7** | 📋 Planned | 0% |
| **Phase 8** | 📋 Planned | 0% |

| Phase | Completion Criteria | Deliverable |
|-------|---------------------|-------------|
| **Phase 0** | Repo pushable, builds on 3 platforms, empty project runs | Foundation: Repo, UE5 project, CI/CD |
| **Phase 1** | One port, one ship, one commodity pair, profitable trade loop | MVP — Modern Mode |
| **Phase 2** | Rust fetchers working, SQLite saves < 5MB, weather affects gameplay | Data & Depth |
| **Phase 3** | Top-down playable, Paper Map toggleable, UI scales 100–200% | Visual Polish (2 styles) |
| **Phase 4** | Age of Sail + Steam Era playable, captains v1 working, rivals v1 working | Historical Eras |
| **Phase 5** | 2+ players can trade, sync stable, desync < 1% | Multiplayer |
| **Phase 6** | AI beats naive players, difficulty curve felt, balance metrics logged | AI & Balance |
| **Phase 7** | JSON mod loads, Lua scripts run, one community mod published | Modding & Content |
| **Phase 8** | Zero critical bugs, Steam page live, press kit ready | Release Prep |
| **Post-Launch** | See Expansion Packs below | Ancient Routes + More |

---

## Critical Path Dependencies

```
Phase 0 ──→ Phase 1 ──→ Phase 2 ──→ Phase 3 ──→ Phase 4 ──→ Phase 5 ──→ Phase 6 ──→ Phase 7 ──→ Phase 8
              │           │           │           │
              ↓           ↓           ↓           ↓
           Vertical    SQLite      2 Styles    Captains
           Slice       Done        Working     v1 Done
```

**Cannot proceed until previous phase "Done":**
- Phase 2 requires Phase 1 vertical slice playable
- Phase 4 requires Phase 3 visual polish (player experience matters)
- Phase 5 requires Phase 4 core gameplay solid (no point MP if SP is broken)

**Can proceed in parallel:**
- Art assets for future eras (risk: may need rework)
- Data pipeline expansion (risk: APIs may change)
- Modding documentation (low risk)

---

## Phase 0: Foundation

**Status:** ✅ **COMPLETE** (as of 2026-05-14)

### Completion Criteria
- [x] Git repo pushable to GitHub with clean history
- [x] Builds successfully on Windows, macOS, Linux (CI/CD configured)
- [ ] Empty UE5 project launches without errors (requires VS 2022)
- [x] `.gitignore` configured for UE5 + LFS
- [x] README has build instructions that work

### Deliverable
✅ Repository that a new contributor can clone and build in < 30 minutes.

### Completed Items
- ✅ Unreal Engine 5.4+ project structure
- ✅ C++ core systems (GameInstance, DataManager, WeatherSystem, FleetManager, Ship)
- ✅ Rust data pipeline with API integrations
- ✅ Python prototype for quick testing
- ✅ CI/CD workflows (GitHub Actions)
- ✅ Build scripts (setup.bat, build.bat)
- ✅ Comprehensive documentation (GDD, TAD, ROADMAP, ADRs)
- ✅ AI agent instructions (5 files)
- ✅ MIT License

### Outstanding Blockers
- ⏳ Visual Studio 2022 installation required for C++ compilation
- ⏳ Rust MSVC linker requires VS C++ tools
- ⏳ CI/CD workflows not yet validated (no runs triggered)

---

## Phase 1: MVP — Modern Mode (Vertical Slice)

### Completion Criteria
- [ ] **One port** fully functional (e.g., Oslo): market, shipyard, services
- [ ] **One ship class** (Panamax container): buy, sail, sell
- [ ] **One commodity pair** (grain: buy low → sail → sell high)
- [ ] Profitable trade loop: player can start, trade, make profit, save, reload
- [ ] SQLite save system: save < 1 MB, loads correctly
- [ ] Basic UI: port screen, navigation, fleet view

### Explicitly NOT in MVP
- Multiple ports (just the one)
- Weather system (static conditions)
- Real-time data (static prices)
- Captains with personalities (interchangeable placeholders)
- Rivals (no AI opponents)
- Multiplayer
- Historical eras

**Vertical slice = one complete gameplay loop.**

---

## Phase 2: Data & Depth

### Completion Criteria
- [ ] Rust data pipeline builds and runs
- [ ] Fetches real commodity prices (World Bank, caches locally)
- [ ] SQLite saves: < 5 MB typical, compression working
- [ ] Weather affects routes: storms delay, ice blocks
- [ ] Offline mode: game works without internet (cached data)
- [ ] Calibration system: real data gently nudges simulation

### Deliverable
Living economy that feels responsive to real-world trends without breaking gameplay.

---

## Phase 3: Visual Polish (2 Styles)

### Completion Criteria
- [ ] **Top-Down/Isometric**: Default, playable, information-dense
- [ ] **Paper Map**: Toggleable, aesthetic, historical feel
- [ ] UI scales 100–200% (accessibility)
- [ ] Full keyboard navigation (no mouse required)
- [ ] Colorblind modes tested
- [ ] Motion sickness: camera smoothing optional

### Post-Launch (NOT Phase 3)
- Full 3D camera mode
- Data Dashboard overlay
- Cinematic mode

**Why 2 styles:** One art pipeline, multiple ways to view it. Realistic for hobby project.

---

## Phase 4: Historical Eras

### Completion Criteria
- [ ] Age of Sail: sailing ships, wind mechanics, pirates
- [ ] Steam Era: steam engines, coal, canals
- [ ] Captains v1: names, basic skills, loyalty (no personality depth yet)
- [ ] Rivals v1: named AI, basic trading (no revenge arcs yet)
- [ ] Ship combat: flee/fight/surrender
- [ ] Storm events: 5-stage mechanic working

### Post-Launch (Expansion Pack): Ancient Routes
- Viking longships, Chinese treasure fleets, Polynesian navigation
- Reason: Sparse historical data requires research partnership
- Expansion: "Argosy Tides: Ancient Routes"

---

## Phase 5: Multiplayer

### Completion Criteria
- [ ] Turn-based multiplayer: 2+ players, stable sync
- [ ] Desync rate < 1% over 100 test games
- [ ] LAN play working
- [ ] Online: dedicated server or P2P with host migration
- [ ] Save/load multiplayer state correctly

### Out of Scope (Post-Launch)
- Real-time multiplayer (high complexity, low value for trading game)
- MMO persistence (requires infrastructure beyond scope)

---

## Phase 6: AI & Balance

### Completion Criteria
- [ ] AI opponents beat "buy low sell high" naive strategy
- [ ] Difficulty levels felt: Beginner < Intermediate < Expert < Master
- [ ] Balance metrics logged: average profit by route, ship usage, abandonment points
- [ ] No infinite money exploits
- [ ] No soft locks (player can always recover from bad position)

---

## Phase 7: Modding & Content

### Completion Criteria
- [ ] JSON mod loading: ships, ports, commodities
- [ ] Lua scripting: events, behaviors
- [ ] One community mod published and working
- [ ] Mod documentation complete
- [ ] Steam Workshop OR GitHub-based distribution

---

## Phase 8: Release Prep

### Completion Criteria
- [ ] Zero critical bugs (crash, data loss, soft lock)
- [ ] Steam page live with trailer
- [ ] Press kit: screenshots, fact sheet, contact
- [ ] ESRB rating submitted (if seeking rating)
- [ ] Launch day patch ready (hotfix branch)

---

## Post-Launch: Expansion Packs

### Argosy Tides: Ancient Routes
- **Era:** B.C.–1600 (pre-industrial)
- **Ships:** Viking longships, Chinese treasure junks, Arab dhows, Polynesian catamarans
- **Challenge:** Sparse historical data — requires research partnership or academic collaboration
- **Timeline:** 6–12 months post-launch

### Potential Future Expansions
- Arctic Routes (icebreakers, polar navigation)
- Future Tech (autonomous ships, green energy)
- Fantasy (steampunk airships, sea monsters)

---

## Risk Register

| Risk | Likelihood | Mitigation |
|------|------------|------------|
| Scope creep into "simulator" | High | Vertical slice gates. No new features until slice is profitable. |
| Real-time data APIs change/break | Medium | Abstraction layer, multiple sources, offline fallback. |
| Multiplayer sync issues | High | Turn-based reduces complexity. Extensive testing phase. |
| Visual polish takes too long | High | 2 styles only. Rest are camera modes. |
| Historical data insufficient | Medium | Ancient Routes as expansion, not core. |

---

## Decision Log

| Date | Decision | Rationale |
|------|----------|-----------|
| 2026-05-14 | Milestone-based roadmap (no dates) | Calendar estimates were unrealistic (15 weeks → 18–36 months) |
| 2026-05-14 | 2 visual styles only | 6 styles = 6× art pipeline work. Not viable for hobby. |
| 2026-05-14 | Ancient Routes as expansion | Pre-industrial data too sparse for core game. |
| 2026-05-14 | Captains v1 basic, v2 deep | Personality arcs post-launch to protect scope. |

---

*Made with 🌊 by the Argosy Tides team*
