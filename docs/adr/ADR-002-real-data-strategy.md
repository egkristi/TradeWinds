# ADR-002: Real-World Data vs. Save Game Strategy

## Status

✅ **Accepted**

## Context

Argosy Tides claims to use "real-world data" for commodity prices, weather, and ports. However, this creates a critical design problem:

**The Problem:**
- Player starts game in March 2026. Brent Crude is $70/barrel.
- Player saves game, resumes in May 2026. Real Brent Crude jumps to $90/barrel.
- Game tries to apply "real" prices → player's entire strategy is invalidated.
- Saved games become **unplayable** due to external real-world events.

**Additionally:**
- Real data APIs change, break, or disappear
- Rate limits (100 req/day free tier) insufficient for player base
- Historical accuracy vs. gameplay fun tension

## Decision

Adopt **Option C: Live data drives news/narrative only; local simulation drives gameplay.**

### The Three Options

| Option | Description | Pros | Cons |
|--------|-------------|------|------|
| **A** | Freeze data at game start (snapshot becomes seed) | Deterministic, no surprises | "Live data" claim is misleading |
| **B** | Smooth interpolation between data snapshots | Graceful transitions | Complex, still vulnerable to spikes |
| **C** | Live data = news/narrative; simulation = gameplay prices | Honest marketing, protects gameplay, allows historical saves | Requires separate systems |

### Chosen Architecture (Option C)

```
┌─────────────────────────────────────────────────────────────┐
│                    DATA FLOW                                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│   Real-World APIs          Game Simulation                │
│   ─────────────────        ────────────────                │
│   World Bank prices   ──→  Calibration Layer              │
│   Open-Meteo weather  ──→  (5% drift, player-controlled) │
│   NOAA forecasts      ──→                                   │
│                             ↓                              │
│                        ┌──────────────┐                  │
│                        │   ULocalEconomy  │                  │
│                        │  (Per-port sim)  │                  │
│                        │                  │                  │
│                        │ • Production     │                  │
│                        │ • Consumption    │                  │
│                        │ • Inventory      │                  │
│                        │ • Price curves   │                  │
│                        └──────────────┘                  │
│                             ↓                              │
│                        Gameplay Prices                     │
│                        (What player sees)                  │
│                                                             │
│   ─────────────────────────────────────────────           │
│                        ↓                                   │
│                   Newspaper Headlines                      │
│                   ("Oil prices rising globally")           │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Key Mechanisms

**1. Local Economy Simulation (Per Port)**

Each port runs independent supply-demand simulation:
- **Production facilities:** Grain silo, oil refinery, steel mill
- **Consumption rates:** Population eats, factories consume inputs
- **Inventory levels:** Physical stock on docks
- **Price curve:** Hyperbolic inverse demand (scarce = expensive, surplus = cheap)

**Formula:**
```
Price = Base × (3.0 / (scarcityRatio + 0.5)) × capacityPressure

Where:
- scarcityRatio = inventory / monthly_demand
- capacityPressure = warehouse_fill_percentage (fire sale if > 90%)
- Base = calibrated from real data, but only as gentle drift target
```

**2. Calibration Layer (5% Drift)**

- Real data updates weekly (or monthly)
- Calibration gently nudges "Base" price toward reality at 5% per game-week
- Player can choose: "Use historical data from save" or "Gradually update"
- Emergency brake: player can freeze calibration entirely

**3. News/Narrative Layer**

- Real-world events become in-game newspaper headlines
- "OPEC announces production cuts" → "Global oil prices expected to rise"
- Headline sets expectations; simulation may or may not follow
- Player skill: reading news and anticipating market response

### For Saved Games

| Scenario | Behavior |
|----------|----------|
| Resume from March save in May | Uses March simulation state, not May real prices |
| Player chooses "update to current" | 5% per week drift toward current real trends |
| Player chooses "stay historical" | Calibration frozen; pure simulation continues |
| APIs unavailable | Uses last cached "Base" values; offline mode works |

## Consequences

### Positive

- **Gameplay protected:** Real-world $20 oil spike doesn't bankrupt players
- **Honest marketing:** "Inspired by real-world data" vs. "Uses live prices"
- **Historical saves work:** Resume old games without temporal paradox
- **Strategic depth:** Player must anticipate how news affects local markets
- **Offline play:** No internet required after initial data fetch

### Negative

- **Complexity:** Two systems (simulation + calibration) vs. one
- **Player confusion:** "Why did oil go up in-game when it went down IRL?"
- **Developer burden:** Must explain divergence in tutorial/tooltips
- **Data accuracy:** Not a "realistic trading simulator" but a "trading-inspired game"

### Mitigations

- **Tutorial:** Explicitly teaches "News ≠ Price" mechanic
- **Newspaper UI:** Clear separation between "Global Trends" and "Local Market"
- **Calibration indicator:** UI shows "Base price drifting +5% toward $70"
- **Player control:** Options to freeze/thaw/speed calibration

## Alternatives Reconsidered

**Option A (Freeze at start):** Rejected because "live data" claim becomes misleading. Better to be honest about simulation.

**Option B (Smooth interpolation):** Rejected because still vulnerable to real-world shocks. Only delays the problem.

## References

- [API_INTEGRATION.md Section: Data Strategy](../API_INTEGRATION.md#critical-design-decision-real-data-vs-game-data)
- [TAD Section 3.3: Market Simulation](../TAD.md#33-market-simulation--local-supply-demand-with-real-world-calibration)
- Reference game: [Offworld Trading Company](https://www.mohawkgames.com/game/offworld-trading-company/) — local market simulation with news events
- Reference game: [Capitalism Lab](https://www.capitalismlab.com/) — supply-chain economics

---

*Decided: 2026-05-14*  
*Author: Munin 🐦‍⬛*  
*Reviewers: Claude AI (advisory, recommended Option C)*
