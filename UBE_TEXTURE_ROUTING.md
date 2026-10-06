# UBE / COTR texture routing (branch `ube`)

Mod page: https://dwemermods.com/mods/4660

This branch keeps one tattoo JSON and one texture path per tattoo. While
`synchronize_tattoos` applies overlays, the plugin decides per actor and per
area (Body / Face / Hands / Feet) which texture variant to use:

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
Build exactly like upstream SlaveTatsNG (CMake presets + vcpkg).
