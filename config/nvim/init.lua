-- Enahnce Editor
vim.opt.number = true
vim.opt.expandtab = true
vim.opt.shiftwidth=4
vim.opt.tabstop=4

-- key map
vim.g.mapleader = " "

vim.api.nvim_set_keymap("i", "<leader>jk", "<ESC>", {noremap = true })
--
-- package manager: packer
require("packer-plugins")
-- link: https://github.com/rockerBOO/awesome-neovim#search

