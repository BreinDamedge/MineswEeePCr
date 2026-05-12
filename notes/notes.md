# here lies the project notes
this file is for any story related notes.

I have managed to compile a hello world and I'm learning a bunch about configless neovim. currently having a blast.

now I want to check the system battery percentage bc no de means I can't see it. the interwebs says: `cat /sys/class/power_supply/BAT0/capacity` might do it. that totally works I'm at 59% rn. I'll alias that command to something in a moment.

how do I alias things in bash permanently? I created a `.bash_aliases` file (in the bottom of `.bashrc` it calls that file to run everything in it, you could also put it directly in .bashrc if you really wanted) and added the `battery` alias which prints out your battery percentage using that above command.
