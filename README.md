# RetroPlugg

Windows VST3 audio effect using JUCE 8 and CMake.

## Upload the source
Extract `RetroPlugg_GitHub_Actions_Ready.zip`. Upload the **contents inside** the `RetroPlugg` folder to the root of this repository, keeping `CMakeLists.txt`, `Source/` and `Assets/` paths. The Windows build workflow is already committed at `.github/workflows/build-windows.yml`; do not overwrite it unless desired.

## Build
On pushes to `main`, GitHub Actions builds the Windows VST3 and standalone executable. Find the result under Actions > Build RetroPlugg VST3 (Windows) > latest run > Artifacts. Build success has not yet been verified.
