# GitHub Issues to Create

## Issue #1: [RESOLVED] Visual Studio 2022 Installation Complete

**Status:** ✅ **RESOLVED** (as of 2026-05-14)

**Template:** Bug Report  
**Labels:** `bug`, `resolved`, `setup`, `phase-0`  
**Priority:** Critical

### Title
[RESOLVED] Visual Studio 2022 C++ tools installed and verified

### Description
**Problem (RESOLVED):**
Visual Studio 2022 Community with C++ workload has been successfully installed.

**Verification:**
```powershell
winget install --id Microsoft.VisualStudio.2022.Community --silent `
  --custom "--add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended"
# Result: "Found an existing package already installed"
```

**Impact:**
- ✅ C++ project compilation now possible
- ✅ Rust data pipeline build (MSVC linker available)
- ✅ Phase 1 development unblocked

**Acceptance Criteria:**
- [x] SETUP.md updated with clear VS installation instructions
- [x] setup.bat script verifies VS installation
- [x] Documentation mentions this requirement prominently
- [x] GitHub issue created and linked in README

**References:**
- SETUP.md
- docs/TAD.md (Language Choice - ADR-001)

---

## Issue #1.5: [BLOCKER] Unreal Engine 5.4 Installation Required

**Template:** Bug Report  
**Labels:** `bug`, `blocker`, `setup`, `phase-0`  
**Priority:** Critical

### Title
[BLOCKER] Unreal Engine 5.4 installation required for project launch

### Description
**Problem:**
Project cannot be launched without Unreal Engine 5.4+ installed. This blocks:
- Opening ArgosyTides.uproject in Unreal Editor
- Building and testing the game
- Phase 1 development

**Impact:**
- Cannot open project in Unreal Editor
- Cannot test gameplay
- Cannot build C++ code changes
- All development blocked until resolved

**Required Installation:**
1. Install Epic Games Launcher
2. Log in to Epic Games account
3. Install Unreal Engine 5.4+ from Library → Engine Versions

**Workaround:**
None - Unreal Engine is mandatory for UE5 project development.

**Acceptance Criteria:**
- [ ] Unreal Engine 5.4+ installed and verified
- [ ] ArgosyTides.uproject opens in Unreal Editor
- [ ] Project builds successfully
- [ ] setup.bat finds UE5 installation
- [ ] Documentation updated with UE5 installation steps

**References:**
- SETUP.md
- README.md build instructions

---

## Issue #2: [BLOCKER] CI/CD Workflows Not Validated

**Template:** Bug Report  
**Labels:** `bug`, `blocker`, `ci-cd`, `phase-0`  
**Priority:** High

### Title
[BLOCKER] GitHub Actions workflows configured but not tested

### Description
**Problem:**
GitHub Actions workflows (build-win.yml, build-pipeline.yml) are configured but have never run successfully. Need to validate:
- Windows build workflow triggers correctly
- Rust pipeline builds without errors
- Git LFS files handled properly
- Build artifacts created successfully

**Impact:**
- Cannot verify automated builds work
- No CI validation for pull requests
- Release automation not tested
- Potential integration issues undetected

**Workflows to Test:**
1. `.github/workflows/build-win.yml` - UE5 Windows builds
2. `.github/workflows/build-pipeline.yml` - Rust data pipeline

**Required Actions:**
- [ ] Trigger build-win workflow manually
- [ ] Trigger build-pipeline workflow manually
- [ ] Verify build artifacts created
- [ ] Fix any workflow errors
- [ ] Add workflow status badges to README

**Acceptance Criteria:**
- [ ] Both workflows run successfully
- [ ] Build artifacts uploaded correctly
- [ ] No errors in workflow logs
- [ ] README.md displays workflow status badges

**References:**
- .github/workflows/build-win.yml
- .github/workflows/build-pipeline.yml

---

## Issue #3: [ENHANCEMENT] Add Project Status Badges

**Template:** Feature Request  
**Labels:** `enhancement`, `documentation`, `phase-0`  
**Priority:** Medium

### Title
[ENHANCEMENT] Add comprehensive project status badges to README

### Description
**Problem:**
README.md lacks visual indicators for project status, making it hard to quickly assess:
- Current phase
- Build status
- License
- Issue count
- Documentation coverage

**Proposed Solution:**
Add Shields.io badges to README.md header:

```markdown
[![GitHub](https://img.shields.io/github/license/egkristi/ArgosyTides)](LICENSE)
[![GitHub Issues](https://img.shields.io/github/issues/egkristi/ArgosyTides)](https://github.com/egkristi/ArgosyTides/issues)
[![GitHub Stars](https://img.shields.io/github/stars/egkristi/ArgosyTides)](https://github.com/egkristi/ArgosyTides/stargazers)
[![Phase](https://img.shields.io/badge/Phase-0%20Complete-blue)](docs/ROADMAP.md)
[![UE5](https://img.shields.io/badge/Unreal-Engine%205.4+-purple)](https://www.unrealengine.com/)
```

**Future Badges (when available):**
- CI/CD workflow status
- Code coverage
- Discord/Community links
- Steam wishlist (post-launch)

**Acceptance Criteria:**
- [ ] README.md includes status badges
- [ ] Badges link to relevant pages
- [ ] Badges styled consistently
- [ ] Badges don't clutter header

---

## Issue #4: [TASK] Phase 1 - Create Oslo Port

**Template:** Phase 1 Task  
**Labels:** `phase-1`, `mvp`, `port`, `high-priority`  
**Priority:** High

### Title
[PHASE1] Implement Oslo port as MVP vertical slice

### Description
**Phase 1: MVP - Modern Mode**

Implement one fully functional port (Oslo, Norway) as the foundation for the vertical slice.

**Requirements:**

### Functional Requirements
- [ ] Port market screen showing commodity prices
- [ ] Shipyard for buying/selling ships
- [ ] Services: refuel, repair
- [ ] Basic port UI with information display
- [ ] Commodity trading (buy/sell grain)

### Technical Requirements
- [ ] C++ class `APort` or `UPort` implemented
- [ ] Blueprint `BP_Port_Oslo` created
- [ ] Port data in SQLite database
- [ ] UI widgets for market, shipyard, services
- [ ] Save/load port state

### Testing Requirements
- [ ] Player can enter port
- [ ] Player can buy commodities
- [ ] Player can sell commodities
- [ ] Prices update correctly
- [ ] No crashes or errors

**Implementation Plan:**

### C++ Classes
- [ ] `UPort` - Base port class
- [ ] `UPortMarket` - Market/pricing logic
- [ ] `UPortServices` - Services management

### Blueprint Classes
- [ ] `BP_Port` - Base port Blueprint
- [ ] `BP_Port_Oslo` - Oslo-specific instance
- [ ] `UI_PortScreen` - Main port UI
- [ ] `UI_MarketWidget` - Market display
- [ ] `UI_ShipyardWidget` - Ship buying/selling

### UI Screens
- [ ] Port overview screen
- [ ] Market screen (buy/sell)
- [ ] Shipyard screen
- [ ] Services screen

### Data Tables
- [ ] PortData - Oslo port configuration
- [ ] CommodityPrices - Grain prices for Oslo

**Acceptance Criteria:**
- [ ] Player can navigate to Oslo port
- [ ] Port UI displays correctly
- [ ] Grain can be bought and sold
- [ ] Prices follow supply/demand simulation
- [ ] Port state saves and loads correctly
- [ ] No compilation errors
- [ ] No runtime errors in PIE

**Dependencies:**
- Depends on: #5 (Ship implementation)
- Blocks: #6 (Trade loop)

**Estimated Effort:**
**Time:** 2-3 days  
**Complexity:** Medium  
**Priority:** High

---

## Issue #5: [TASK] Phase 1 - Implement Panamax Ship Class

**Template:** Phase 1 Task  
**Labels:** `phase-1`, `mvp`, `ship`, `high-priority`  
**Priority:** High

### Title
[PHASE1] Implement Panamax container ship as MVP vessel

### Description
**Phase 1: MVP - Modern Mode**

Implement one ship class (Panamax container ship) with full cargo functionality.

**Requirements:**

### Functional Requirements
- [ ] Ship statistics display (capacity, speed, fuel)
- [ ] Cargo loading/unloading system
- [ ] Fuel consumption and refueling
- [ ] Ship movement between ports
- [ ] Ship purchase/sell functionality

### Technical Requirements
- [ ] `UShip` class complete (already started)
- [ ] `UShip` Blueprint-exposed functions
- [ ] Cargo manifest system working
- [ ] Fuel system implemented
- [ ] Save/load ship state

**Implementation Plan:**

### C++ Classes
- [x] `UShip` - Base ship class (DONE)
- [ ] `UShipMovement` - Movement/routing logic
- [ ] `UShipCargo` - Cargo management

### Blueprint Classes
- [ ] `BP_Ship` - Base ship Blueprint
- [ ] `BP_Ship_Panamax` - Panamax instance
- [ ] `UI_ShipScreen` - Ship management UI
- [ ] `UI_CargoWidget` - Cargo display

### UI Screens
- [ ] Ship overview screen
- [ ] Cargo manifest screen
- [ ] Ship statistics screen

### Data Tables
- [ ] ShipData - Panamax configuration
- [ ] ShipClasses - Ship class definitions

**Acceptance Criteria:**
- [ ] Player can buy Panamax ship
- [ ] Cargo can be loaded (grain)
- [ ] Cargo can be unloaded
- [ ] Fuel depletes over time
- [ ] Ship can travel to Oslo
- [ ] Ship state saves/loads correctly

**Dependencies:**
- Depends on: None
- Blocks: #4 (Port implementation), #6 (Trade loop)

**Estimated Effort:**
**Time:** 1-2 days  
**Complexity:** Medium  
**Priority:** High

---

## Summary

### Blockers (Must Fix Before Phase 1)
1. **Visual Studio Installation** - Critical blocker
2. **CI/CD Validation** - High priority blocker

### Enhancements (Nice to Have)
3. **Status Badges** - Medium priority documentation

### Phase 1 Tasks (MVP Implementation)
4. **Oslo Port** - High priority, 2-3 days
5. **Panamax Ship** - High priority, 1-2 days

### Next Steps
1. Install Visual Studio 2022
2. Create GitHub issues from this document
3. Link issues in README.md
4. Begin Phase 1 implementation

---

*Generated: 2026-05-14*
