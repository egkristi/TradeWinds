# Argosy Tides - Development Setup Guide

## Prerequisites

### Required Software

1. **Unreal Engine 5.4+**
   - Already installed ✓
   - Verify: Open Epic Games Launcher → Library → Engine Versions

2. **Visual Studio 2022** (Required for C++ development)
   - Download: https://visualstudio.microsoft.com/downloads/
   - Workloads to install:
     - ✓ "Game development with C++"
     - ✓ "Desktop development with C++"
   - Individual components:
     - ✓ MSVC v143 - VS 2022 C++ x64/x86 build tools
     - ✓ Windows 10/11 SDK
     - ✓ CMake tools for Windows
     - ✓ Git for Windows

3. **Git and Git LFS**
   - Already installed ✓
   - Git LFS initialized ✓

4. **Rust** (for data pipeline tools)
   - Already installed ✓
   - Requires Visual Studio C++ tools for MSVC target
   - Alternative: Install WSL2 and use GNU target

5. **Python 3.11+** (for prototyping scripts)
   - Download: https://www.python.org/downloads/
   - Or use: `winget install --id Python.Python.3.11`

## Installation Steps

### Step 1: Install Visual Studio 2022

```powershell
# Download and run Visual Studio Installer
winget install --id Microsoft.VisualStudio.2022.Community --silent `
  --custom "--add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended"
```

**OR** manually:
1. Download Visual Studio Installer from https://visualstudio.microsoft.com/
2. Run installer
3. Select "Game development with C++" workload
4. Click Install

### Step 2: Verify Visual Studio Installation

```powershell
# Check for Visual Studio installation
$vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
& $vsWhere -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64
```

### Step 3: Configure Rust for MSVC

After Visual Studio is installed:

```powershell
# Open Developer Command Prompt for VS 2022
# Or run:
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

# Verify Rust can find MSVC
rustc --version
cargo --version

# Build data pipeline
cd Tools/DataPipeline
cargo build --release
```

### Step 4: Build Unreal Engine Project

```powershell
# Method 1: Open in Unreal Editor (generates project files)
cd c:\Users\willm\code\ArgosyTides
& "C:\Program Files\Epic Games\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe" ArgosyTides.uproject

# Method 2: Build from command line
& "C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\Build.bat" `
  ArgosyTidesEditor Win64 Development `
  -project="c:\Users\willm\code\ArgosyTides\ArgosyTides.uproject" `
  -log -wait
```

### Step 5: Verify Setup

```powershell
# Check Git status
git status

# Check Git LFS
git lfs ls-files

# Verify project structure
tree /F /A
```

## Troubleshooting

### Rust Build Fails with "linker `link.exe` not found"

**Solution:** Install Visual Studio with C++ workload (see Step 1)

### Unreal Editor Won't Open Project

**Solution:**
1. Right-click `.uproject` file
2. Select "Switch Unreal Engine Version"
3. Choose 5.4+
4. Try opening again

### Git LFS Files Not Downloading

**Solution:**
```powershell
git lfs install
git lfs pull
```

## Next Steps

1. **Open project in Unreal Editor**
   - Double-click `ArgosyTides.uproject`
   - Wait for shader compilation
   - Verify no compilation errors

2. **Create first Blueprint**
   - Open Content Browser
   - Right-click → Blueprint Class
   - Create BP_TestShip based on UShip class

3. **Test data pipeline** (after VS installation)
   ```powershell
   cd Tools/DataPipeline
   cargo run -- build-all
   ```

## Current Status

✅ Project structure created
✅ Git repository initialized
✅ Git LFS configured
✅ Unreal Engine project files created
✅ C++ module skeleton created
✅ Rust data pipeline code written
✅ CI/CD workflows configured

⏳ Waiting for: Visual Studio installation to complete builds

## References

- [Unreal Engine 5.4 Documentation](https://docs.unrealengine.com/5.4/)
- [Rust on Windows](https://rust-lang.github.io/rustup/installation/windows.html)
- [Visual Studio Setup for UE5](https://docs.unrealengine.com/5.0/en-US/setting-up-visual-studio-development-environment-for-unreal-engine/)
