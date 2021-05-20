# git rebase用法分享

> 天下苦git久矣
>
> ​				——《史记·陈涉世家》

## rebase是什么

变基，主要用于整合修改，作用是你可以提取在当前分支中引入的补丁和修改，然后在基底分支应用一次，即将提交到某一分支上的所有修改都移至另一分支上，就好像“重新播放”一样。

```bash
git branch
	*r1
	r2
	r3
git rebase r3
```

## 原理

它的原理是首先找到这两个分支（即当前分支 `r1 `，变基操作的目标基底分支`r3`） 的最近共同祖先 ，然后对比当前分支相对于该祖先的历次提交，提取相应的修改并存为临时文件， 然后将当前分支指向目标基底 `r3`, 最后以此将之前另存为临时文件的修改依序应用。 

## rebase与merge区别

刚才的操作，我们还有另一个办法可以做到

```bash
git checkout r3
git merge r1
```

这两种整合方法的最终结果没有任何区别，但是`rebase`使得提交历史更加整洁。 如果你点开一个经过`rebase`的分支的历史记录你会发现，哇，好整洁，竟然是一条直线，意思就是，尽管可能是在很多分支上开发项目和提交， 按理说应该会有很多很多分叉，然后偶尔汇总一下，但`rebase`这个操作，让这些提交看上去就像是串行的一样，提交历史是一条直线没有分叉。

一般我们这样做的目的是为了确保在向远程分支推送时能保持提交历史的整洁 在这种情况下，你首先在自己的分支里进行开发，当开发完成时你需要先将你的代码变基到 `origin/dev` 上，然后再向主项目提交修改。 这样的话，项目的维护者就不再需要进行整合工作，只需要快进合并便可。

请大家注意，无论是通过`rebase`，还是通过`merge`，整合的最终结果始终是一样的，只不过是提交历史不同。 变基是将一系列提交按照原有次序依次应用到另一分支上，而合并是把最终结果合在一起。

## rebase的更多用法

### 整理提交记录

当我们在进行项目开发的初期，我们往往不太注重整洁的提交历史，因为这的确会增加一些多余的操作，但是当我们的项目越来越大，参与的开发者越来越多，或者使用我们代码的人越来越多的时候，就会面临两个问题，其一是：混乱的提交历史让我们对代码的管理越来越困难，有时候代码出问题了你不知道要回滚到哪个版本，其二是：丢人！(作为一个成熟的开源项目，你要学会自己管理自己的提交历史了.jpg)

`git rebase`可以让我们完全删除提交（基本上是对 Git屎山说再见，但是最好别这么做），重新修改提交信息（修改格式，或者把中文改成中文），将多次提交合并成一次提交（这对于隐藏小改变的提交很有用，例如添加一个分号或者换行）以及其他巴拉巴拉。

比如说我们对一个文件做了三次修改，提交了三次，那我们有没有办法把这三次改成一次呢？

当然有（不然我也不会说了

```bash
git commit -a -m "1"
git commit -a -m "2"
git commit -a -m "3"
git rebase -i HEAD~3	//返回三次提交之前，更好的做法是找到那个哈希值，然后 git rebase xxxxxxxxx
//这个时候会出现一个vim界面
//大概长这样：

pick xxxxxxxxxx 1
pick xxxxxxxxxx 2
pick xxxxxxxxxx 3
# Rebase befb50f5c8..2d2e6f4b63 onto befb50f5c8 (2 commands)
#
# Commands:
# p, pick = use commit
# r, reword = use commit, but edit the commit message
# e, edit = use commit, but stop for amending
# s, squash = use commit, but meld into previous commit
# f, fixup = like "squash", but discard this commit's log message
# x, exec = run command (the rest of the line) using shell
# d, drop = remove commit
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out

//注释已经写的非常明白了，举一个合并的小例子吧，我们需要：
i
把2和3前边的pick改成squash或者s
esc :wq
```

这样其实就成功了，相当于把2和3的提交融入进了1

其他的操作可以用上面那些不同的指令来做

到现在一切都很顺利，直到我看到了一些高级操作

### 一些野路子（我也没玩过）

```bash
git rebase --onto dev r1 r2
```

这条命令的意思是，取出`r2`分支，找到它从`r1`分出之后改变的那部分补丁，然后把这些补丁应用在`dev`上，属于比较高端的操作，我们估计很难用到这条命令

## 冲突处理

```bash
git rebase dev
	conflict xxxx
git status
	both modified xxx.c
vi xxx.c
//决定采用哪个版本，或者两个都不要，自己写
git commit -a -m "xxx"
git rebase --contine
//一直解冲突，解呀解，解呀解
//完事儿
```

## 协作开发时提交代码的规范操作

### master与dev

+ master分支主要用于发布比较稳定的版本
+ dev分支主要用于合作开发

### dev与dev_xxx

显然我们不能所有人同时在dev上工作，这样会造成混乱的提交，甚至可能出现严重的错误（两个人同时修改了某个文件）

所以需要每个人建立自己的开发分支，例如dev_xxx，每个人在自己的分支上独立工作，然后把自己的修改合入dev分支

```bash
git clone xxx
git branch
	*dev
	master
git checkout -b dev_megumin
```

```bash
git branch dev_megumin
git checkout dev_megumin
```

### 合入代码之前要做什么

+ 首先rebase一下最新的dev(因为你可能已经在自己的分支上开发了很久，dev发生了较大变化)（有冲突的话请参照“冲突处理”一节）

  ```bash
  git branch
  	*dev_megumin
  	dev
  git pull dev -r
  ```

  ```bash
  git checkout dev
  git pull
  git checkout dev_megumin
  git rebase dev
  ```

+ 接下来，把你的数次提交整合成一次（当然每次改动不要太多，最好是不同的分支做不同的工作，每次合入一个功能或者一类bug的修复）

  ```bash
  git log
  	commit xxxxxxxxxx(HEAD->dev_megumin)
  	commit xxxxxxxxxx
  	...(你的数次提交)
  	commit xxxxxxxxxx(origin/dev)
  	...(dev的提交记录)
  git reset --soft xxxxxxxxxxxx    //(origin/dev)
  git commit -m "fix bug of xxx"	//提交信息尽量写的详细一点点
  ```

+ 现在你的分支应该是以下这个样子的

  ```bash
  git log
  	commit xxxxxxxxxx(HEAD->dev_megumin)
  		commit message
  	commit xxxxxxxxxx(origin/dev)
  	...(dev的提交记录)
  ```

+ 如果是这样的话，那就已经非常完美了，接下来让我们来到下一节：怎么合入

### 怎么合入

最好的方法是MR（PR），让大家一起review，然后merged

第二好的办法是merge（在代码经过review的情况下）（在代码管理严格的社区不要这样做（如果你碰巧有权限的话））

```bash
git branch
	*dev_megumin
	dev
git checkout dev
git merge dev_megumin
git pull origin:dev dev -f
// git pull -f
```

