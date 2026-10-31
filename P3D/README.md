## POWER3D: 3D software rendering engine in i386 assembly.

To assemble (Windows/Linux): Install the [MASM32 SDK](http://www.masm32.com/download.htm) & run `makedll.bat`. Use WINE if required.

This process will output two (useful) files: `power3d.dll` and `power3d.lib`.

## API REFERENCE:
uint32_t color is stored in this format: `0xFFRRGGBB`, where FF is unused.

### Initialization
`_SetWindowTitle(char* title)`: Sets the title of any windows created. Call at any time to update the main window.

`_SetCoreProc(void (*funcptr)(), char type)`: Sets one of four functions which P3D will run:
- Type 1: Runs once every timer tick
- Type 2: Runs once every frame (set by Framerate)
- Type 3: Runs when "Debug > Debug Function" is pressed
- Type 4: Runs on engine startup

`_SetFrameRate(int MS)`: Sets the maximum frame time (In Milliseconds)

`_Timer_new(int TicksPerSecond)`: Sets the timer's TPS.

`_StartEngine()`: Starts the main POWER3D loop, running the functions from `_SetCoreProc()`.

```c
_SetWindowTitle("LOTCS");
_Timer_new(20); //Gameloop 20 times per second
_SetFrameRate(16); //Draw every 16ms
_SetCoreProc(&gameloop, 1);
_SetCoreProc(&videoloop, 2);
_StartEngine();
```

### System Interaction
`_GetFrameRate()`: Returns milliseconds since last frame

`_iskeydown(short key)`: Checks if the requested key is currently being pressed. Returns either 0 (Unpressed) or 1 (Pressed).

Allowed keys:
- 1 / LKEY_UP
- 2 / LKEY_DOWN
- 3 / LKEY_LEFT
- 4 / LKEY_RIGHT
- 5 / LKEY_A
- 6 / LKEY_B
- 7 / LKEY_R
- 8 / LKEY_L
- 9 / LKEY_PAUSE
- 10 / LKEY_MISC

These key-codes map to this list of [Microsoft Virtual Key Codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes), respectively:
- 0x57
- 0x53
- 0x44
- 0x41
- 0x20
- 0x10
- 0x51
- 0x45
- 0x3A
- 0x40

### Drawing
`_DrawLine(short x0, short y0, short x1, short y1, uint32_t color, uint32_t vbuffer)`

`_DrawWirePolygon(void *polygon)`

`_DrawSky(uint32_t flags, uint32_t color)`: Fills screen with specific color. Flags is reserved and should be `0`.

`_SetPixel(short x, short y, uint32_t color)`: Sets pixel (x, y) to color.

### Drawing Text

`_Print_string(int x, int y, char* text, uint32_t color)`: Renders any C string to the window.

`_Print_char(int x, int y, char text, uint32_t color)`: Renders any char literal to the window.

`_Print_int(int x, int y, int text, uint32_t color)`: Renders any number to the window.

X/Y automatically clipped to screen. Every char is rendered as an 8x8 sprite. Be sure to render text AFTER the scene/drawsky to prevent unreadable text.
```c
_Print_string(4, 4, “Hello,\nWorld!”, 0xFFFFFFFF); // Displays the multi-line "Hello, [Line Break] World!"
_Print_char(100, 50, 'A', 0xFFFF0000); //Displays the letter A
_Print_int(40, 24, 38, 0xFFFFFF00); //Displays the number 38
```

### TO DOCUMENT:
`_DrawLine`, `_DrawWirePolygon`
