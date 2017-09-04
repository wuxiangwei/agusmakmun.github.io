---
layout: post
title: Ceph 编译打包
date: 2017-09-04
author: wuxiangwei
category: [Ceph]
tags: Ceph
---


新建个干净的虚拟机。    
git clone代码。    
虚拟机可以无法连接代码库，先用物理机连接代码库，再打成.tar.gz包，拷贝到虚拟机，解压。

git check到指定的版本。    
执行`install-deps.sh`安装依赖的脚本。    
执行`dpkg-buildpackage -b -j4 -d`打包命令。打出的deb包的名字中包含`+netease`字段。        


