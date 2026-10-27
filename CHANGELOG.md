# Changes

## 0.9.0 (SlaveTats NG ++)

* Tattoo textures may now live inside BSA archives. The texture existence check uses the game's resource system instead of ``JContainers.fileExistsAtPath`` (loose files only), so packed tattoos are no longer silently skipped. Tattoo JSON files must still be loose.
* The UBE/COTR routing uses the same check, so UBE variants inside archives are found too.
* Local build paths are trimmed from the DLL and from the CommonLib build.

## 0.8.2 (UBE / COTR routing)

* UBE races use ``slavetats\UBE\<texture>`` when that file exists; 3BA actors with the ``COTR`` keyword use it for the Face only.

## 0.8.0

* The boolean field ``gloss`` in tattoos isn't used anymore, it has been replaced by two new float fields, ``glossiness`` and ``specularstrength``.

* Three other new fields have been added to tattoos: ``specularstrength``, ``emissivemult`` and ``glowtexture``.

* Besides the old ``apply_overlay`` function in ``SlaveTats.psc``, a new function ``apply_overlay_ex`` has been added to ``SlaveTatsNG.psc``:

  ```
  bool function apply_overlay_ex(Actor target, bool isFemale, string area, int slot, string path, int color, int glow, float glossiness = 0.0, string bump_path = "", float alpha = 1.0, float specular = 0.0, string glow_path = "", float emissive_mult = 1.0) global native
  ```
  It contains the above mentioned ``gloss`` change and the three new fields for the NiOverride parameters ``SpecularStrength``, ``EmissiveMult`` and ``Texture[glow/detail]``.
  The old Papyrus function in ``SlaveTats.psc`` with boolean ``gloss`` parameter still exists; if ``gloss = true``, it calls ``apply_overlay_ex`` with hardcoded ``glossiness = 5.0`` and ``specularstrength = 5.0`` parameters.

  ```
  bool function apply_overlay(Actor target, bool isFemale, string area, int slot, string path, int color, int glow, bool gloss, string bump = "", float alpha = 1.0) global native
  ```
  Note: ``apply_overlay/apply_overlay_ex`` only apply NiOverride overlays, they don't change the SlaveTats JContainer tattoos, so they shouldn't be called directly. Instead edit the SlaveTats tattoos with JContainer or SlaveTats functions, and then call ``synchronize_tattoos``.

* The tattoo version (``.SlaveTats.version``) of actors is changed from ``1.0`` to ``2.0``.