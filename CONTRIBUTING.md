# Contributing to Argosy Tides

Thank you for your interest in contributing to Argosy Tides! This document provides guidelines and instructions for contributing to the project.

## 🎯 Project Overview

**Argosy Tides** is a maritime trading simulation game built with Unreal Engine 5.4+.

- **Current Phase:** Phase 0 Complete - Foundation Ready
- **Next Phase:** Phase 1 (MVP) - One port, one ship, one commodity
- **Languages:** C++20, Blueprint, Rust, Python
- **License:** MIT

## 📋 How to Contribute

### 1. Check Existing Issues
Before starting work, check the [Issues](https://github.com/egkristi/ArgosyTides/issues) page to:
- See if the feature/bug is already reported
- Find issues labeled "good first issue" or "help wanted"
- Understand current priorities

### 2. Create a New Issue
If you don't see an issue for what you want to work on:
- Use the appropriate issue template
- Provide clear description and context
- Wait for maintainer feedback before starting major work

### 3. Fork and Clone
```bash
# Fork the repository on GitHub, then:
git clone https://github.com/YOUR_USERNAME/ArgosyTides.git
cd ArgosyTides

# Install Git LFS
git lfs install
git lfs pull
```

### 4. Set Up Development Environment
See [SETUP.md](SETUP.md) for detailed setup instructions.

**Required:**
- Unreal Engine 5.4+
- Visual Studio 2022 with C++ workload
- Rust 1.78+ (for data pipeline)
- Git LFS

### 5. Create a Branch
```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/issue-123
```

**Branch naming:**
- `feature/` - New features
- `fix/` - Bug fixes
- `docs/` - Documentation updates
- `refactor/` - Code refactoring
- `test/` - Test additions

### 6. Make Changes

#### C++ Code
- Follow UE5 coding conventions (see `.cursorrules`)
- Use `UPROPERTY()` for all UObject references
- Use `UFUNCTION(BlueprintCallable)` for Blueprint exposure
- Add logging with `UE_LOG()`
- Compile and test in Unreal Editor

#### Rust Code
- Follow Rust idioms (see `.cursorrules`)
- Use `anyhow::Result` for error handling
- Use `tracing` for logging
- Add tests where appropriate
- Run `cargo test` before committing

#### Blueprint
- Prefix with `BP_`
- Inherit from C++ base classes when possible
- Add comments to complex logic
- Test in PIE (Play In Editor)

#### Documentation
- Keep Markdown files concise and well-organized
- Update CHANGELOG.md for significant changes
- Keep README.md up to date

### 7. Commit Your Changes

Use [Conventional Commits](https://www.conventionalcommits.org/):

```bash
git commit -m "feat: add new ship class"
git commit -m "fix: resolve compilation error in DataManager"
git commit -m "docs: update README with setup instructions"
git commit -m "test: add unit tests for Rust data pipeline"
```

**Types:**
- `feat:` - New feature
- `fix:` - Bug fix
- `docs:` - Documentation only
- `style:` - Formatting only (no code change)
- `refactor:` - Code refactoring
- `test:` - Adding tests
- `chore:` - Maintenance tasks

### 8. Push and Create Pull Request

```bash
git push origin feature/your-feature-name
```

Then on GitHub:
1. Click "Compare & pull request"
2. Fill in PR description
3. Reference related issues (e.g., "Closes #123")
4. Wait for review

### 9. Code Review

- Respond to feedback promptly
- Make requested changes
- Be open to suggestions
- Keep discussions professional and constructive

## 🧪 Testing

### C++ Code
1. Compile with `.\build.bat`
2. Test in Unreal Editor (Play In Editor)
3. Check Output Log for errors
4. Verify Blueprint integration

### Rust Code
```bash
cd Tools/DataPipeline
cargo test
cargo build --release
```

### Python Scripts
```bash
python Tools/fetch_data_prototype.py --all
```

## 📝 Code Style

### C++ (Unreal Engine)
```cpp
// Use UPROPERTY for garbage collection
UPROPERTY(BlueprintReadWrite, Category = "Stats")
int32 MaxCargoCapacity;

// Use UFUNCTION for Blueprint exposure
UFUNCTION(BlueprintCallable, Category = "Cargo")
bool LoadCargo(const FString& CommodityId, int32 Amount);

// Log with UE_LOG
UE_LOG(LogTemp, Log, TEXT("Loaded %d tons"), Amount);
```

### Rust
```rust
// Use anyhow::Result
pub async fn fetch_data() -> Result<()> {
    info!("Fetching data...");
    let response = client.get(&url).send().await?;
    Ok(())
}

// Use tracing for logging
use tracing::{info, warn, error};
```

### Blueprint
- Prefix: `BP_Ship`, `UI_PortScreen`
- Inherit from C++ classes
- Comment complex graphs

## 🚫 What NOT to Do

### Don't Add Yet (Future Phases)
- Multiple ports (Phase 2)
- Weather system (Phase 2)
- Historical eras (Phase 4)
- Multiplayer (Phase 5)
- AI opponents with personalities (Phase 6)

### Don't Commit
- Binary files (use Git LFS)
- `Binaries/`, `Intermediate/`, `Saved/` directories
- Rust `target/` directory
- `.vs/`, `.idea/` IDE files
- Large asset files without LFS

## 🐛 Reporting Bugs

Use the [Bug Report](.github/ISSUE_TEMPLATE/bug_report.md) template.

Include:
- Clear description
- Steps to reproduce
- Expected vs actual behavior
- Environment (UE5 version, OS, etc.)
- Screenshots/logs if applicable

## 💡 Feature Requests

Use the [Feature Request](.github/ISSUE_TEMPLATE/feature_request.md) template.

Include:
- Problem statement
- Proposed solution
- Alternatives considered
- Phase alignment (see ROADMAP.md)

## 📞 Questions?

- Check [Documentation](docs/)
- Review [AI_INSTRUCTIONS.md](.github/AI_INSTRUCTIONS.md)
- Search existing [Issues](https://github.com/egkristi/ArgosyTides/issues)
- Open a new [Issue](https://github.com/egkristi/ArgosyTides/issues/new)

## 🎖️ Recognition

Contributors will be acknowledged in:
- README.md Contributors section
- CHANGELOG.md
- Release notes

Thank you for contributing to Argosy Tides! 🌊🚢
