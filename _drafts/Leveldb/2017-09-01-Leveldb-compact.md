---
layout: post
title: Leveldb Compact
date: 2017-09-01
author: wuxiangwei
categories: Leveldb
tags: Leveldb
---

* Kramdown table of contents
{:toc .toc}

# 编译

默认make，不编译测试程序。
查看Makefile文件，按需编译。
make check编译结束自动运行测试用例。

```shell
check: all $(PROGRAMS) $(TESTS)                                                                     
       for t in $(TESTS); do echo "***** Running $$t"; ./$$t || exit 1; done
```

写入NULL表项，会引发Compact操作。

```shell
DBImpl::Write() --> DBImpl::MakeRoomForWrite(true) --> DBImpl::MaybeScheduleCompaction()
```

Write流程：

- 写日志
- 写内存

```
DBImpl
    |-- log_: log::Writer

log::Writer::AddRecord();
WriteBatchInternal::InsertInto()
```


Compact流程：
- 分段compact


```
PosixEnv
    |-- queue_: BGQueue
        |-- arg: void*  // 任务参数
        |-- void (function*)(void*)  // 任务函数

DBImpl::CompactRange(begin, end) --> DBImpl::TEST_CompactRange(level, begin, end) --> DBImpl::MaybeScheduleCompaction() --> PosixEnv::Schedule()


Compaction
    |-- level_: int
    |-- input_version_: Version*
    |-- inputs_: std::vector<FileMetaData*>  // each compaction reads inputs from "level_" and "level_+1"


CompactionState
    |-- compaction: Compaction* const
    |-- smallest_snapshot: SequenceNumber

VersionSet
    |-- last_sequence_: uint64_t

versionSet::MakeInputIterator


// compact线程
// 如果队列为空，等待；否则，取出任务，执行任务函数。
// compact的任务函数为DBImpl::BGWork，任务参数为DBImpl实例。
PosixEnv::BGThread() --> DBImpl::BGWork() --> DBImpl::BackgroundCall() --> DBImpl::BackgroundCompaction() --> DoCompactionWork()
// 如果手动compact，调用VersionSet::CompactRange；否则调用VersionSet::PickCompaction()，获得1个Compaction实例。
```

1. 计算和给定key-range存在overlap的level的最大值；
2. 逐层compact


打印日志
"Compacting %d@%d + %d@%d files"
文件数@层号，L层的文件数@L层 + L+1层的文件数@L+1层。

# 注意事项

## Slice构造函数不能传入临时变量

```c
class Slice {
private:
    const char* data_;
}

{
    leveldb::Slice start(Key(0));
    leveldb::Slice end(Key(10));
    db_->CompactRange(&start, &end);
}
```
Slice::data_直接引用了构造函数传入的数据，如果传入的是临时变量，临时变量销毁后data_将指向一个未知位置。
查看Leveldb的LOG文件可以发现Manual compact 的开始和结束Key不正确。


## Leveldb v1.5版本显示日志问题

```
2017/08/30-23:12:35.013862 7f36641ff700 Manual compaction at level-0 from 'paxos .. 'paxos; will stop at (end)
2017/08/30-23:12:35.015385 7f36641ff700 Manual compaction at level-1 from 'paxos .. 'paxos; will stop at 'paxos
2017/08/30-23:12:35.133755 7f36641ff700 Manual compaction at level-1 from 'paxos .. 'paxos; will stop at (end)
2017/08/30-23:12:35.134655 7f36641ff700 Manual compaction at level-2 from 'paxos .. 'paxos; will stop at 'paxos
2017/08/30-23:12:35.261322 7f36641ff700 Manual compaction at level-2 from 'paxos .. 'paxos; will stop at 'paxos
```
日志中手动compaction的开始和结束位置相同，都为paxos。正确的位置应该为“paxos012345”，由于Key中存在一个0，所以字符串被阶段了。
