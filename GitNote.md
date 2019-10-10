## GIT Notes

#### Part 0:    Git Config
    1. git config --list
    2. git config --global core.editor "'c:/Program Files/Notepad++.exe' -multiInst -nosession"
    3. git config --global core.name  "lyricc"
    4. git config --global core.mail "lyricc@sina.cn"

#### Part 1: Git Base
    1. git init
    2. git add 
    3. git status -s  [if add | if modify]
    4. git diff 
    5. git diff --staged/--cached
    6. git rm ReadMe.md 
    7. git rm --cached readme.md
    8. git mv file1 file2
    9. git log 
        -p 显示差异
        -2 显示最近2次log
        --pretty=oneline
        --pretty=format:"%h - %an , %ar : %s"
        --graph
        // limit aera
        --since=2.weeks
        --Sfunciton_name
    10. git commit --amend
    11. git reset HEAD <file>   -- 撤销已经暂存的文件
    12. git reset --hard HEAD <file>

    // 撤销修改的文件
    13. git checkout -- <file>
    
    14. git remote 
    15. git remote -v
    16. git remote add [short name] [url]
    17. git fetch [remote-name] + git merge
    18. git push [remote-name] [branch-name]
    19. git remote show [remote-name]
    20. git remote rename pb paul
    21. git remote rm paul
    
    // tag
    22. git tag    // list
    23. git tag -l "1.8.1*"  // 
    24. git tag -a v1.4.1 -m "my version 1.4.1"
    25. git show v1.4.1

    // 轻量标签
    26. git tag v1.4.2-lw

    27. git tag -a v1.2 9fceb02  // 补加标签

    28. git push [remote-name] [tag-name]

    29. git checkout -b version2 v2.0.0 // 创建分支version2 对应tag:v2.0.0

#### Part 2. Branch
    1. git branch [branch-name]     // 创建分支
    2. git checkout [branch-name]   // 切换分支
    
    //TODO::
    3. git merge [anthor-banch]     // 
    4. git log --oneline --decorate // --decorate
    5. git branch -d issue1001
    6. git mergetool
    7. git branch   // 列出所有的分支
    8. git branch -v  // 列出所有分支的最新提交信息
    9. git branch --merged              // 列出已经合并到当前分支的分支列表
    10. git branch --no-merged          // 列出没有合并到当前分支的分支列表
    11. git push origin --delete serverfix  // 删除 origin 仓库的serverfix分支
    12. git 
----
- remove untracked files/directories

```
	git clean -fdx
        -f force
        -d dictories
        -x remove ignored files too
        -n preview before remove
        -i for interactive
```
