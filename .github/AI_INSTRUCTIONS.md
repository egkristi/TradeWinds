# Argosy Tides - AI Agent Instructions

## 🎯 Project Overview

**Argosy Tides** is a maritime trading simulation game built with Unreal Engine 5.4+ where players build shipping empires across historical eras using real-world data.

### Key Facts
- **Engine:** Unreal Engine 5.4+
- **Primary Language:** C++20 (core systems)
- **Scripting:** Blueprint (UI, gameplay)
- **Data Pipeline:** Rust 1.78+ (real-world API integration)
- **Prototyping:** Python 3.11+ (quick scripts)
- **Database:** SQLite 3.45+
- **Platform:** PC (Windows, macOS, Linux)
- **Phase:** Phase 0 Complete - Foundation ready

### Repository Structure
```
ArgosyTides/
├── Source/ArgosyTides/     # C++ game code
│   ├── Core/               # Game instance, types
│   ├── Data/               # Data managers
│   ├── Ship/               # Ship & fleet systems
│   └── Economy/            # (TODO) Market, commodities
├── Content/                # UE5 assets
│   ├── Blueprints/         # Blueprint classes
│   ├── Maps/               # Game levels
│   └── DataTables/         # Data assets
├── Tools/
│   ├── DataPipeline/       # Rust data fetcher
│   └── fetch_data_prototype.py
├── Config/                 # UE5 configuration
├── docs/                   # Design documents
└── .github/workflows/      # CI/CD
```

---

## 🏗️ Architecture Principles

### 1. Layered Architecture
```
Game Layer (Blueprint/C++)
    ↓
Data Abstraction Layer (UDataManager)
    ↓
Calibration Layer (5% drift from real data)
    ↓
Local Simulation (Supply/Demand)
    ↓
Real-World APIs (World Bank, Open-Meteo)
```

### 2. Language Ownership
| Layer | Language | Purpose |
|-------|----------|---------|
| Core Engine | C++20 | Performance-critical systems |
| UI/Gameplay | Blueprint | Rapid iteration, designer-friendly |
| Data Pipeline | Rust | API fetching, ETL, CLI tools |
| Prototyping | Python | One-off scripts, experiments |

### 3. Data Strategy (ADR-002)
- **Real data = calibration & narrative** (not direct gameplay)
- **Local simulation = actual game prices**
- **5% drift rate** from real data per game-week
- **Player choice:** Use historical data or update to current trends

---

## 📝 Coding Conventions

### C++ (Unreal Engine)

#### Naming Conventions
```cpp
// Classes: PascalCase with U/A prefix
class UArgosyTidesGameInstance;  // UObject-derived
class AShipActor;                 // AActor-derived
class FCommodityPrice;            // Struct

// Variables: camelCase with Hungarian prefixes
UPROPERTY()
FString ShipName;      // F for FString
int32 MaxCapacity;     // Explicit sized int
float CurrentFuel;     // float
bool bIsPlayerOwned;   // bool with 'b' prefix
TArray<UShip*> FleetShips;  // T-prefixed templates

// Functions: PascalCase
UFUNCTION(BlueprintCallable)
void StartNewGame();

// Member variables: m_ prefix (optional, UE5 style varies)
double m_NetWorth;
```

#### File Organization
```cpp
// Header: ArgosyTidesGameInstance.h
#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArgosyTidesGameInstance.generated.h"

UCLASS()
class ARGOSYTIDES_API UArgosyTidesGameInstance : public UGameInstance
{
    GENERATED_BODY()
    
public:
    UArgosyTidesGameInstance();
    virtual void Init() override;
    virtual void Shutdown() override;
    
protected:
    UPROPERTY()
    UDataManager* DataManager;
};

// Implementation: ArgosyTidesGameInstance.cpp
#include "ArgosyTidesGameInstance.h"
#include "DataManager.h"

UArgosyTidesGameInstance::UArgosyTidesGameInstance()
    : DataManager(nullptr)
{
}
```

#### UE5 Best Practices
1. **Use UPROPERTY()** for all UObject references (garbage collection)
2. **Mark functions UFUNCTION()** for Blueprint exposure
3. **Use GENERATED_BODY()** in all UCLASS/USTRUCT
4. **Override virtual methods** with proper specifiers
5. **Use TSharedPtr/TWeakPtr** for non-UObject references
6. **Log with UE_LOG()** not printf/std::cout

```cpp
// Good
UE_LOG(LogTemp, Log, TEXT("DataManager: Initialized"));
UE_LOG(LogTemp, Warning, TEXT("Invalid commodity ID: %s"), *CommodityId);
UE_LOG(LogTemp, Error, TEXT("Failed to load save game"));

// Bad
printf("Error occurred\n");  // Don't do this
```

### Rust (Data Pipeline)

#### Naming Conventions
```rust
// Modules: snake_case
mod fetch_commodity_prices;
mod db;

// Types: PascalCase
struct CommodityDataPoint {
    ref_date: String,
    value: f64,
}

// Functions: snake_case
async fn fetch_all_commodities(output_dir: &str) -> Result<()> {
    // ...
}

// Constants: SCREAMING_SNAKE_CASE
const MAJOR_PORTS: &[(&str, f64, f64)] = &[
    ("ROTTERDAM", 51.9225, 4.47917),
];

// Variables: snake_case
let commodity_cache = HashMap::new();
```

#### Error Handling
```rust
// Use anyhow for application-level errors
use anyhow::Result;

pub async fn fetch_weather_data(output_dir: &str) -> Result<()> {
    let client = Client::new();
    
    // Use ? operator for propagation
    let response = client.get(&url).send().await?;
    
    // Use tracing for logging
    info!("Fetched weather for {}", port_name);
    warn!("Rate limit approaching");
    error!("Failed to parse response: {}", e);
    
    Ok(())
}

// Use thiserror for library errors
use thiserror::Error;

#[derive(Error, Debug)]
pub enum DataPipelineError {
    #[error("HTTP request failed: {0}")]
    HttpError(#[from] reqwest::Error),
    
    #[error("Database error: {0}")]
    DbError(#[from] rusqlite::Error),
}
```

#### Async Patterns
```rust
// Use tokio runtime
#[tokio::main]
async fn main() -> Result<()> {
    // Parallel fetching
    let (commodities, weather, ports) = tokio::try_join!(
        fetch_commodities(&output_dir),
        fetch_weather(&output_dir),
        fetch_ports(&output_dir)
    )?;
    
    Ok(())
}

// Rate limiting
tokio::time::sleep(Duration::from_millis(500)).await;
```

---

## 🔧 Common Workflows

### Adding a New C++ Class

1. **Create header file** in appropriate directory:
```cpp
// Source/ArgosyTides/Economy/Market.h
#pragma once
#include "CoreMinimal.h"
#include "Market.generated.h"

UCLASS()
class ARGOSYTIDES_API UMarket : public UObject
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable)
    double GetPrice(const FString& CommodityId);
    
    UPROPERTY()
    TMap<FString, double> Prices;
};
```

2. **Create implementation file**:
```cpp
// Source/ArgosyTides/Economy/Market.cpp
#include "Market.h"

double UMarket::GetPrice(const FString& CommodityId)
{
    if (Prices.Contains(CommodityId))
    {
        return Prices[CommodityId];
    }
    return 100.0; // Default price
}
```

3. **Update Build.cs** if new dependencies needed

4. **Compile** and test in Blueprint

### Adding a New Blueprint

1. **Open Unreal Editor** → Content Browser
2. **Right-click** → Blueprint Class
3. **Choose parent class** (e.g., UShip → BP_Ship)
4. **Name it** with BP_ prefix
5. **Add components** and logic visually
6. **Compile** and save

### Fetching Real-World Data

**Option 1: Rust Pipeline (Production)**
```bash
cd Tools/DataPipeline
cargo run -- fetch-commodities
cargo run -- fetch-weather
cargo run -- build-all
```

**Option 2: Python Prototype (Quick Testing)**
```bash
python Tools/fetch_data_prototype.py --all
```

**Option 3: In-Game (Runtime)**
```cpp
// C++ call from game code
DataManager->SetUseLiveData(true);  // Triggers API fetch
```

### Building the Project

**Windows:**
```powershell
# Quick build
.\build.bat

# Or manually
& "C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\Build.bat" `
  ArgosyTidesEditor Win64 Development `
  -project="ArgosyTides.uproject" -log -wait
```

**Generate Visual Studio Project:**
```powershell
# Right-click ArgosyTides.uproject → 
# "Generate Visual Studio project files"
```

---

## 🧠 Design Patterns

### Data Manager Pattern
```cpp
// Abstract data access with caching
class UDataManager : public UObject {
    // Public API - Blueprint accessible
    UFUNCTION(BlueprintCallable)
    FCommodityPrice GetCommodityPrice(FString Id);
    
    // Internal - real-world fetch
    void FetchCommodityPrices();  // Rust integration
    
    // Internal - cache
    TMap<FString, FCommodityPrice> CommodityCache;
};
```

### Calibration Pattern
```cpp
// Gradual drift toward real data (5% per game-week)
void CalibratePrice(double& GamePrice, double RealPrice)
{
    float DriftRate = 0.05;  // 5% per week
    GamePrice = FMath::Lerp(GamePrice, RealPrice, DriftRate);
}
```

### Event System Pattern
```cpp
// Delegate for market events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnPriceChanged, 
    FString, CommodityId, 
    float, NewPrice
);

class UMarket {
    UPROPERTY(BlueprintAssignable)
    FOnPriceChanged OnPriceChanged;
    
    void UpdatePrice(FString Id, float Price) {
        // ... update logic ...
        OnPriceChanged.Broadcast(Id, Price);
    }
};
```

---

## ⚠️ Gotchas & Common Issues

### 1. Unreal Engine Compilation
**Problem:** "Linker errors" or "Module not found"  
**Solution:** 
- Run `.\build.bat` to rebuild
- Delete `Binaries/`, `Intermediate/`, `Saved/`
- Regenerate Visual Studio project files

### 2. Blueprint Not Seeing C++ Class
**Problem:** C++ class doesn't appear in Blueprint picker  
**Solution:**
- Check `UCLASS()` macro is present
- Verify `GENERATED_BODY()` in class
- Compile project in Unreal Editor
- Check module name in Build.cs matches

### 3. Rust MSVC Linker Errors
**Problem:** "linker `link.exe` not found"  
**Solution:**
- Install Visual Studio with C++ workload
- Open "Developer Command Prompt for VS"
- Or set environment: `vcvarsall.bat x64`

### 4. Git LFS Issues
**Problem:** Large binary files not downloading  
**Solution:**
```bash
git lfs install
git lfs pull
```

### 5. Hot Reload Failures
**Problem:** C++ changes don't reflect in Editor  
**Solution:**
- Compile in Visual Studio (not just hot reload)
- Restart Unreal Editor
- Check for compilation errors in Output Log

---

## 📚 Documentation References

| Document | Purpose | Location |
|----------|---------|----------|
| **GDD** | Game Design Document | `docs/GDD.md` |
| **TAD** | Technical Architecture | `docs/TAD.md` |
| **ROADMAP** | Implementation phases | `docs/ROADMAP.md` |
| **ADR-001** | Language choice rationale | `docs/adr/ADR-001-language-choice.md` |
| **ADR-002** | Real data strategy | `docs/adr/ADR-002-real-data-strategy.md` |
| **SETUP** | Installation guide | `SETUP.md` |
| **PHASE0_STATUS** | Current progress | `PHASE0_STATUS.md` |

---

## 🎮 Phase 1 (MVP) Priorities

When working on Phase 1, focus on:

1. **One Port (Oslo)**
   - Market screen
   - Shipyard
   - Services (refuel, repair)

2. **One Ship (Panamax)**
   - Buy/sell functionality
   - Cargo loading/unloading
   - Basic stats display

3. **One Commodity (Grain)**
   - Price display
   - Buy/sell mechanics
   - Profit calculation

4. **Basic UI**
   - Port screen
   - Navigation screen
   - Fleet overview

5. **Save/Load**
   - SQLite integration
   - Game state persistence
   - Load on startup

**DO NOT** add:
- Multiple ports (yet)
- Weather system (yet)
- Captains with personalities (yet)
- Multiplayer (Phase 5)
- Historical eras (Phase 4)

---

## 🤖 AI-Specific Guidance

### When Modifying C++ Code

1. **Always check for UPROPERTY/UFUNCTION macros**
2. **Include proper headers** (CoreMinimal.h first)
3. **Use UE5 types** (FString, TArray, TMap) not std::
4. **Add Blueprint accessibility** if designers need it
5. **Log with UE_LOG** for debugging

### When Modifying Rust Code

1. **Use Result<T>** for fallible operations
2. **Add tracing::info/warn/error** for logging
3. **Handle errors with ?** operator
4. **Test with cargo test**
5. **Rate limit API calls** (be nice to free APIs)

### When Creating Blueprints

1. **Start from C++ base class**
2. **Use descriptive names** (BP_Ship, UI_PortScreen)
3. **Add comments** to complex logic
4. **Test in PIE** (Play In Editor)
5. **Version control .umap and .uasset files** (LFS)

### When Writing Documentation

1. **Update CHANGELOG.md** for significant changes
2. **Keep README.md** up to date
3. **Document new C++ classes** with Doxygen comments
4. **Update TAD** if architecture changes
5. **Add ADR** for major decisions

---

## 🚀 Quick Start for AI Agents

### First Time Setup
```powershell
# 1. Verify environment
.\setup.bat

# 2. Open in Unreal Editor
ArgosyTides.uproject

# 3. Build C++ project
.\build.bat

# 4. Test Rust pipeline
cd Tools\DataPipeline
cargo build --release
```

### Common Tasks

**Add new ship class:**
1. Create `Source/ArgosyTides/Ship/NewShipClass.h/cpp`
2. Add to `ArgosyTides.Build.cs` if needed
3. Compile
4. Create Blueprint child class
5. Add to DataTable

**Add new API endpoint:**
1. Create `Tools/DataPipeline/src/fetch_new_api.rs`
2. Add to `main.rs` command
3. Test with `cargo run -- fetch-new-api`
4. Integrate with `UDataManager`

**Create new UI screen:**
1. Design in UMG (Unreal Motion Graphics)
2. Create C++ widget class if needed
3. Blueprint for layout
4. Add to GameInstance for management

---

## 📞 Need Help?

- **UE5 Documentation:** https://docs.unrealengine.com/5.4/
- **Rust Book:** https://doc.rust-lang.org/book/
- **Project Issues:** Check `PHASE0_STATUS.md` for known blockers
- **Architecture:** See `docs/TAD.md`
- **Design:** See `docs/GDD.md`

---

*Last Updated: 2026-05-14*  
*Phase: 0 Complete - Foundation Ready*
