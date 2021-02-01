[TOC]

# git使用

## init

```shell
git init	
初始化
git init newrepo
```

初始化后，会在 newrepo 目录下会出现一个名为 .git 的目录，所有 Git 需要的数据和资源都存放在这个目录中。

如果当前目录下有几个文件想要纳入版本控制，需要先用 git add 命令告诉 Git 开始对这些文件进行跟踪，然后提交：

```shell
$ git add *.c
$ git add README
$ git commit -m '初始化项目版本'
```

## clone

我们使用 **git clone** 从现有 Git 仓库中拷贝项目（类似 **svn checkout**）。

```shell
git clone <repo>
git clone <repo> <directory>
```

## config

git 配置信息

```shel
git config --global user.name "Luke.Deng"
git config --global user.email  "xiangshuo1992@gmail.com"
```

## 暂存区替换工作区

```shell
git checkout .
```



## 分支

```bash
git checkout -b smr origin/smr
```

## 忽略

```shell

```

