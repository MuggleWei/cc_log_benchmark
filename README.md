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
Use google benchmark for performance testing. The test is divided into two scenario
1. **Scenario 1**: Determine the minimum test time (set MinTime in google benchmark), and write logs as much as possible during this time. This scenario is mainly for asynchronous logs, which can reflect the throughput of the log library, and how efficient is the writing of the log front-end when the buffer is highly stressed. The number of threads use in this scenario is: 1/2/4/8
2. **Scenario 2**: Determine the number of iterations and repetitions (set Iterations + Repetitions in google benchmark) to reflect the performance of each log library under non-stress testing. The number of threads tested in this scenario is: 1/${0.5 * num_of_CPU}/${1 * num_of_CPU}/${2 * num_of_CPU}

## Build
Run `build.sh` (`build.bat` in Windows) to build, The log library under test will be automatically downloaded during the build process. Then run `run_benchmark.sh` to run tests and generate benchmark report, report fill will be generated in `build` directory, filename is `benchmark_*.txt`.  
Note: Since some log libraries do not support all platforms, Only linux can guarantee all log libraries be tested.  

## Benchmark
Date: 2023-10-14  
Log libraries' version, see: [CMakeLists.txt](./CMakeLists.txt)  
Write data per time:
```
struct LogMsg {
	uint64_t u64;
	uint32_t u32;
	int64_t i64;
	int32_t i32;
	char s[128];
};
```
logging output patterns: 
```
${Level}|${datetime}|${filename}.${line_no}|${func_name}|${thread_id} - u64: msg.u64, i64: msg.i64, u32: msg.u32, i32: msg.i32, s: msg.s
```

### Machine
Type: laptop  
Machine: 20R10002CD ThinkPad X1 Carbon 7th  
System: Arch Linux x86_64  
Kernel: 6.5.6-arch2-1  
CPU: Intel i7-10710U (12) @ 4.700GHz  
GPU: Intel Comet Lake UHD Graphics  
Memory: 15659MiB  
gcc: (GCC) 13.2.1 20230801  
ldd: (GNU libc) 2.38  

### Extra Instructions
Due to some problems encountered during benchmark on my local machine, `fmtlog`, `quill` and `reckless` did not fully cover all scenarios.  
* When `#define FMTLOG_BLOCK 1` in `fmtlog`, the benchmark process will be stuck and unable to continue, so `fmtlog` only tested the mode that discard log when the buffer is full
* When use `UNBOUNDED` in `quill`, in **Scenario 1**, it will cause the memory usage to keep growing and fail, so when benchmark `quill_unbounded`, skip **Scenario 1**
* I did not find the interface to set the buffer size for `fmtlog` and `Nanolog`, so I only used the default buffer size with them

**Due to personal limitations, if there are any errors, omissions, or lack of consideration, please feel free to correct me!**

## Result of Benchmark
In the [gbenchmark](./report/benchmark_20231014/gbenchmark) directory, you can find the details of the benchmark report of my local machine, graphically represented as follows:  

**Scenario 1**: Determine the minimum test time (x axis: logging library + number of threads, y axis: elapsed time (ns))
<img src="./report/benchmark_20231014/img/min_time.svg" />

**Scenario 2**: Determine the number of iterations and repetitions (x axis: logging library + number of threads, y axis: elapsed time of median of 5 replicate benchmarks (ns))
<img src="./report/benchmark_20231014/img/iter_repeat.svg" />

## Result analysis
It is easy to see from the above chart
* In scenario 1, the faster log libraries are (in alphabetical order): fmtlog, haclog, Nanolog, quill_bounded
* In scenario 2, the faster log libraries are (in alphabetical order): fmtlog, haclog, Nanolog

**So why are the four log libraries mentioned above faster? What are their advantages and disadvantages, and what pitfalls should we pay attention to when using them? **  

The above four log libraries are all asynchronous log libraries. They are also all designed multi-buffer queue and the consumer is responsible for polling. The overall ideas are similar, and the code details are interesting in their own way. But as a user, there is one thing need Pay special attention to  

**Pay special attention to**  
**Pay special attention to**  
**Pay special attention to**  

**Since the buffer is used, you must consider the situation when the buffer is full. At this time, there are three different ways to deal with it**  
1. **Blocking**: The producer thread blocks, waiting for the buffer to have enough space before writing.
2. **Discard**: Give up writing this log, or write this log directly but give up the entire buffer of logs
3. **Expand**: Dynamically increase the buffer length and continue writing

`haclog` and `Nanolog` chose option 1, `fmtlog` chose option 1/2, and `quill` chose option 2/3.  
Due to the situation mentioned in [Extra Instructions](#extra-instructions), `fmtlog` can only choose option 2, and `quill` only discusses bounded mode in **Scenario 1**  

### fmtlog
advantage
* It shows good speed in both scenarios, among which the speed in **Scenario 1** is on par with `quill_bounded` and tied for the fastest speed
* In both scenarios, the stability of speed performance is good enough and the fluctuation is small
* Use `format` formatting style

disadvantages
* A large number of lost logs occurred in **Scenario 1**
* Lost logs also occurred in **Scenario 2**
* When setting `#define FMTLOG_BLOCK 1`, the benchmark of **Scenario 1** cannot be completed

### haclog
advantage
* In most cases, both scenarios show good speed. In the case of multi-threading in **Scenario 2**, the speed is only slightly worse than Nanolog
* When the buffer is full, blocking mode is adopted and no logs will be lost

disadvantages
* When the throughput exceeds a certain threshold, the buffer is filled up, the efficiency will drop significantly

### Nanolog
advantage
* Shows good speed in both scenarios, with speed ranking first in case of multi-threading in **Scenario 2**
* Very high throughput, no significant drop in efficiency occurs in either **Scenario 1** or **Scenario 2**
* When the buffer is full, blocking mode is adopted and no logs will be lost

disadvantages
* The log cannot be read directly and needs to be decoded using the `decompressor` program

### quill
advantage
* Speed in **Scenario 1** is on par with `fmtlog` and tied for the fastest speed
* Use `format` formatting style

disadvantages
* Log loss may occur in `bounded` mode
* In `unbounded` mode, it may cause the memory to keep growing and the benchmark of **Scenario 1** cannot be completed

### A little extra consideration
`haclog` is developed in plain C, while `fmtlog`, `Nanolog` and `quill` are developed in C++; when it comes to the log library scenario, theoretically the upper limit of C++ implementation speed will be a little higher, as shown in the following two aspects  
* Compilation-time calculation: C++ can pre-calculate the log parameter information at compile-time, while the log library implemented in plain C needs to calculate it during the first run
* Log front-end serialization
  * C needs to traverse va_list at runtime, and the generated assembly code is serialized parameter by parameter through a loop. Whether it is judging the precalculated type through switch, or calling a preset function pointer, it may bring a little extra overhead
  * C++ performs serialization through Variadic template, and the assembly code can be implemented in the form of flat expansion, exchanging space for time

## Summary
* `fmtlog` and `quill` use format formatting style, which is easy to write, and both have strong speed stability. `fmtlog` and `quill_bounded` perform well in **Scenario 1**. However, as analyzed in the previous section, their greater speed comes at the cost of losing logs, this requires special attention in usage scenarios  
* `haclog` also performs well in both scenarios. In **Scenario 2**, its performance is only slightly inferior to `Nanolog`. However, in **Scenario 1**, when throughput exceeds a certain threshold, the efficiency is greatly reduced. This is exactly the opposite of `fmtlog` and `quill`, `haclog` reduces the speed in exchange for not losing logs
* `Nanolog` shows extremely high efficiency and ultra-high throughput in both scenarios. It is the king in **Scenario 2** and guarantees no loss of logs under pressure in **Scenario 1** You don’t have to sacrifice too much efficiency. However, its ultra-high throughput is traded for non-real-time readability of logs, which also makes tools such as `tail` unusable.

It can be seen that none of the current asynchronous logs can crush other log libraries in all aspects, but they all make trade-offs in some aspects.  