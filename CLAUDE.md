# Argosy Tides - Claude Code Instructions

## Project Overview

Maritime trading simulation game (Unreal Engine 5.4+, C++20, Rust, Blueprint)

**Current Phase:** Phase 0 Complete - Foundation ready  
**Next Phase:** Phase 1 (MVP) - One port, one ship, one commodity

## Essential Context

### Architecture
- **C++ Core:** `Source/ArgosyTides/` - Game systems (GameInstance, DataManager, Ship, Fleet)
- **Blueprint:** `Content/Blueprints/` - UI, gameplay scripting
- **Rust Pipeline:** `Tools/DataPipeline/` - Real-world data fetching
- **Python:** `Tools/fetch_data_prototype.py` - Quick prototyping

### Key Design Decisions

**ADR-002: Real Data Strategy**
- Real-world data = calibration layer (5% drift/week) + narrative
- Local supply/demand simulation = actual gameplay prices
- Player can choose: historical data vs current trends

**ADR-001: Language Choice**
- C++20: Core engine (UE5 native)
- Blueprint: UI/rapid iteration
- Rust: Data pipeline (compiled binary, no runtime deps)
- Python: One-off scripts, experiments

## Coding Standards

### C++ (Unreal Engine)

**Always:**
- Use `UPROPERTY()` for UObject references (garbage collection)
- Use `UFUNCTION(BlueprintCallable)` for Blueprint exposure
- Include `CoreMinimal.h` first
- Use UE5 types: `FString`, `TArray<T>`, `TMap<K,V>`, `FDateTime`
- Prefix: `U` (UObject), `A` (Actor), `F` (Struct), `b` (bool)
- Log with `UE_LOG(LogTemp, Level, TEXT("msg"))`

**Example:**
```cpp
UCLASS()
class UShip : public UObject {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    int32 MaxCargoCapacity;
    
    UFUNCTION(BlueprintCallable, Category = "Cargo")
    bool LoadCargo(const FString& CommodityId, int32 Amount);
};
```

### Rust

**Always:**
- Use `anyhow::Result` for errors
- Use `tracing` for logging
- Use `?` operator for propagation
- Rate limit APIs (500ms between calls)

**Example:**
```rust
pub async fn fetch_commodities(output_dir: &str) -> Result<()> {
    info!("Fetching commodity prices...");
    
    let client = Client::new();
    let response = client.get(&url).send().await?;
    
    Ok(())
}
```

### Blueprint

**Always:**
- Prefix with `BP_` (e.g., `BP_Ship`)
- Inherit from C++ base classes
- Add comments to complex logic
- Test in PIE (Play In Editor)

## Common Tasks

### Adding New C++ Class
1. Create `.h` and `.cpp` in appropriate `Source/ArgosyTides/` subdirectory
2. Use `UCLASS()`, `GENERATED_BODY()`, `UPROPERTY()`, `UFUNCTION()`
3. Compile project (`.\build.bat`)
4. Create Blueprint child class if needed

### Fetching Data
```bash
# Production (Rust)
cd Tools/DataPipeline
cargo run -- fetch-commodities

# Prototype (Python)
python Tools/fetch_data_prototype.py --all
```

### Building
```powershell
# UE5 project
.\build.bat

# Rust pipeline
cd Tools\DataPipeline
cargo build --release
```

## Phase 1 (MVP) Priorities

**DO:**
- Focus on one port (Oslo), one ship (Panamax), one commodity (grain)
- Implement basic trade loop: buy → sail → sell → profit
- Create simple UI screens
- Add save/load with SQLite

**DON'T:**
- Add multiple ports yet
- Implement weather system yet
- Add captains with personalities yet
- Work on multiplayer (Phase 5)
- Add historical eras (Phase 4)

## Documentation

| File | Purpose |
|------|---------|
| `docs/GDD.md` | Game Design Document |
| `docs/TAD.md` | Technical Architecture |
| `docs/ROADMAP.md` | Implementation phases |
| `SETUP.md` | Installation guide |
| `PHASE0_STATUS.md` | Current progress |
| `.github/AI_INSTRUCTIONS.md` | Detailed AI guide |

## Known Issues

1. **Visual Studio required** for C++ compilation and Rust MSVC linker
2. **Git LFS** needed for binary assets
3. **Hot reload** sometimes fails - full compile recommended
4. **GitHub CLI authentication** - Use `GITHUB_PAT_TOKEN` from `.env` file:
   ```powershell
   $env:GH_TOKEN = $env:GITHUB_PAT_TOKEN
   gh auth status
   ```
   Ensure `.env` is ignored by Git and not committed to the repository.

## When Modifying Code

1. **Check existing patterns** in `Source/ArgosyTides/`
2. **Follow naming conventions** (Hungarian notation for C++)
3. **Add logging** for debugging
4. **Test in Unreal Editor** after compilation
5. **Update documentation** if architecture changes

## References

- UE5 Docs: https://docs.unrealengine.com/5.4/
- Rust Book: https://doc.rust-lang.org/book/
- Project Repo: https://github.com/egkristi/ArgosyTides
