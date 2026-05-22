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

I'm working on the actual board thing now and trying to print stuff with extra c files. I need to learn how to use make to build the project w/multiple files. I mean I don't need to but it'd be fun. I'll get to that later. working rn on board representation and printing everything out. the other two config things you should do are:
- [ ] shift+space -> _
    - this is gonna be tough so I'll leave it for later
- [x] <C-BS> -> <C-w> (in instert mode)

okay so I'm printing out the board as a silly little grid of xs atm which works. I'll have to find a better more readable method. I'll get to that in a bit.


now I need to design the board struct.
# Board Data
so the board has it's rows and columns, and it needs to know where all the bombs are. so bombs need to be... bombs can be kept track of as... oh, just make the board a 2d array of ints. -1 is a bomb and all the other numbers are a count. This could be a good excuse to learn to use an enum.

Still fighting the dang seg fault. it is being triggered when I access the rows element at least. so it's not actually my freeing situation. very strange. might learn to use gdb, that or I'll just tinker. I'm in the car right now so I'll have to just tinker about.

hey uh... when you uh- when you malloc a board you should uh- you should return the pointer you just alloced. like- not returning anything from a function that returns something should def be an error or like a warning but by default I guess not.

You should make the board data a contiguous 1d array and index into it w/ the rc trick bc it's just better. you should fix this dealloc error first probably so you can figure out what it is but honestly who cares just do the 1d and fix the bug if it's still there. also- what was it oh yeah, you should learn how to use macros even though you should avoid them (I hear they're evil) but also they might be useful one day. you might be able to make a macro for the rc math for indexing into a 2d array but might as well just type it out. also you've been told to make the bar str not a variable length array (VLA) bc they're "weird" so you should read about why they're weird, and until then just use a static 2048 char array and don't support boards bigger than 1k^2 bc the EeePC is a potato anyway.

also uh good reminder: don't go optimization crazy. this is your first draft. and it's minesweeper.

yeah the invalid pointer bug is inconsistant. I'm not checking that the mallocs succeed so maybe it's that? probably not tho. I'll make the thing a single buffer.

was gonna make a whole function to find the width of the numbers to be printed but the largest that a number can be for bomb count is 9 which is still one digit which is less than -1 so just make it two wide. actually make it 1 wide and just print bs in the bombs. 

counting is complete now I think. now it also checks in bomb placement if you put a bomb where one already was and it adds an iteration to the for loop.

I should add an enum for bomb, and also flag except that the flag enum will go with the dirt & empty enums in the display/occupation grid thingy... that needs a name ig.

you made the enum and then you played a bunch of minesweeper.

next thing to do is mark spots as displayable.
