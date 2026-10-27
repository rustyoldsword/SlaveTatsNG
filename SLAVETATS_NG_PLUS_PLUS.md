# SlaveTats NG ++ (branch `ube`)

Mod page: https://dwemermods.com/mods/4660

A fork of SlaveTatsNG 0.8.2 with two additions. Everything else, including the
Papyrus API and the tattoo JSON format, is unchanged.

## Tattoo textures inside BSA archives (0.9.0)

Upstream checks that a tattoo texture exists with `JContainers.fileExistsAtPath`,
which only sees loose files. A tattoo whose DDS is inside a BSA is silently
dropped, even though the game itself would load it.

This fork asks the game's own resource system instead
(`RE::BSResourceNiBinaryStream`, `texture_exists()` in
`src/ube_texture_resolver.cpp`). It finds the file in loose folders and in every
loaded BSA, so tattoo packs can be shipped as a compressed archive. Results are
cached per path for the session; a texture that cannot be found is logged once
(`texture not found: ...` in `SlaveTatsNG.log`).

Tattoo JSON files must stay loose: SlaveTats reads the tattoo directory with
JContainers `readFromDirectory`, which only looks at the disk.

## UBE / COTR texture routing (0.8.2)

The plugin keeps one tattoo JSON and one texture path per tattoo. While
`synchronize_tattoos` applies overlays, it decides per actor and per area
(Body / Face / Hands / Feet) which texture variant to use:

- **UBE races** (detected from the race editor ID read natively, so
  RaceCompatibilityCondition's Papyrus `GetRace` hook does not interfere):
  every area probes `Data/Textures/Actors/Character/slavetats/UBE/<texture>`.
- **3BA actors with the `COTR` keyword** on their base: only the Face area is
  routed to the UBE variant, because COTR heads use the UBE head UV while
  body, hands and feet stay 3BA.

If the UBE file does not exist the original path is used, so a pack without
UBE variants never produces blank overlays. The same resolver is used for the
`in_bsa == 0` file-existence check in `tattoo.cpp`.

Code: `include/ube_texture_resolver.h`, `src/ube_texture_resolver.cpp`.
Build exactly like upstream SlaveTatsNG (CMake presets + vcpkg). The MSVC build
trims local paths from the DLL (`/d1trimfile`, `/PDBALTPATH`).
