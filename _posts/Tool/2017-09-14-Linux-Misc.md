---
layout: post
title: Linux常用工具总结
date: 2017-09-14
author: wuxiangwei
categories: 工具
tags: 工具
---

* Kramdown table of contents:
{:toc, toc}


# iftop


1. 指定网卡；
2. 带宽的单位为字节，默认为bit；

iftop -i eth5.100 -B


# iostat


iostat -txm 2 -p /dev/sdb