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

# config things
to find your config file you can run `:echo stdpath('config')` (shoutout that youtube series).
your config file is located at `/home/brein/.config/nvim`, and the file is init.lua

things you've changed are:
- you set your tabs to spaces and your number of spaces to 4
