set ambiwidth=double
set autochdir
"set colorcolumn=80
set confirm
set cursorcolumn
set cursorline
set display=lastline
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set fileencoding=utf-8
set foldmethod=syntax
set laststatus=2
set nocompatible
set number
set pastetoggle=<F4>
set showcmd
set statusline=%m%r%F[%Y]%=[%{&ff},%{&enc}]\ [+U%04B]\ %04l,%04v\ %03p%%
set viminfo='1000,f1,<500,:50,@50,/50,h,c,n~/.vim/viminfo
set visualbell
set wildmenu
set shiftwidth=4
set tabstop=4
"set expandtab
set cindent

if has("gui_running")
	set guifontwide=文泉驿等宽正黑\ 9
	set guifont=文泉驿等宽正黑\ 9
	"set guifontwide=Droid\ Sans\ Mono
	"set guifont=Droid\ Sans\ Mono
	set guioptions-=L
	set guioptions-=r
	set noguipty
endif

colorscheme github
filetype indent on
filetype plugin on

nmap <F5> :% w !wc -m <CR>
"nmap <F6> :DiffChangesDiffToggle <CR>
"nmap <F6> :% w ! diff -u % - <CR>

"Tlist
map <F7> :silent! Tlist<CR>
let Tlist_Ctags_Cmd='ctags'
let Tlist_Show_One_File=0
let Tlist_File_Fold_Auto_Close=1
let Tlist_Exit_OnlyWindow=1

"tags
nmap <F8> :!ctags -R --c-kinds=+p --fields=+lS -f ~/.vim/tagsinfo <CR>
set tags+=~/.vim/systags
set tags+=~/.vim/tagsinfo
inoremap <expr> <C-L> omni#cpp#maycomplete#Complete()
