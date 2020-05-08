## Stathizzz's build of dwm

Here's my build of dwm.

### FAQ

> What are the bindings?

This is suckless, the source code is the documentation! Check out `config.h`.

### My Patch

- xrdb_dynamic
	This patch uses xrdb to load .Xresources file. Existing patches don't work fully dynamically as they use non-generic options for color names, so they don't work with every .Xresources file. Together with fsignals, dwm can change its colors even after it has started (.ie. via a pywal change) by calling the xrdb signal (i.e. xsetroot -name "fsignals:2" or xsetroot -name "fsignals:xrdb"). As a last option, the user can input the .Xresources file in the config.h which he will be using.

### Patches and features

Patches:
- pertag (one layout per tag)
- true fullscreen and prevents focus shifting
- windows can be made sticky
- stacker patch
- shiftview to cycle tags
- moveresize patch
- gaps around windows and bar
- dwmc
- reads xresources colors
- fsignal support
- xrdb support for changing colors dynamically 
- autostart programs at boot through script files 

Layouts:
- Fibonacci
- Centered Master
- Bstack

Contains a scratchpad accessible with mod+shift+enter

### Please install `libxft-bgra`!

