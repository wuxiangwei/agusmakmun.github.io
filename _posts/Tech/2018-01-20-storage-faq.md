---
layout: post
title: 存储问题FAQ
date: 2018-01-20
author: wuxiangwei
categories: 存储
tags: 存储
---

* Kramdown table of content
{:toc, toc}

# 磁盘问题 #

## 坏盘 ##

检查`/var/log/syslog`中对应磁盘的日志记录。

## 慢盘 ##

检查磁盘监控，是否出现长时间util为100%。

# 内存问题 #

## swap ##

swap导致卡住。
存储应该关闭swap。

