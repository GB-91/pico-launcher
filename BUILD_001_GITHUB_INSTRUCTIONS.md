# Build 001 — GitHub Actions instructions

## Recommended method: upload the complete project

1. Make a backup/download of the current fork.
2. Open the fork on GitHub.
3. Upload the contents of this project ZIP to the repository root, preserving folders.
4. Confirm replacement of `arm9/source/App.cpp`.
5. Confirm that these files exist:
   - `arm9/gfx/splashEnhanced01.png` through `splashEnhanced10.png`
   - matching `.grit` files
6. Commit with the message:
   `DSpico Launcher Enhanced Build 001`
7. Open **Actions** → **Build Pico Launcher**.
8. The push normally starts the workflow automatically. Otherwise choose **Run workflow**.
9. Wait for a green check mark.
10. Open the completed workflow and download the artifact **Pico_Launcher**.
11. Extract it and locate `LAUNCHER.nds`.
12. On the microSD, back up the existing `_picoboot.nds` as `_picoboot_backup.nds`.
13. Rename the new `LAUNCHER.nds` to `_picoboot.nds` and copy it to the same location as the old file.
14. Safely eject the microSD and test on the Nintendo DS.

## Test checklist

- Launcher boots without a white screen or freeze.
- Splash appears on the expected screen.
- Logo, title, subtitle and signature are legible.
- A phrase appears at startup.
- Rebooting several times can show different phrases.
- Launcher interface opens normally after the fade.

## Recovery

If the launcher does not start, remove the new `_picoboot.nds` and rename `_picoboot_backup.nds` back to `_picoboot.nds`.

## Important note

Build 001 uses ten pre-rendered splash variants and the launcher's existing cross-fade. The staged appearance of each individual element is deliberately reserved for the next build, after this first hardware test confirms palette, tile conversion, memory use and timing.
