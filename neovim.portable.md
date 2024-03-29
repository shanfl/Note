#### sysinit.vim

> ```bash
> $VIM/sysinit.vim
> ```
> 
> ```bash
> let s:config_path = fnamemodify(expand("$VIM"), ':h:h:h:h') . '\config\nvim'
> let &rtp .= ',' . s:config_path
> exec 'source ' . s:config_path . '\init.vim'
> ```
> 
> 
