# ADR-001: Language Choice

## Status

✅ **Accepted**

## Context

Argosy Tides requires multiple languages for different layers:
- Core game engine (performance-critical)
- UI/rapid prototyping
- Data pipeline (real-world API fetching)
- Build tooling

**Constraints:**
- Hobby project with potential commercialization
- Small team (1 developer + AI assistance)
- Cross-platform (Windows, macOS, Linux)
- Real-world data integration required
- Modding support desired

## Decision

Use a **polyglot stack** with clear ownership:

| Layer | Language | Version | Use Case | Owner |
|-------|----------|---------|----------|-------|
| **Core Engine** | C++ | C++20 | Performance-critical systems, UE5 integration | Game programmer |
| **UI/Gameplay** | Blueprint | UE5 | Rapid prototyping, UI, gameplay scripting | Designer + programmer |
| **Data Pipeline** | Rust | 1.78+ | API fetching, ETL, CLI tools | Backend/devops |
| **Prototyping** | Python | 3.11+ | One-off scripts, quick experiments | Any |
| **Build System** | C++ + CMake | — | Compilation, packaging | Game programmer |

## Rationale

### Why C++ for Core?
- **Unreal Engine 5** is C++ native — best performance, full feature access
- C++20 provides modern features (concepts, coroutines, ranges)
- Industry standard for AAA game development
- Compile-time type safety for large codebase

### Why Blueprint for UI?
- **Rapid iteration** — visual scripting is 10× faster for UI layout
- **Designer-friendly** — non-programmers can prototype
- **Seamless C++ integration** — hot-reload, call C++ from Blueprint, vice versa
- **UE5 recommended pattern** — official Epic workflow

### Why Rust for Data Pipeline?
- **Compiled binary** — no Python interpreter dependency on user machines
- **Performance** — native speed for API fetching and processing
- **Portability** — single static binary for Win/Mac/Linux
- **No dependency hell** — Cargo manages crates, unlike pip/virtualenv
- **Memory safety** — no crashes from null pointers or use-after-free
- **Future-proof** — if data pipeline grows, Rust scales better than Python

### Why Python stays?
- **Prototyping speed** — 5-line script vs. 50-line Rust
- **Data science ecosystem** — pandas, numpy for analysis
- **One-off tools** — not shipped with game, developer-only
- **Familiarity** — most developers know Python

## Consequences

### Positive
- Each language used where it excels
- Rust pipeline removes runtime dependency risk
- Blueprint allows designer autonomy
- C++ ensures performance for core loop

### Negative
- **Cognitive load** — developer must know 4 languages (or AI must bridge)
- **Build complexity** — multiple toolchains (MSVC/Clang/GCC + Cargo + Python)
- **Debugging friction** — crossing C++/Blueprint boundary requires expertise
- **Rust learning curve** — if developer unfamiliar with ownership/borrowing

### Mitigations
- **Clear boundaries** — language interfaces are well-defined (API contracts)
- **AI assistance** — Claude/Copilot bridges language gaps
- **Documentation** — this ADR + code comments explain choices
- **Rust for data only** — not in hot path, performance less critical than correctness

## Alternatives Considered

| Alternative | Pros | Cons | Why Rejected |
|-------------|------|------|--------------|
| **Python for data pipeline** | Fast to write, familiar | Runtime dependency, slow, packaging hell | Rust's compiled binary wins for user experience |
| **C# (Unity)** | Familiar, good tooling | Would require engine switch (UE5 chosen first) | UE5's Nanite/Lumen/C++ ecosystem preferred |
| **Pure C++** | Single language | Slow iteration for UI, verbose for data | Blueprint + Rust split is optimal |
| **Pure Blueprint** | No C++ | Performance limits, spaghetti code | C++ needed for systems programming |

## References

- [TAD Section 1: Technology Stack](../TAD.md#1-technology-stack)
- [TAD Section 5: Data Pipeline](../TAD.md#5-data-pipeline)
- Epic Games: [UE5 C++ vs Blueprint guide](https://docs.unrealengine.com/5.0/en-US/blueprints-vs-cplusplus-in-unreal-engine/)
- Rust Book: [Why Rust?](https://doc.rust-lang.org/book/ch00-00-introduction.html)

---

*Decided: 2026-05-14*  
*Author: Munin 🐦‍⬛*  
*Reviewers: Claude AI (advisory)*
