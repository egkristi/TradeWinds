# TradeWinds — Game Design Document (GDD)

> **Version:** 1.0  
> **Date:** 2026-05-14  
> **Status:** Draft — awaiting GitHub repo creation  
> **Jira:** MUNIN-70  

---

## 1. Executive Summary

**TradeWinds** is a maritime trading simulation game where players buy ships, trade commodities between ports, manage finances, and build a shipping empire. The game spans historical and modern eras with real-world data powering the economy, ports, ships, and routes.

**Core loop:** Buy ship → Load cargo → Sail route → Sell for profit → Upgrade fleet → Expand empire.

**Visual identity:** Nautical, warm, evocative. Think sepia-toned maps meeting modern data visualization.

---

## 2. Game Overview

| Attribute | Detail |
|-----------|--------|
| **Name** | TradeWinds |
| **Genre** | Maritime Trading Simulation / Tycoon |
| **Platforms** | PC (Windows, macOS, Linux) |
| **Engine** | Unreal Engine 5.4+ |
| **Multiplayer** | Single-player, Local multiplayer (hotseat/LAN), Online multiplayer (dedicated servers), AI opponents |
| **Target Audience** | Strategy fans, history enthusiasts, data geeks, casual tycoon players |
| **Monetization** | Hobby project with commercial potential — single purchase, no microtransactions, modding support |
| **ESRB Rating** | E for Everyone |

---

## 3. Core Gameplay

### 3.1 Game Flow

```
Main Menu
    ├── New Game
    │       ├── Select Era (Modern / Age of Sail / Steam Era / Custom)
    │       ├── Select Map (World / Region / Custom)
    │       ├── Select Visual Style (Top-Down / Isometric / Full 3D / Paper Map / Data Dashboard)
    │       ├── Configure Difficulty & AI Opponents
    │       └── Start
    ├── Continue
    ├── Multiplayer
    │       ├── Host Game (Local / Online)
    │       ├── Join Game (LAN / Server Browser)
    │       └── Spectate
    ├── Options
    └── Mods / Workshop
```

### 3.2 Core Loop

1. **Market Analysis** — Check port prices, commodity trends, weather, demand
2. **Ship Management** — Select ship(s), check fuel/crew condition, load/unload cargo
3. **Route Planning** — Plot course considering distance, weather, fuel, risks
4. **Sailing** — Real-time or accelerated travel with event encounters
5. **Trading** — Sell cargo, buy new goods, negotiate deals
6. **Expansion** — Buy new ships, upgrade existing, hire better crew, unlock new ports

### 3.3 Victory Conditions

| Mode | Win Condition |
|------|---------------|
| **Tycoon** | Reach $X net worth within Y years |
| **Trader** | Complete X special delivery contracts |
| **Explorer** | Visit all ports on the map |
| **Survival** | Stay profitable for X years with increasing difficulty |
| **Sandbox** | No win condition — infinite play |

---

## 4. Eras & Game Modes

### 4.1 Modern Mode (Default)

**Time period:** Present day (2024+)

**Features:**
- Live commodity prices (gold, oil, grain, electronics, containers)
- Real-time weather data affecting routes (storms, fog, ice)
- Modern ship classes: Container ships, bulk carriers, tankers, LNG carriers, ro-ro ferries
- Real port data: throughput, facilities, fees, congestion
- Live events: strikes, canal closures, geopolitical events
- Fuel prices fluctuate with real Brent crude / bunker fuel indices
- Insurance modeled on real maritime insurance principles

**Data sources:** See Section 11.

### 4.2 Age of Sail (1650–1850)

**Ship classes:**
- Sloop (fast, small cargo, low crew)
- Brig (balanced)
- Barque (large cargo, slow)
- Clipper (very fast, luxury goods)
- East Indiaman (huge cargo, armed)

**Commodities:** Spices, tea, silk, sugar, rum, slaves (optional/historical accuracy toggle), fur, timber

**Hazards:** Pirates, storms, scurvy, mutiny, shipwreck, naval press gangs

**Ports:** Historical accuracy — major trading posts of the era

### 4.3 Steam Era (1850–1950)

**Ship classes:**
- Steam paddle-wheeler
- Iron-hulled cargo steamer
- Oil tanker (early)
- Passenger liner (mail contracts)
- Refrigerated ship (frozen meat trade)

**Commodities:** Coal, iron, manufactured goods, grain, meat, oil, passengers

**Innovations:** Telegraph (faster market info), Suez Canal, Panama Canal, steam engines

### 4.4 Custom / Scenario Mode

- User-defined starting parameters
- Historical events as scenarios (Gold Rush, Spice Wars, Containerization)
- Community-created scenarios via modding

### 4.5 Global Historical Expeditions (B.C.–1600)

Pre-industrial maritime trade across all cultures. No gunpowder-era ships.

**Ship classes by culture:**

| Culture | Ship Class | Era | Specialization |
|---------|-----------|-----|---------------|
| **Viking** | Knarr | 800–1100 | Cargo, coastal, river-capable |
| **Viking** | Longship (Skeid) | 800–1100 | Fast raids, shallow draft |
| **Viking** | Dragon Ship (Drekar) | 900–1100 | Long-range, prestige |
| **Chinese** | Junk (Fuchuan) | 200–1500 | Balanced cargo, junk rig |
| **Chinese** | Treasure Ship (Baochuan) | 1405–1433 | Massive cargo, Zheng He's fleet |
| **Chinese** | Sand Boat (Shachuan) | 800–1500 | River/canal, shallow draft |
| **Arab** | Dhow (Boom) | 500–1500 | Monsoon trade, lateen sail |
| **Arab** | Baghlah | 700–1600 | Deep cargo, Red Sea / Indian Ocean |
| **Polynesian** | Double Canoe (Waka) | 500–1500 | Exploration, no compass |
| **Polynesian** | Outrigger Canoe | 500–1500 | Island hopping, shallow draft |
| **Mediterranean** | Carrack | 1300–1600 | Late Age of Sail precursor |
| **Mediterranean** | Galley | 500–1500 | Rowed, coastal, slave-powered |

**Unique mechanics:**
- **Viking:** Raid OR trade (dual economy), fjord navigation, seasonal sailing only
- **Chinese:** Treasure fleet expeditions (massive multi-ship missions), compass navigation, silk trade
- **Arab:** Monsoon timing (seasonal routes), dhow specialization, incense/spice focus
- **Polynesian:** Celestial navigation (no compass), star charts, island discovery
- **Mediterranean:** Galley combat (ramming), trireme fleets, amphora cargo

**Commodities:** Amber, walrus ivory, silk, porcelain, spices, incense, obsidian, grain, wine, olive oil, salt, furs, slaves (toggleable/historical context)

**Routes:**
- Baltic Sea amber route
- Silk Road maritime (South China Sea → Indian Ocean → Red Sea)
- Spice route (Moluccas → India → Arabia → Mediterranean)
- Pacific island chain routes
- Mediterranean grain routes (Alexandria → Rome)

**Hazards:** Pirates (all eras), storms, scurvy, mutiny, shipwreck, ice (Viking routes), monsoon timing, reef navigation

**Events:**
- Viking raids on monasteries (loot + reputation hit)
- Zheng He's treasure fleet voyages (massive reward)
- Typhoon season (South China Sea)
- Monsoon wind reversal (Arabian Sea / Indian Ocean)

---

## 5. Ship System

### 5.1 Ship Attributes

| Attribute | Description |
|-----------|-------------|
| **Cargo Capacity** | Tonnage / TEU (containers) / volume |
| **Speed** | Knots — affects travel time and fuel |
| **Fuel / Range** | Distance before refueling (modern) or provisions (historical) |
| **Crew** | Minimum and optimal crew size |
| **Condition** | Hull integrity, engine state, sail condition |
| **Ice Class** | Ability to navigate polar routes |
| **Draft** | Shallow draft = access to smaller ports |
| **Cost** | Purchase price, maintenance, crew wages, insurance |

### 5.2 Ship Classes (Modern)

| Class | Capacity | Speed | Range | Cost | Best For |
|-------|----------|-------|-------|------|----------|
| Feeder | 500 TEU | 16 kn | 5,000 nm | $15M | Short regional routes |
| Panamax | 5,000 TEU | 22 kn | 12,000 nm | $80M | Panama Canal routes |
| Post-Panamax | 12,000 TEU | 24 kn | 15,000 nm | $150M | Major lanes |
| Ultra Large | 24,000 TEU | 22 kn | 18,000 nm | $200M | Asia-Europe only |
| Bulk Carrier | 180,000 DWT | 14 kn | 20,000 nm | $60M | Ore, coal, grain |
| LNG Carrier | 170,000 m³ | 19 kn | 18,000 nm | $250M | Gas transport |
| Oil Tanker (VLCC) | 320,000 DWT | 15 kn | 22,000 nm | $120M | Crude oil |

### 5.3 Ship Classes (Historical — Age of Sail)

| Class | Tons | Crew | Speed | Guns | Cost |
|-------|------|------|-------|------|------|
| Sloop | 50 | 15 | 10 kn | 8 | £500 |
| Brig | 200 | 40 | 8 kn | 16 | £2,000 |
| Barque | 400 | 60 | 6 kn | 20 | £5,000 |
| Clipper | 800 | 80 | 14 kn | 4 | £15,000 |
| East Indiaman | 1,200 | 150 | 7 kn | 30 | £30,000 |

---

## 6. Port System

### 6.1 Port Attributes

| Attribute | Description |
|-----------|-------------|
| **Location** | Real-world lat/lon |
| **Type** | Container, bulk, liquid, passenger, fishing, military |
| **Depth** | Max vessel draft allowed |
| **Facilities** | Dry dock, repair, chandlery, warehouses |
| **Fees** | Port dues, pilotage, tug, berthing |
| **Security** | Piracy risk, political stability |
| **Connectivity** | Rail, road, inland waterway links |

### 6.2 Port Tiers

| Tier | Examples | Features |
|------|----------|----------|
| **Mega-Hub** | Shanghai, Singapore, Rotterdam | All commodities, cheapest bulk rates |
| **Major** | Hamburg, Los Angeles, Dubai | Most commodities, good rates |
| **Regional** | Oslo, Cape Town, Vancouver | Limited commodities, moderate fees |
| **Minor** | Nuuk, Reykjavik, Port Moresby | Niche goods, high fees, seasonal |

### 6.3 Port Services

- **Repair** — Fix hull, engine, sails
- **Refuel / Reprovision** — Bunker fuel, coal, food, water
- **Crew** — Hire, train, rest
- **Insurance** — Buy maritime insurance
- **Storage** — Warehouse goods for price speculation
- **Shipyard** — Buy new ships, sell old, upgrade

---

## 7. Commodity & Economy System

### 7.1 Modern Commodities

| Category | Examples | Price Driver |
|----------|----------|--------------|
| **Containers** | Electronics, textiles, machinery | Global trade volume, fuel costs |
| **Bulk Dry** | Iron ore, coal, grain, cement | Industrial demand, harvest cycles |
| **Liquid Bulk** | Crude oil, LNG, chemicals | OPEC, geopolitics, season |
| **Refrigerated** | Meat, fish, fruit, vaccines | Seasonal, perishability |
| **Vehicles** | Cars, trucks, heavy equipment | Manufacturing output |
| **Project Cargo** | Wind turbines, factory parts | Infrastructure investment |

### 7.2 Price Dynamics

- **Base price** — Real-world commodity indices (source: see Section 11)
- **Local modifiers** — Supply/demand at each port
- **Seasonality** — Harvest times, heating oil demand, monsoon
- **Events** — War, embargo, canal closure, pandemic
- **Player impact** — Large trades affect local prices (market depth)

### 7.3 Contracts & Missions

| Type | Description |
|------|-------------|
| **Spot Trade** | Buy low, sell high — pure speculation |
| **Delivery Contract** | Fixed price, destination, deadline — penalty for delay |
| **Charter** | Rent ship to AI/players for a route |
| **Mail/Passenger** | Time-sensitive, reputation-based |
| **Treasure Hunt** | Historical mode — find sunken treasure |
| **Diplomatic** | Deliver to embargoed ports (high risk/reward) |

---

## 8. Sailing & Navigation

### 8.1 Route Planning

- **Great circle** — Shortest distance, may pass through ice/weather
- **Rhumb line** — Constant bearing, easier navigation
- **Canal routes** — Suez, Panama, Kiel — save distance but pay fees
- **Coastal** — Safer, more ports, longer distance

### 8.2 Weather System

| Element | Source | Impact |
|---------|--------|--------|
| **Wind** | Real-time + historical METAR | Speed (sail), fuel (motor), danger |
| **Storms** | NOAA/ECMWF forecasts | Delay, damage, reroute |
| **Fog** | Local weather | Reduced speed, collision risk |
| **Ice** | NSIDC / real ice charts | Block routes, need ice class ship |
| **Currents** | Ocean current models | Speed modifier, fuel impact |

### 8.3 Random Events

| Event | Era | Effect |
|-------|-----|--------|
| Pirate attack | All | Combat minigame or pay ransom |
| Mutiny | Historical | Negotiate or suppress |
| Mechanical failure | Steam+ | Repair at sea or drift |
| Customs inspection | Modern | Delay, potential fines |
| Smuggling opportunity | All | High reward, caught = huge penalty |
| Castaway rescue | All | Reputation boost, possible reward |

---

## 9. Multiplayer System

### 9.1 Modes

| Mode | Players | Description |
|------|---------|-------------|
| **Hotseat** | 2–4 | Pass-and-play on same PC |
| **LAN** | 2–8 | Local network, simultaneous turns or real-time |
| **Online** | 2–16 | Dedicated server, real-time or async |
| **Cooperative** | 2–4 | Players run one company together |
| **Versus AI** | 1 + 1–7 AI | Competitive with AI opponents |

### 9.2 AI Opponents

- **Personalities:** Aggressive expander, cautious trader, speculator, route monopolist
- **Difficulty levels:** Beginner / Intermediate / Expert / Master
- **AI adapts:** Learns player strategies, counter-trades, undercuts prices

---

## 10. Visual Styles

Players can switch visual styles at any time (or lock per game):

### 10.1 Top-Down / Isometric (Classic)
- 2D sprites or 3D models viewed from above
- Hex or grid-based movement
- Clean UI, information-dense
- Best for: Strategy purists, data-first players

### 10.2 Full 3D
- UE5 Nanite/Lumen quality
- Detailed ship models, animated water, dynamic weather
- Cinematic camera angles
- Best for: Immersion, screenshots, streamers

### 10.3 Paper Map
- Hand-drawn nautical chart aesthetic
- Compass roses, rhumb lines, wind roses
- Ink-and-parchment color palette
- Best for: Historical mode, artistic feel

### 10.4 Data Dashboard
- Bloomberg-terminal inspired
- Real-time graphs, heatmaps, data tables
- Minimal chrome, maximal information
- Best for: Hardcore players, data visualization

### 10.5 Cinematic
- Focus on ship detail, ports, weather
- Almost no UI — contextual popups only
- Best for: Casual play, screenshots, roleplay

---

## 11. Real-World Data Sources

### 11.1 Commodity Prices

| Source | Data | Update Frequency |
|--------|------|-----------------|
| **UN Comtrade** | Global trade flows | Annual |
| **World Bank Commodity Price Data** | 60+ commodities | Monthly |
| **Baltic Exchange** | Freight indices (BDI, BDTI, etc.) | Daily |
| **IMF Primary Commodity Prices** | Broad basket | Monthly |
| **Trading Economics API** | Real-time commodity quotes | Hourly |

### 11.2 Port Data

| Source | Data |
|--------|------|
| **World Port Index (NIMA)** | Port locations, facilities |
| **Lloyd's List** | Port throughput, congestion |
| **MarineTraffic / VesselFinder** | Real ship positions, port calls |
| **UNCTAD Liner Shipping Index** | Port connectivity |

### 11.3 Weather & Ocean

| Source | Data |
|--------|------|
| **NOAA/NWS** | Marine forecasts, storm tracks |
| **ECMWF** | Global weather models |
| **Open-Meteo API** | Free weather API (no key needed) |
| **Copernicus Marine Service** | Ocean currents, sea ice |
| **NSIDC** | Arctic/Antarctic ice extent |

### 11.4 Ship Data

| Source | Data |
|--------|------|
| **IMO GISIS** | Ship registry, specs |
| **Clarksons Research** | Fleet data, newbuildings |
| **VesselValue** | Ship valuations |

### 11.5 Historical Data

| Source | Era | Data |
|--------|-----|------|
| **CLIWOC** (Climatological Database for the World's Oceans) | 1750–1850 | Ship logs, weather |
| **East India Company Records** | 1600–1850 | Trade routes, prices |
| **Slave Voyages Database** | 1526–1866 | Routes (ethical handling) |
| **Historical GIS** | Various | Port development over time |

---

## 12. Monetization & Licensing

### 12.1 Revenue Model

**Phase 1 (Hobby):** Free, open development, community-driven
**Phase 2 (Commercial):** Single purchase ($19.99–$29.99)
- Base game includes Modern + Age of Sail
- Expansion packs: Steam Era, Scenarios, new regions
- No microtransactions, no loot boxes, no pay-to-win

### 12.2 Licensing Strategy

| Component | License | Notes |
|-----------|---------|-------|
| **Game code** | Proprietary | Closed source initially, possible open-source later |
| **Documentation** | CC BY-SA 4.0 | GDD, architecture docs open |
| **Modding API** | Open | SDK provided for community mods |
| **Data pipeline** | MIT | ETL/data fetcher tools open source |
| **Art assets** | Proprietary | Original UE5 assets |
| **Music/SFX** | Licensed or original | Commissioned or royalty-free |

### 12.3 IP Protection

- Trademark "TradeWinds" in relevant classes (USPTO, EUIPO, WIPO)
- Code obfuscation for release builds
- Steam/EGS DRM optional (hobby phase: DRM-free)

---

## 13. UI/UX Design

### 13.1 Screen Flow

```
Main Menu
├── New Game Wizard
│   ├── Era Selection (visual cards)
│   ├── Map Selection (interactive globe)
│   ├── Visual Style (live preview)
│   ├── Difficulty (slider + presets)
│   └── AI Configuration
├── Port Screen
│   ├── Market (buy/sell with sparklines)
│   ├── Shipyard (3D model viewer)
│   ├── Crew (cards with portraits)
│   ├── Warehouse (inventory grid)
│   └── Services (repair, insurance)
├── Navigation Screen
│   ├── Map (zoomable, layers)
│   ├── Route Planner (drag handles)
│   ├── Weather Overlay (animated)
│   └── Fleet Status (ship cards)
├── Finance Screen
│   ├── Balance Sheet
│   ├── Profit/Loss History
│   ├── Stock Price (if publicly traded)
│   └── Loans & Insurance
└── Encyclopedia
    ├── Ports (real-world data)
    ├── Ships (historical specs)
    ├── Commodities (price history)
    └── Events (timeline)
```

### 13.2 Key UI Principles

- **Information density:** Players need lots of data at a glance
- **Contextual help:** Hover for tooltips, click for encyclopedia
- **Keyboard shortcuts:** Power users should rarely need mouse
- **Accessibility:** Colorblind modes, scalable UI, screen reader support

---

## 14. Audio Design

### 14.1 Music

| Context | Style |
|---------|-------|
| **Main menu** | Epic orchestral with nautical themes |
| **Port / Planning** | Relaxed, ambient, tavern-inspired |
| **Sailing (calm)** | Gentle strings, waves, seabirds |
| **Sailing (storm)** | Tense, dramatic, building |
| **Combat / Events** | Percussive, urgent |
| **Victory / Milestone** | Triumphant, brass-forward |

### 14.2 Sound Effects

- **Ship sounds:** Creaking wood, engine thrum, sail flapping, foghorn
- **Environment:** Waves, rain, wind, gulls, port ambience
- **UI:** Paper/map sounds, coin clinks, bell rings
- **Events:** Cannon fire, alarm bells, cheering crew

---

## 15. Post-Launch Content

### 15.1 Free Updates

- New ports (community voting)
- Balance patches
- Bug fixes
- QoL improvements

### 15.2 Paid Expansions

| Expansion | Content |
|-----------|---------|
| **Arctic Routes** | Northern Sea Route, icebreakers, polar ports |
| **The Spice Wars** | Deep historical scenario, colonial competition |
| **Mega-Ships** | Ultra-large vessels, automation, AI routing |
| **Pirates of the Caribbean** | Historical pirate mode, naval combat |

### 15.3 Modding Support

- Steam Workshop integration
- Custom ships, ports, commodities
- Scenario editor
- API for external data sources
- Total conversion support

---

## 16. Appendices

### Appendix A: Glossary

| Term | Definition |
|------|------------|
| **TEU** | Twenty-foot Equivalent Unit (container measure) |
| **DWT** | Deadweight Tonnage (cargo + fuel + crew + stores) |
| **BDI** | Baltic Dry Index (bulk freight cost indicator) |
| **Bunker fuel** | Heavy fuel oil for ships |
| **Ice class** | Ship certification for polar navigation |
| **Lloyd's** | Maritime insurance market |
| **Chandlery** | Ship supply store |
| **Press gang** | Historical forced naval recruitment |

### Appendix B: Reference Games

| Game | What to Learn From |
|------|-------------------|
| **Ports of Call** | Core loop, route planning, cargo matching |
| **Patrician III** | Port development, production chains |
| **Sid Meier's Pirates!** | Combat, exploration, character progression |
| **Merchant Navy** | Ship management realism |
| **Transport Fever 2** | Supply chain depth, modding |
| **Anno 1800** | Production chains, city building |
| **Sea of Thieves** | Nautical atmosphere, ship feel |

### Appendix C: Risk Assessment

| Risk | Likelihood | Impact | Mitigation |
|------|------------|--------|------------|
| Data API changes | High | Medium | Abstract data layer, multiple sources |
| Scope creep | High | High | MVP first, expansions later |
| UE5 learning curve | Medium | Medium | Prototype in Blueprint, refactor to C++ |
| Multiplayer complexity | Medium | High | Start with hotseat, add online later |
| Commercial flop | Low | High | Hobby-first, gauge interest before full commercial |

---

*Document owner: Munin 🐦‍⬛*  
*Next review: After MVP scope definition*
