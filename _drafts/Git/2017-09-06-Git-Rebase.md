---
layout: post
title: Git Rebase
date: 2017-09-06
author: wuxiangwei
categories: Git
tags: Git
---

`git rebase <upstream> [--onto <newbase>]`命令。    
先将当前分支reset到newbase，然后再将当前分支和upstream间的commit，重新apply到当前分支。具体步骤如下：    

> All changes made by commits in the current branch but that are not in <upstream> are saved to a temporary area. This is the same set of commits that would be shown by git log <upstream>..HEAD (or git log HEAD, if --root is specified).

将所有仅存在于当前分支，在upstream中没有的commit保存到一个临时区域。这些commits可以通过`git log upstream..HEAD`查看。

> The current branch is reset to <upstream>, or <newbase> if the --onto option was supplied. This has the exact same effect as git reset --hard <upstream> (or <newbase>). ORIG_HEAD is set to point at the tip of the branch before the reset.

将当前分支reset到newbase，效果等同于执行`git reset --hard newbase`命令。

> The commits that were previously saved into the temporary area are then reapplied to the current branch, one by one, in order. Note that any commits in HEAD which introduce the same textual changes as a commit in HEAD..<upstream> are omitted (i.e., a patch already accepted upstream with a different commit message or timestamp will be skipped).

那些保存在临时区域内的commits将逐个被reapplied到当前分支。

具体应用场景：
两个分支a和b，在分支a中做了修改c，欲将c同步到b中。    

1. 基于分支a创建新分支aa。执行`git branch aa a`命令；
2. 将分支aa reset到分支b，将修改c应用到分支aa。执行`git rebase a --onto b`命令。
3. 将分支aa提交到refs/for/b中评审，评审结束后直接merge到分支b，这部分工作由gerrit来完成。

