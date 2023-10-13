* [readme EN](./README.md)
* [readme 中文](./README_cn.md)

## Overview
The repo benchmark several C/C++ log library. The tested libraries list below(Sort alphabetically)  
* [easyloggingpp](https://github.com/abumq/easyloggingpp): C++ logging library. It is extremely powerful, extendable, light-weight, fast performing, thread and type safe and consists of many built-in features. It provides ability to write logs in your own customized format. It also provide support for logging your classes, third-party libraries, STL and third-party containers etc.
* [fmtlog](https://github.com/MengRao/fmtlog): fmtlog is a performant fmtlib-style logging library with latency in nanoseconds.
* [glog](https://github.com/google/glog): C++ implementation of the Google logging module
* [haclog](https://github.com/MuggleWei/haclog): Haclog(Happy Aync C log) is an extremely fast plain C logging library
* [loguru](https://github.com/emilk/loguru): A lightweight C++ logging library
* [nanolog](https://github.com/PlatformLab/NanoLog): Nanolog is an extremely performant nanosecond scale logging system for C++ that exposes a simple printf-like API. 
* [quill](https://github.com/odygrd/quill): Asynchronous Low Latency C++ Logging Library
* [reckless](https://github.com/mattiasflodin/reckless/tree/master): Reckless logging. Low-latency, high-throughput, asynchronous logging library for C++.
* [spdlog](https://github.com/gabime/spdlog): Fast C++ logging library

## Benchmark explanation
Use google benchmark for testing. The test is divided into two scenario
1. Determine the minimum test time (set MinTime in google benchmark), and write logs as much as possible during this time. This scenario is mainly for asynchronous logs, which can reflect the throughput of the log library, and how efficient is the writing of the log front-end when the buffer is highly stressed. The number of threads tested in this scenario is: 1/2/4/8
2. Determine the number of iterations and repetitions (set Iterations + Repetitions in google benchmark) to reflect the performance of each log library under non-stress testing. The number of threads tested in this scenario is: 1/${0.5 * num_of_CPU}/${1 * num_of_CPU}/${2 * num_of_CPU}

## Build
Run `build.sh` (`build.bat` in Windows) to build, The log library under test will be automatically downloaded during the build process. Then run the program starting with `gbenchmark_` in the `bin` directory to test.  
Note: Since some log libraries do not support all platforms, Only linux can guarantee all log libraries be tested.  
