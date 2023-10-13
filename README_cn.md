* [readme EN](./README.md)
* [readme 中文](./README_cn.md)

## 概述
此库对几个 C/C++ 日志库做 benchmark, 被测的库如下所示(按字母顺序排序)  
* [easyloggingpp](https://github.com/abumq/easyloggingpp): C++ logging library. It is extremely powerful, extendable, light-weight, fast performing, thread and type safe and consists of many built-in features. It provides ability to write logs in your own customized format. It also provide support for logging your classes, third-party libraries, STL and third-party containers etc.
* [fmtlog](https://github.com/MengRao/fmtlog): fmtlog is a performant fmtlib-style logging library with latency in nanoseconds.
* [glog](https://github.com/google/glog): C++ implementation of the Google logging module
* [haclog](https://github.com/MuggleWei/haclog): Haclog(Happy Aync C log) is an extremely fast plain C logging library
* [loguru](https://github.com/emilk/loguru): A lightweight C++ logging library
* [nanolog](https://github.com/PlatformLab/NanoLog): Nanolog is an extremely performant nanosecond scale logging system for C++ that exposes a simple printf-like API. 
* [quill](https://github.com/odygrd/quill): Asynchronous Low Latency C++ Logging Library
* [reckless](https://github.com/mattiasflodin/reckless/tree/master): Reckless logging. Low-latency, high-throughput, asynchronous logging library for C++.
* [spdlog](https://github.com/gabime/spdlog): Fast C++ logging library

## Benchmark 说明
使用 google benchmark 进行测试, 测试分为两部分场景
1. 设定最小的测试时间 (设置 google benchmark 中的 MinTime), 在这时间中尽可能的压力测试写日志, 此场景主要针对异步日志, 可以反映日志库的吞吐量, 以及当缓冲区高度紧张的情况下日志前端的写入效率如何. 在此场景下测试的线程数量为: 1/2/4/8
2. 设定迭代和重复次数 (设置 google benchmark 中的 Iterations + Repetitions), 反映在非压力测试的情况下, 各个日志库的表现如何. 在此场景下测试的线程数量为: 1/${0.5 * CPU数量}/${1 * CPU数量}/${2 * CPU数量}

## 构建
直接运行 `build.sh` (Windows 上运行 `build.bat`)进行构建, 构建过程中会自动下载被测的日志库. 接着运行 `run_benchmark.sh` 进行测试并生成报告.  
注意: 由于部分日志库并不支持所有平台, 所以仅在 Linux 能够测试所有的日志库.  
