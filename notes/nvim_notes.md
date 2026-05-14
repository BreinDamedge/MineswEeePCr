# Neovim (no cfg) Notes

# keybinds
`:e .` : open file explorer in cwd
`:tabe` or `:tabnew` : opens a new tab
`gt`/`gT` : goes to the next/previous tab
`:tabclose` or `:tabc` : closes the current tab 
`:tabonly` or `:tabo` : closes all but the current tab
`:nohl` : remove highlights after searching
`ctrl+\` then `ctrl+n` : return to normal mode to get out of a terminal w/out closing it (VERY USEFUL)
`:tabmove N` : moves the current tab. position is 0 indexed and when no arg is provided it moves it to the end.
`:split` : splits horizontally
`window+<Down>` : move down a window (<Up>, h, l do their respective directions) (window by default is <C-w> I've rebound it to <Space>w.
`:e <filename>` : open's a file for editing 
`window + c` : close focused window

# Leader
default leader key is `ctrl+w`. New windows can be made w/leader + s, or leader+v for a vertical split.

# config things
to find your config file you can run `:echo stdpath('config')` (shoutout that youtube series).
your config file is located at `/home/brein/.config/nvim`, and the file is init.lua

things you've changed are:
- you set your tabs to spaces and your number of spaces to 4
you should figure out how to change your leader key to space
so I didn't change my leader key, I changed my window commands "leader" thing from <C-w> to <Space>w. also added the <S-h> and <S-l> to move between windows.

- you made `<Space>e` open a new window and the explorer
