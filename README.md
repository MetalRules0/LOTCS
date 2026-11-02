# Legacy of the Chaos Soul
<img src="resources/wet_dog.png" alt="Icon" width="512" height="512">

> ###### Check out the [discord server](https://discord.gg/pD3qwdBd4f)!
## What is it?
LotCS is a 3D turn-based RPG for Windows 95 or above, similar to the Paper Mario series.

The game is made to run on vintage hardware, leveraging the custom Power3D Engine.
> ###### Note: See [/P3D/](./P3D) for Power3D source code and [API reference](./P3D/README.md).
## Compilation:
> ###### Note: Linux is required to build LOTCS.
1: Install these programs with your package manager:
- WINE
- GCC
- MinGW-i686-GCC

2: Install the [MASM32 SDK](http://www.masm32.com/download.htm) - which is required to assemble Power3D - to your default WINE prefix.

> ###### Note: This can be done by simply running the installer in WINE. When prompted, install to the default path (`C:\masm32`).

3: Clone the repository.

4: Mark `build.sh` as executable.

5: Run `build.sh`.

This will produce `LOTCS.EXE` and `Power3D.dll`. `LOTCS.EXE` is compiled with i586 instructions.
> ###### License: This code is licensed under GNU GPL v3. Read [LICENSE](./LICENSE) for more details.
