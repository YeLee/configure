# Lines configured by user

#zsh init
[ -d ~/.cache/zsh ] || mkdir -p ~/.cache/zsh
autoload -Uz compinit
compinit -d ~/.cache/zsh/zcompdump
HISTFILE=~/.cache/zsh/zshistory
HISTSIZE=10000
SAVEHIST=$HISTSIZE

PROMPT2='_%F{red}%B>>>%b%f'
PROMPT='%F{green}[%D{%y-%m-%d(%u) %H:%M:%S}] %F{blue}[%~]%F{red}%B>>>%b%f'
export xsessionlog=/tmp/xsessionlog
[[ "$PATH" =~ "$HOME/bin" ]] || export PATH=$PATH:$HOME/bin

#some keys
bindkey -v
bindkey "\ec" push-line-or-edit
bindkey "\e[A" history-beginning-search-backward
bindkey "\e[B" history-beginning-search-forward
bindkey "^J" history-beginning-search-backward
bindkey "^K" history-beginning-search-forward
bindkey "^A" beginning-of-line
bindkey "^E" end-of-line
bindkey "^F" vi-forward-word
bindkey "^B" vi-backward-word
bindkey "^R" clear-screen
bindkey "^L" history-incremental-search-backward
bindkey "^O" history-incremental-pattern-search-forward
bindkey "^P" history-incremental-pattern-search-backward

#some opts
setopt extendedhistory
setopt histignorealldups
setopt histignorespace
setopt correctall
setopt autolist
setopt automenu
setopt menucomplete
setopt extendedglob

#some comps
eval $(dircolors -b)
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*' verbose yes
zstyle ':completion:*' menu select
zstyle ':completion:*:*:default' force-list always
zstyle ':completion:*' matcher-list '' 'm:{a-zA-Z}={A-Za-z}'
zstyle ':completion:*' completer _complete _ignored _correct _approximate
zstyle ':completion:*:descriptions' format '%U%B%d%b%u'
zstyle ':completion:*:warnings' format '%B%F{red}WARNINGS:%f No matches for %U%F{blue}%d%u.%b'
zstyle ':completion:*' select-prompt '%B%F{red}SELECTED:%f %F{blue}%M%f%b'
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;34'
zstyle ':completion:*:processes' command 'ps -u$USER o pid,pcpu,size,cmd'
zstyle -e ':completion:*:sudo:*' command-path 'reply=($path /sbin /usr/sbin)'

#some alias
hash -d dl="$HOME/下载"
hash -d doc="$HOME/文档"
hash -d pic="$HOME/图片"
hash -d sft="/mnt/Software"
alias grep='grep --color=auto'
alias ls='ls --color=auto'
alias la='ls -A'
alias ll='ls -l'
alias lc="LC_ALL=C"
alias launchx="startx 1>$xsessionlog 2>$xsessionlog"

#some func
command_not_found_handler() {
	wget -q "http://www.portagefilelist.de/index.php/Special:PFLQuery2?file=${1}&searchfile=lookup&lookup=file&txt" -O - |awk -v cmd="$1" 'BEGIN{printf "\033[4;32m%s\033[0m may be included in the following packages: \n", cmd} {if ((NR != 1) && (!rec[$1$2]++)) {i++;printf "\033[33m%02d\033[0m:\033[1;31m%s\033[0m/\033[1;35m%s\033[0m\n", i, $1, $2}} END{if (i == 0) printf "\033[1;4;31mNo matches for %s !\033[0m\n", cmd}'
	return 127
}

# End of lines configured by user
