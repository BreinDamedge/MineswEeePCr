# here lies the project notes
this file is for any story related notes.

I have managed to compile a hello world and I'm learning a bunch about configless neovim. currently having a blast.

now I want to check the system battery percentage bc no de means I can't see it. the interwebs says: `cat /sys/class/power_supply/BAT0/capacity` might do it. that totally works I'm at 59% rn. I'll alias that command to something in a moment.

how do I alias things in bash permanently? I created a `.bash_aliases` file (in the bottom of `.bashrc` it calls that file to run everything in it, you could also put it directly in .bashrc if you really wanted) and added the `battery` alias which prints out your battery percentage using that above command.

alrighty so I was adding this to my github and I generated a key. I needed to share it to my other computer so that I could add it to github. I wanted a way to send it from this machine to the other so i did `curl -d "$(cat <my_key_file>)" <my_other_computers_ip>` and then I ran a python post request echoer on my other laptop which worked great for sending it.

YUUUSS it totally worked!!! this is also the first time I've used ssh keys for github. this is awesome :D

now I'm going to start on the coding/architecture.
man it's been so long since I've used c. shall we use a struct for the game state? sure!

okay that went well. now I'm getting an auth error w/github. that's weird. I'll fix that tomorrow.
real quick I'll add to my nvim config to do movement up and down between windows.

It is a new day (5.12.2026)
First I'll fix my ssh-agent config so that the github key loads and then I can actually push from this machine...
so I added an ssh config file (~/.ssh/config) with the content:
```
Host github.com
    HostName github.com
    User git
    IndentityFile ~/.ssh/<file_name>
```
and now I'll see if that worked.
nope! that gave "bad configuration option: identityfile" so I'll see what that's about. nope I wrote "Indentity" lmao.
