---
layout: post
title: Ceph 编译打包
date: 2017-09-04
author: wuxiangwei
category: [Ceph]
tags: Ceph
---

* Kramdown table of contents
{:toc .toc}

# 生成deb包

新建个干净的虚拟机。    
git clone代码。    
虚拟机可以无法连接代码库，先用物理机连接代码库，再打成.tar.gz包，拷贝到虚拟机，解压。

git check到指定的版本。    
执行`install-deps.sh`安装依赖的脚本。    
执行`dpkg-buildpackage -b -j4 -d`打包命令。打出的deb包的名字中包含`+netease`字段。        

再将编译出的deb文件打包成一个tar包，执行`tar -czf ceph-deb.tar.gz ./ --exclude ceph --exclude ceph.tar.gz`命令。    


# 检查deb包

检查deb包的版本号以及其依赖包的版本号。

对未安装的deb包，执行`dpkg -I ceph-common_0.94.6+netease.1.1-7_amd64.deb`命令。
对已安装的deb包，执行`dpkg -s ceph-common`命令。


# 测试deb包

Ceph节点：    
pubt1-nova64.yq.163.org    
pubt1-nova69.yq.163.org    
pubt1-nova65.yq.163.org    
pubt1-nova68.yq.163.org    
pubt1-nova72.yq.163.org    
pubt1-nova73.yq.163.org    

Nova节点：    
udo apt-get  install libfcgi0ldbl
ubt1-nova42.yq.163.org    
pubt1-nova30.yq.163.org    


解压到指定目录：    
```
mkdir ceph-debs
tar xf ceph-deb.tar.gz -C ceh-debs
```

安装deb包：    
```
sudo dpkg -i *.deb
# 安装缺失的依赖包
sudo apt-get install -f
sudo apt-get  install libfcgi0ldbl
sudo dpkg -i *.deb
```
注意操作系统的版本和Ceph版本的匹配，否则会有依赖问题。




