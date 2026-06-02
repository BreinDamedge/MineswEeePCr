-- formatting
vim.opt.expandtab = true    -- spaces instead of tabs
vim.opt.shiftwidth = 4      -- num spaces per indentation level
vim.opt.tabstop = 4         -- number of spaces a tab counts for
vim.opt.softtabstop = 4

-- window commands
vim.keymap.set('n', '<Space>w', '<C-w>', { desc = "window commands" })
vim.keymap.set('n', '<C-h>', '<C-w>h', { desc = "move to left window" })
vim.keymap.set('n', '<C-l>', '<C-w>l', { desc = "move to right window" })
vim.keymap.set('n', '<C-k>', '<C-w><Up>', { desc = "move to upward window" })
vim.keymap.set('n', '<C-j>', '<C-w><Down>', { desc = "move to downward window" })

-- tab commands
vim.keymap.set('n', '<S-h>', 'gT', { desc = "prev tab" })
vim.keymap.set('n', '<S-l>', 'gt', { desc = "next tab" })
vim.keymap.set('n', '<Space>t', ':tabnew<CR>', { desc = "new tab" })

-- close all
vim.keymap.set('n', '<Space>qq', ':only<CR>:tabonly<CR>:q<CR>', { desc = "close everything" })

-- my backspace bind
vim.keymap.set('i', '<C-H>', '<C-w>', { desc = "delete prev word in insert mode" }) -- H is <BS> for some reason

-- file explorer baybeee (netrw config)
vim.keymap.set('n', '<Space>e', ':Lexplore<CR>', { desc = "open file explorer" })
vim.g.netrw_keepdir = 1
vim.g.netrw_banner = 0
vim.g.netrw_winsize = 20
vim.g.netrw_list_hide = [[\(^\|\s\s\)\zs\.\S\+]]  -- hide dotfiles in netrw on load

-- highlighting in visual mode
vim.api.nvim_set_hl(0, 'Visual', { ctermbg = 'magenta', bold = true })

-- active tab color
vim.api.nvim_set_hl(0, "TabLine", { ctermbg = 'cyan', bold = true })
vim.api.nvim_set_hl(0, "TabLineFill", { ctermbg = 'cyan', bold = true })

-- get ur dang line numbers! on and relative
vim.opt.relativenumber = true
vim.opt.number = true
vim.opt.cursorline = true
vim.api.nvim_set_hl(0, "CursorLineNr", { ctermbg = "magenta", bold = true })
vim.api.nvim_set_hl(0, "LineNr", { ctermbg = "cyan", bold = true })
vim.api.nvim_set_hl(0, "CursorLine", { ctermbg = "none", bold = false }) -- highlight active line

-- keep the active line in the center of the screen
vim.opt.scrolloff = 999
vim.opt.fillchars = { eob = " " }

-- display datetime in status line right
vim.opt.statusline = "%<%f %h%m%r%=%-14.(%l,%c%V%) %{strftime('%Y-%m-%d %H:%M')}"

-- setup clipboard
vim.opt.clipboard = "unnamedplus"
