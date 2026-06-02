# Openbox Config Notes
howy cwap.

[this](www.openbox.org/help/Configuration) looks like a pretty dang good resource so far.

openbox is a window manager? i think so. it lets me use windows and I'm only sitting at ~400mb of ram used instead of 700 w/kde and it's much more responsive. now 400 > 200, but still gives me 1600 left to play with, and now I actually have colors and fonts so I think it's worth it atm.

# Getting a Terminal
I'd like to change it's terminal from whatever the default is to Konsole (bc it's installed) and then to Alacritty or something if possible. how do I do that?

## steps
`update-alternatives --config x-terminal-emulator`
then select the number for konsole

added `export TERMINAL="konsole"` to `~/.config/openbox/autostart`
this works. doesn't work w/kitty but that's honestly fine.

# Getting a Background
setting the desktop background with `feh`. `feh --bg-scale /path/to/wallpaper` (--bg-fill will crop instead of stretch). add this to autostart.

# Getting rid of Konsole's scroll bar 
