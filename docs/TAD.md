# TradeWinds — Technical Architecture Document (TAD)

> **Version:** 1.0  
> **Date:** 2026-05-14  
> **Jira:** MUNIN-70  

---

## 1. Technology Stack

| Layer | Technology | Version | Purpose |
|-------|-----------|---------|---------|
| **Engine** | Unreal Engine | 5.4+ | Core game engine, rendering, networking |
| **Language (Game)** | C++ | C++20 | Core systems, performance-critical code |
| **Language (UI/Gameplay)** | Blueprint | UE5 | Rapid prototyping, UI, gameplay scripting |
| **Language (Tools)** | Rust | 1.78+ | Data pipeline, CLI tools, performance-critical utilities |
| **Database** | SQLite (local) / PostgreSQL (MP server) | 3.45+ / 16+ | Game state, market data, player progress |
| **Networking** | UE5 Netcode + Dedicated Server | — | Multiplayer, authoritative server |
| **Data Fetching** | Rust + reqwest + tokio | — | Real-world commodity, weather, port data |
| **Build System** | Unreal Build Tool (UBT) + CMake | — | Compilation, packaging |
| **CI/CD** | GitHub Actions | — | Automated builds, tests, packaging |
| **Version Control** | Git + Git LFS | — | Source + asset management |
| **Documentation** | MkDocs / GitHub Pages | — | Living documentation |

---

## 2. Project Structure

```
TradeWinds/
├── .github/
│   └── workflows/
│       ├── build-win.yml
│       ├── build-mac.yml
│       ├── build-linux.yml
│       └── release.yml
├── Content/
│   ├── Blueprints/
│   │   ├── Core/
│   │   ├── GameModes/
│   │   ├── Port/
│   │   ├── Ship/
│   │   └── UI/
│   ├── Maps/
│   │   ├── MainMenu.umap
│   │   ├── PortView.umap
│   │   ├── Navigation.umap
│   │   └── WorldMap.umap
│   ├── Meshes/
│   │   ├── Ships/
│   │   ├── Ports/
│   │   └── Environment/
│   ├── Materials/
│   ├── Textures/
│   ├── Sound/
│   └── DataTables/
│       ├── Ships.csv
│       ├── Ports.csv
│       ├── Commodities.csv
│       └── Events.csv
├── Source/
│   ├── TradeWinds/
│   │   ├── TradeWinds.Build.cs
│   │   ├── Core/
│   │   │   ├── GameInstance.h/cpp
│   │   │   ├── SaveGame.h/cpp
│   │   │   └── Settings.h/cpp
│   │   ├── Data/
│   │   │   ├── DataManager.h/cpp      # Abstract data layer
│   │   │   ├── MarketData.h/cpp
│   │   │   ├── WeatherData.h/cpp
│   │   │   └── PortData.h/cpp
│   │   ├── Economy/
│   │   │   ├── Commodity.h/cpp
│   │   │   ├── Market.h/cpp
│   │   │   ├── PriceEngine.h/cpp
│   │   │   └── Contract.h/cpp
│   │   ├── Ship/
│   │   │   ├── Ship.h/cpp
│   │   │   ├── ShipClass.h/cpp
│   │   │   ├── ShipSystem.h/cpp        # Engine, hull, sails
│   │   │   └── FleetManager.h/cpp
│   │   ├── Port/
│   │   │   ├── Port.h/cpp
│   │   │   ├── PortService.h/cpp
│   │   │   └── Shipyard.h/cpp
│   │   ├── Navigation/
│   │   │   ├── RoutePlanner.h/cpp
│   │   │   ├── WeatherSystem.h/cpp
│   │   │   ├── OceanCurrents.h/cpp
│   │   │   └── EncounterSystem.h/cpp
│   │   ├── Multiplayer/
│   │   │   ├── GameSession.h/cpp
│   │   │   ├── TurnManager.h/cpp
│   │   │   └── Replication/
│   │   │       ├── ShipReplication.h/cpp
│   │   │       └── MarketReplication.h/cpp
│   │   ├── AI/
│   │   │   ├── AIOpponent.h/cpp
│   │   │   ├── AIDecision.h/cpp
│   │   │   └── AITrading.h/cpp
│   │   └── UI/
│   │       ├── MainMenu.h/cpp
│   │       ├── PortScreen.h/cpp
│   │       ├── NavigationScreen.h/cpp
│   │       └── HUD.h/cpp
│   └── TradeWinds.Target.cs
├── Tools/
│   ├── DataPipeline/ (Rust crate)
│   │   ├── Cargo.toml
│   │   ├── src/
│   │   │   ├── main.rs
│   │   │   ├── fetch_commodity_prices.rs
│   │   │   ├── fetch_weather.rs
│   │   │   ├── fetch_port_data.rs
│   │   │   ├── build_datatables.rs
│   │   │   ├── update_game_data.rs
│   │   │   └── lib.rs
│   │   └── tests/
│   ├── Build/
│   │   ├── package_game.py
│   │   └── upload_to_steam.py
│   └── Tests/
│       └── run_tests.py
├── Docs/
│   ├── GDD.md
│   ├── TAD.md
│   ├── ROADMAP.md
│   ├── API_INTEGRATION.md
│   └── MODDING_GUIDE.md
├── Config/
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   └── DefaultData.ini
├── Saved/
│   └── (runtime generated)
├── .gitattributes
├── .gitignore
├── LICENSE
├── README.md
└── TradeWinds.uproject
```

---

## 3. Core Systems Design

### 3.1 Game Instance & State Management

```cpp
// TradeWindsGameInstance
class UTradeWindsGameInstance : public UGameInstance {
    UPROPERTY()
    UMarketData* MarketData;
    
    UPROPERTY()
    UWeatherSystem* WeatherSystem;
    
    UPROPERTY()
    UFleetManager* PlayerFleet;
    
    UPROPERTY()
    UDataManager* DataManager;  // Abstracts real-world vs cached data
    
    // Game mode configuration
    EGameEra CurrentEra;
    EVisualStyle VisualStyle;
    float GameSpeed;  // Real-time, accelerated, turn-based
};
```

### 3.2 Data Layer Abstraction

```cpp
// Core principle: Game code never calls APIs directly
// DataManager handles: real-time fetch, caching, offline fallback, historical data

class UDataManager : public UObject {
public:
    // Market data
    UFUNCTION(BlueprintCallable)
    FCommodityPrice GetCommodityPrice(FString CommodityId, FString PortId);
    
    UFUNCTION(BlueprintCallable)
    TArray<FCommodityPrice> GetPriceHistory(FString CommodityId, int32 Days);
    
    // Weather
    UFUNCTION(BlueprintCallable)
    FWeatherForecast GetForecast(float Lat, float Lon, int32 HoursAhead);
    
    // Port data
    UFUNCTION(BlueprintCallable)
    FPortInfo GetPortInfo(FString PortId);
    
    // Ship data
    UFUNCTION(BlueprintCallable)
    FShipSpecs GetShipSpecs(FString ShipClassId, EGameEra Era);
    
private:
    UPROPERTY()
    UMarketDataSource* MarketSource;  // Real API or cached
    UPROPERTY()
    UWeatherDataSource* WeatherSource;
    UPROPERTY()
    UPortDataSource* PortSource;
    
    // SQLite cache for offline play
    sqlite3* LocalCache;
};
```

### 3.3 Market Simulation

```cpp
class UMarket : public UObject {
public:
    // Price calculation
    float CalculatePrice(FString CommodityId, FString PortId);
    
    // Factors affecting price
    UPROPERTY()
    float BasePrice;           // From real-world index
    UPROPERTY()
    float SupplyDemandModifier; // Local port inventory vs demand
    UPROPERTY()
    float SeasonalModifier;     // Harvest times, heating season
    UPROPERTY()
    float EventModifier;        // War, embargo, canal closure
    UPROPERTY()
    float PlayerImpact;         // Large trades move markets
    
    // Formula: Price = Base * (1 + SupplyDemand + Seasonal + Event + Player)
};
```

### 3.4 Ship System

```cpp
class AShip : public AActor {
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FShipClass ShipClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HullIntegrity;  // 0-100%
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EngineCondition;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FuelLevel;  // Or provisions for sailing ships
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CargoLoad;  // Current tonnage
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FCargo> CargoHold;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCrew Crew;
    
    // Systems
    UPROPERTY()
    UShipMovement* Movement;
    UPROPERTY()
    UShipCombat* Combat;  // For historical modes / pirates
};
```

### 3.5 Captain & Crew System

Captains and crew are persistent characters with personality, skills, and relationships.

```cpp
USTRUCT()
struct FCaptainPersonality {
    UPROPERTY()
    float Cautiousness;       // -storm risk, -speed
    
    UPROPERTY()
    float Aggressiveness;     // +speed, +piracy risk
    
    UPROPERTY()
    float Charisma;           // +crew morale, +negotiation
    
    UPROPERTY()
    float Greed;              // +smuggling, -loyalty
    
    UPROPERTY()
    float Courage;            // Flee vs. fight in storms
    
    UPROPERTY()
    float Loyalty;            // 0-100, affects defection/mutiny
};

UCLASS()
class UCaptain : public UObject {
public:
    UPROPERTY()
    FName Name;
    
    UPROPERTY()
    FText Backstory;
    
    UPROPERTY()
    FCaptainPersonality Personality;
    
    UPROPERTY()
    TMap<FName, int32> Skills;  // Navigation, Combat, Trade, Leadership
    
    UPROPERTY()
    int32 ExperienceLevel;
    
    UPROPERTY()
    float Health;  // 0-100, injuries reduce temporarily
    
    UPROPERTY()
    bool bIsAlive;
    
    UPROPERTY()
    FDateTime JoinedDate;
    
    UPROPERTY()
    TArray<FGameEvent> PersonalHistory;
    
    UPROPERTY()
    TMap<FName, float> Relationships;  // With other captains, rivals
    
    // Events
    UFUNCTION()
    void OnStormEncounter(FWeatherConditions Storm);
    
    UFUNCTION()
    void OnPiracyEncounter(FPirateShip Pirates);
    
    UFUNCTION()
    void OnMutinyCheck(float FleetMorale);
    
    UFUNCTION()
    void OnRivalOffer(URivalCompany* Rival, float BribeAmount);
};

USTRUCT()
struct FCrewMember {
    UPROPERTY()
    FName Name;
    
    UPROPERTY()
    ECrewRole Role;  // Sailor, Navigator, Doctor, Cook, Marine, Engineer
    
    UPROPERTY()
    int32 SkillLevel;
    
    UPROPERTY()
    float Morale;
    
    UPROPERTY()
    float Health;
};

USTRUCT()
struct FCrew {
    UPROPERTY()
    int32 Count;
    
    UPROPERTY()
    TArray<FCrewMember> Members;
    
    UPROPERTY()
    float AverageMorale;
    
    UPROPERTY()
    float AverageHealth;
    
    UPROPERTY()
    float MutinyRisk;
    
    // Skills aggregate
    float GetNavigationBonus() const;
    float GetRepairSpeed() const;
    float GetCombatBonus() const;
};
```

### 3.6 Rival System

Rivals are AI opponents with personality, history, and evolving relationships.

```cpp
UCLASS()
class URivalManager : public UObject {
public:
    UPROPERTY()
    TArray<URivalCompany*> ActiveRivals;
    
    UPROPERTY()
    TArray<FRivalHistory> HistoryLog;
    
    UFUNCTION()
    void GenerateRivals(int32 Count, EGameEra Era);
    
    UFUNCTION()
    void OnPlayerAction(FPlayerAction Action);
    
    UFUNCTION()
    void OnRivalAction(FRivalAction Action);
};

UCLASS()
class URivalCompany : public UObject {
public:
    UPROPERTY()
    FName CompanyName;
    
    UPROPERTY()
    FRivalPersonality Personality;
    
    UPROPERTY()
    TMap<FName, float> RelationshipWithPlayer;  // -100 to +100
    
    UPROPERTY()
    TArray<FGameEvent> SharedHistory;  // Events both player and rival participated in
    
    UPROPERTY()
    TArray<AShip*> Fleet;
    
    UPROPERTY()
    float Wealth;
    
    UPROPERTY()
    ECompanyStatus Status;  // Active, Bankrupt, Merged, Defeated
    
    // Rival actions
    UFUNCTION()
    void DecideAction();
    
    UFUNCTION()
    void OfferAlliance();
    
    UFUNCTION()
    void DeclarePriceWar(FString Route);
    
    UFUNCTION()
    void AttemptSabotage();
    
    UFUNCTION()
    void RequestRescue(AShip* Ship);  // Rival in distress — do you help?
};

USTRUCT()
struct FRivalPersonality {
    UPROPERTY()
    ERivalArchetype Archetype;  // Bully, Shadow, Aristocrat, PirateKing, Visionary, Survivor
    
    UPROPERTY()
    float Aggressiveness;       // Attack player routes?
    
    UPROPERTY()
    float Honor;                // Keep agreements? Respect fair play?
    
    UPROPERTY()
    float Cunning;              // Sabotage, espionage, trickery
    
    UPROPERTY()
    float Pride;                // Vengeful when humiliated?
    
    UPROPERTY()
    float Generosity;           // Help others? Share info?
};
```

**Rival AI:**
- Behavior trees with personality-weighted decisions
- Memory system: rivals remember player actions forever
- Grudge tracking: specific grievances, not just generic "hostility"
- Dynamic alliances: rivals ally against dominant player
- Succession: defeated rival's heir may inherit grudges

### 3.7 Risk & Event System

Events are not random dice rolls — they are *situations* with meaningful choices.

```cpp
UCLASS()
class UEventSystem : public UObject {
public:
    UFUNCTION()
    void EvaluateStormRisk(AShip* Ship, FRoute Route, FWeatherForecast Forecast);
    
    UFUNCTION()
    void TriggerStormEvent(AShip* Ship, FWeatherConditions Storm);
    
    UFUNCTION()
    void TriggerPiracyEvent(AShip* Ship, FPirateShip Pirates);
    
    UFUNCTION()
    void TriggerMutinyEvent(AShip* Ship, FCrew Crew);
    
    UFUNCTION()
    void TriggerRivalEvent(URivalCompany* Rival, ERivalEventType Type);
    
    // Player choice resolution
    UFUNCTION()
    void ResolvePlayerChoice(FEventChoice Choice, AActor* Context);
};

USTRUCT()
struct FEventChoice {
    UPROPERTY()
    FText Description;
    
    UPROPERTY()
    float SuccessChance;
    
    UPROPERTY()
    TArray<FEventConsequence> SuccessConsequences;
    
    UPROPERTY()
    TArray<FEventConsequence> FailureConsequences;
    
    UPROPERTY()
    TArray<FText> SuccessFlavour;  // Story text on success
    
    UPROPERTY()
    TArray<FText> FailureFlavour;  // Story text on failure
};
```

**Storm stages:**
1. Warning → player decides: divert, reduce sail, or push through
2. Building → escalating consequences: damage, crew injury, cargo loss
3. Peak → survival choices: heave-to, abandon cargo, captain's courage check
4. Aftermath → assess, decide: limp to port or call rescue

### 3.8 Company Progression

```cpp
class URoutePlanner : public UObject {
public:
    UFUNCTION(BlueprintCallable)
    FRoute CalculateRoute(FVector2D Start, FVector2D End, FRoutePreferences Preferences);
    
    // Route segments
    UPROPERTY()
    TArray<FRouteSegment> Segments;
    
    // Cost calculation
    float CalculateFuelCost(FRoute Route, FShipClass Ship);
    float CalculateTime(FRoute Route, FShipClass Ship, FWeatherForecast Weather);
    float CalculateRisk(FRoute Route, FShipClass Ship);  // Piracy, weather, ice
};
```

### 3.6 Weather System

```cpp
class UWeatherSystem : public UObject {
public:
    // Fetch real weather or use cached/historical
    UFUNCTION(BlueprintCallable)
    FWeatherForecast GetForecast(float Lat, float Lon);
    
    // Impact on sailing
    UFUNCTION(BlueprintCallable)
    float GetSpeedModifier(FWeatherConditions Conditions, FShipClass Ship);
    
    UFUNCTION(BlueprintCallable)
    float GetDamageRisk(FWeatherConditions Conditions, FShipClass Ship);
    
    // Visual representation
    UPROPERTY()
    UMaterialParameterCollection* WeatherParams;
};
```

---

## 4. Networking Architecture

### 4.1 Single-Player

- Local SQLite database
- All simulation runs client-side
- Save/load to local disk

### 4.2 Local Multiplayer (Hotseat)

- Shared screen, pass-and-play
- Same save file, different player states
- Turn-based or real-time with pause

### 4.3 Online Multiplayer

**Architecture:** Authoritative dedicated server

```
Client (Player 1) <--> Dedicated Server <--> Client (Player 2..N)
                          |
                          v
                    PostgreSQL DB
```

**Replication strategy:**
- **Authoritative:** Server owns market state, ship positions, trade transactions
- **Prediction:** Clients predict ship movement, server corrects
- **Compression:** Market data deltas only, not full state

**Turn-based mode:**
- All players submit actions → server resolves → broadcasts results
- Prevents desync, allows async play

### 4.4 AI Opponents

- Run on server (multiplayer) or client (single-player)
- Decoupled from player logic via interface
- Configurable difficulty via behavior trees

---

## 5. Data Pipeline

### 5.1 Architecture

```
External APIs (NOAA, Baltic Exchange, etc.)
    |
    v
Rust Fetcher Tools (Tools/DataPipeline/)
    |
    v
Data Validation & Normalization
    |
    v
SQLite Cache (local) / PostgreSQL (server)
    |
    v
UE5 Data Tables (Content/DataTables/)
    |
    v
In-Game Market & Weather Systems
```

### 5.2 Fetcher Tools

```rust
# Tools/DataPipeline (Rust crate)
// src/fetch_commodity_prices.rs
use reqwest;
use serde_json;
use tokio;

static COMMODITY_APIS: phf::Map<&'static str, &'static str> = phf_map! {
    "baltic_dry_index" => "https://api.balticexchange.com/bdi",
    "world_bank" => "https://api.worldbank.org/v2/commodity",
    // Fallback sources
};

pub async fn fetch_prices() -> Result<Vec<CommodityPrice>, FetchError> {
    // Try primary source
    // Fall back to secondary
    // Store in SQLite cache
    Ok(vec![])
}

pub fn update_game_data() -> Result<(), FetchError> {
    // Generate UE5 DataTable CSV from cached data
    Ok(())
}
```

### 5.3 Offline Fallback

- Game ships with snapshot of real data
- If APIs unavailable, use cached/historical data
- Player notified: "Using cached market data — last updated: YYYY-MM-DD"

---

## 6. Visual Architecture

### 6.1 Render Targets by Style

| Style | Rendering | Key Features |
|-------|-----------|--------------|
| **Top-Down** | Orthographic camera, sprite-based or simple 3D | Performance, information density |
| **Isometric** | Fixed angle, 3D models, no perspective distortion | Classic RTS feel |
| **Full 3D** | Perspective camera, Nanite meshes, Lumen lighting | Cinematic, immersive |
| **Paper Map** | Post-process filters, custom shaders | Hand-drawn aesthetic |
| **Data Dashboard** | Minimal 3D, maximum UI panels | Bloomberg terminal feel |
| **Cinematic** | Dynamic camera, depth of field, weather VFX | Roleplay, screenshots |

### 6.2 World Representation

- **World map:** Sphere mesh with real-world lat/lon projection
- **Ports:** Instanced static meshes (thousands of ports possible)
- **Ships:** Nanite-enabled detailed meshes for close-up, LOD for distance
- **Ocean:** Water plugin with real-time weather interaction
- **Weather:** Niagara VFX for rain, snow, fog, storms

### 6.3 UI Framework

- UMG (Unreal Motion Graphics) for all UI
- CommonUI plugin for platform-agnostic widgets
- Slate for custom editor/debug tools
- Responsive layout: supports 1080p to 4K+

---

## 7. Save System

### 7.1 Save Data Structure

```cpp
UCLASS()
class UTradeWindsSaveGame : public USaveGame {
    UPROPERTY()
    FString SaveVersion;  // For migration
    
    UPROPERTY()
    FDateTime SaveTimestamp;
    
    UPROPERTY()
    EGameEra CurrentEra;
    
    UPROPERTY()
    FPlayerState PlayerState;
    
    UPROPERTY()
    TArray<FShipState> Fleet;
    
    UPROPERTY()
    TMap<FString, FPortState> PortStates;
    
    UPROPERTY()
    TMap<FString, FCommodityPriceSnapshot> MarketSnapshot;
    
    UPROPERTY()
    TArray<FContract> ActiveContracts;
    
    UPROPERTY()
    TArray<FGameEvent> EventHistory;
    
    UPROPERTY()
    int32 TurnNumber;  // For turn-based modes
};
```

### 7.2 Cloud Saves

- Steam Cloud (if distributed via Steam)
- Custom cloud save via REST API (cross-platform)

---

## 8. Testing Strategy

| Test Type | Tool | Scope |
|-----------|------|-------|
| **Unit** | UE5 Automation + pytest | Core systems (market, routing, ship) |
| **Integration** | UE5 Automation | Data pipeline, save/load, networking |
| **UI** | UE5 Automation + manual | All screens, responsiveness |
| **Performance** | UE5 Stat commands | Frame rate, memory, load times |
| **Multiplayer** | Dedicated server tests | Sync, latency, desync detection |
| **Data** | pytest | API fetchers, data validation |

---

## 9. Build & Deployment

### 9.1 CI/CD Pipeline

```yaml
# .github/workflows/build.yml
name: Build TradeWinds
on: [push, pull_request]
jobs:
  build:
    strategy:
      matrix:
        os: [windows-latest, macos-latest, ubuntu-latest]
    steps:
      - uses: actions/checkout@v4
      - name: Setup UE5
        uses: setup-unreal-engine@v1
      - name: Build
        run: ue5-build --target=TradeWinds --config=Shipping
      - name: Test
        run: ue5-test --project=TradeWinds
      - name: Package
        run: ue5-package --platform=${{ matrix.os }}
```

### 9.2 Distribution

| Channel | Format | Notes |
|---------|--------|-------|
| **Steam** | .exe, .app, .sh | Full integration, Workshop, Cloud |
| **Epic** | Same | EGS exclusivity option |
| **itch.io** | Same | Early access, hobby builds |
| **GitHub Releases** | ZIP | Free builds, modders |
| **Direct** | Installer | Corporate/enterprise licensing |

---

## 10. Performance Targets

| Metric | Target | Notes |
|--------|--------|-------|
| **Frame rate** | 60 FPS (min 30) | All visual styles |
| **Load time** | < 10s | From main menu to gameplay |
| **Save time** | < 2s | Large save files |
| **Memory** | < 4GB RAM | Base game |
| **Disk** | < 5GB | Base install |
| **Network** | < 100ms latency | For online multiplayer |

---

## 11. Security & Anti-Cheat

### 11.1 Single-Player
- No anti-cheat needed (it's a single-player game)
- Save file validation (checksums)

### 11.2 Multiplayer
- Server-authoritative design prevents most cheating
- Data validation on server
- Optional: Easy Anti-Cheat (EAC) for competitive modes

### 11.3 Data Integrity
- API responses signed/validated where possible
- Fallback to cached data if API response looks suspicious
- Rate limiting to prevent abuse of external APIs

---

## 12. Modding Architecture

### 12.1 Supported Mods

| Type | Format | Tools |
|------|--------|-------|
| **Ships** | Static mesh + JSON config | Blender/Max + editor |
| **Ports** | Lat/lon + JSON | Spreadsheet + editor |
| **Commodities** | JSON | Text editor |
| **Scenarios** | JSON + Lua/Blueprint | UE5 editor |
| **Visual styles** | Material/shader packs | UE5 editor |
| **Total conversion** | Full project fork | UE5 + source |

### 12.2 Mod API

```cpp
// UTradeWindsModAPI - exposed to Blueprint
UCLASS()
class UTradeWindsModAPI : public UObject {
    UFUNCTION(BlueprintCallable, Category="Modding")
    static void RegisterShipClass(FShipClassConfig Config);
    
    UFUNCTION(BlueprintCallable, Category="Modding")
    static void RegisterPort(FPortConfig Config);
    
    UFUNCTION(BlueprintCallable, Category="Modding")
    static void RegisterCommodity(FCommodityConfig Config);
    
    UFUNCTION(BlueprintCallable, Category="Modding")
    static void AddEvent(FGameEventConfig Config);
};
```

---

## 13. Development Environment

### 13.1 Required Tools

| Tool | Version | Purpose |
|------|---------|---------|
| Unreal Engine | 5.4+ | Game engine |
| Visual Studio / Rider | 2022+ / 2024+ | C++ IDE |
| Blender / Maya | 4.0+ / 2024+ | 3D modeling |
| Substance Painter | 2024+ | Texturing |
| FMOD / Wwise | Latest | Audio middleware |
| Rust | 1.78+ | Data pipeline, CLI tools |
| Git + LFS | Latest | Version control |

### 13.2 Recommended Hardware

| Role | Spec |
|------|------|
| **Development** | RTX 4070+, 32GB RAM, NVMe SSD |
| **Testing (min)** | GTX 1060, 16GB RAM, SSD |
| **Testing (target)** | RTX 3060, 16GB RAM, SSD |

---

*Document owner: Munin 🐦‍⬛*  
*Next revision: After technical prototype review*
