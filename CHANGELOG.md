# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added - 2026-05-14
- **Project Foundation**
  - Initial project structure created
  - Unreal Engine 5.4+ project configuration
  - Git repository with LFS support
  - CI/CD workflows (GitHub Actions)
  
- **C++ Core Systems**
  - `UArgosyTidesGameInstance` - Main game instance
  - `UDataManager` - Data abstraction layer
  - `UWeatherSystem` - Weather management
  - `UFleetManager` - Fleet management
  - `UShip` - Ship class
  - Shared types (`EGameEra`, `EVisualStyle`, data structs)
  
- **Rust Data Pipeline**
  - CLI tool for fetching real-world data
  - World Bank commodity price integration
  - Open-Meteo weather integration
  - SQLite database support
  - Port data management
  
- **Documentation**
  - Game Design Document (GDD)
  - Technical Architecture Document (TAD)
  - Implementation Roadmap
  - API Integration Guide
  - Architecture Decision Records (ADRs)
  - Setup instructions
  - Build scripts

### Changed
- Renamed project from "TradeWinds" to "Argosy Tides" (trademark compliance)

### Removed
- Slave trade mechanics (ethical decision - see GDD)

## [0.1.0] - 2026-05-14

### Initial Release
- Phase 0: Foundation complete
- Ready for Unreal Editor opening
- Ready for Rust data pipeline build (requires Visual Studio C++ tools)

---

## Future Versions (Planned)

### [0.2.0] - Phase 1: MVP
- One functional port (Oslo)
- One ship class (Panamax container)
- One commodity trading loop
- Basic UI screens
- SQLite save system

### [0.3.0] - Phase 2: Data & Depth
- Real commodity price integration
- Weather system affecting routes
- Offline mode with cached data
- Calibration layer for real data

### [0.4.0] - Phase 3: Visual Polish
- Top-down visual style
- Paper Map visual style
- UI scaling and responsiveness

### [0.5.0] - Phase 4: Historical Eras
- Age of Sail mode
- Steam Era mode
- Captains v1 system
- Rival AI v1

### [1.0.0] - Release
- Multiplayer support
- AI opponents with personalities
- Modding support
- Steam release
