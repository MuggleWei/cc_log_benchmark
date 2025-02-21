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
2. **Scenario 2**: Determine the number of iterations and repetitions (set Iterations + Repetitions in google benchmark) to reflect the performance of each log library under non-stress testing. The number of threads tested in this scenario is: 1, 1/4n, 1/2n, n, 2n (n is the number of hardware parallelism obtained through `std::thread::hardware_concurrency`, NOTE: this number is not necessarily equal to the actual number of CPU cores and will also be affected by hyperthreading)

## Build
Run `build.sh` (`build.bat` in Windows) to build, The log library under test will be automatically downloaded during the build process. Then run `run_benchmark.sh` to run tests and generate benchmark report, report fill will be generated in `build` directory, filename is `benchmark_*.txt`.  
Note: Since some log libraries do not support all platforms, Only linux can guarantee all log libraries be tested.  

## Benchmark
Date: 2025-02-21  
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
Kernel: 6.11.9-arch1-1  
CPU: Intel i7-10710U (12) @ 4.700GHz  
GPU: Intel Comet Lake UHD Graphics  
Memory: 15659MiB  
gcc: (GCC) 14.2.1 20240910  
ldd: (GNU libc) 2.40  

### CPU frequency setting and monitoring
Execute `cpupower frequency-info` to view the information in my machine
```
analyzing CPU 7:
   driver: intel_pstate
   ...
   hardware limits: 400 MHz - 4.70 GHz
   ...
   boost state support:
     Supported: yes
     Active: yes
```

Before starting the benchmark, run `scripts/set_cpu_freq.sh` to limit the CPU frequency to a fixed value (here I chose 3.2GHz). Then, when running the benchmark, run `scripts/monitor_cpu_freq.sh` to monitor the CPU frequency, and confirm that there is no rate drop due to high CPU temperature.

### Extra Instructions
Due to some problems encountered during benchmark on my local machine, `fmtlog`, `quill` and `reckless` did not fully cover all scenarios.  
* Since we want to write logs as fast as possible, quill only tests the scenario under `BOUNDED`
* In **Scenario 1**, `quill::QueueType::BoundedBlocking` lead the process be stuck, so this mode skips **Scenario 1**
* I did not find the interface to set the buffer size for `Nanolog`, so I only used the default buffer size with them

**Due to personal limitations, if there are any errors, omissions, or lack of consideration, please feel free to correct me!**

## Result of Benchmark
In the [benchmark](./report/benchmark_20250221/benchmark) directory, you can find the details of the benchmark report of my local machine, graphically represented as follows:  

**Scenario 1**: Determine the minimum test time (x axis: logging library + number of threads, y axis: google benchmark - Time)
<img src="./report/benchmark_20250221/img/min_time.svg" />

**Scenario 2**: Determine the number of iterations and repetitions (x axis: logging library + number of threads, y axis: google benchmark - Time)
<img src="./report/benchmark_20250221/img/iter_repeat.svg" />

### About the y-axis values 
The y-axis is google benchmark - Time. In the case of multi-threading, it does not represent the average single time consumption, but the average result based on throughput and time. The formula is:
**google benchmark Time = (sum(time-consuming of each thread) ÷ number of threads) ÷ total number of executions**
Therefore, the results of multi-threading can be compared horizontally, but it cannot be simply regarded as a single time consumption. If you want to get the average time-consuming data of a single time under multi-threading, you can modify the google benchmark (v1.8.3) codes:
```
// benchmark_runner.cc
BenchmarkRunner::IterationResults BenchmarkRunner::DoNIterations() {
   ...
   // Just comment the following line
   // i.results.real_time_used /= b.threads();
   ...
}
```

## Result analysis
It is easy to see from the above chart
* In scenario 1, the faster log libraries are (in alphabetical order): fmtlog, Nanolog, quill
* In scenario 2, the faster log libraries are (in alphabetical order): fmtlog, haclog, Nanolog, quill

**So why are the four log libraries mentioned above faster? What are their advantages and disadvantages, and what pitfalls should we pay attention to when using them? **  

The above four log libraries are all asynchronous log libraries. They are also all designed multi-buffer queue and the consumer is responsible for polling. The overall ideas are similar, and the code details are interesting in their own way. But as a user, there is one thing need Pay special attention to  

**Pay special attention to**  
**Pay special attention to**  
**Pay special attention to**  

**Since the buffer is used, you must consider the situation when the buffer is full. At this time, there are three different ways to deal with it**  
1. **Blocking**: The producer thread blocks, waiting for the buffer to have enough space before writing.
2. **Discard**: Give up writing this log, or write this log directly but give up the entire buffer of logs
3. **Expand**: Dynamically increase the buffer length and continue writing

`haclog` and `Nanolog` chose option 1, `fmtlog` chose option 1/2, and `quill` chose option 1/2/3.  
Due to the situation mentioned in [Extra Instructions](#extra-instructions), we hope that logs can be written as quickly as possible, so `quill` only discusses bounded mode.  

### fmtlog
advantage
* Good speed in both scenarios
* If log loss is allowed when the buffer is full, the speed is tied with `quill` for the fastest speed in **Scenario 1**
* Supports blocking mode when the buffer is full, and will not lose logs
* Use `format` formatting style

disadvantages
* In drop mode, log loss occurred in both **Scenario 1** and **Scenario 2**  

### haclog
advantage
* Good speed in **Scenario 2**
* When the buffer is full, blocking mode is adopted and no logs will be lost

disadvantages
* When the throughput exceeds a certain threshold, the buffer is filled up, the efficiency will drop significantly

### Nanolog
advantage
* Good speed in both scenarios
* Very high throughput. In scenarios where log loss is not tolerated, whether it is **Scene 1** or **Scene 2**, it's the absolute kings
* When the buffer is full, blocking mode is adopted and no logs will be lost

disadvantages
* The log cannot be read directly and needs to be decoded using the `decompressor` program
* Only support Linux

### quill
advantage
* Good speed in both scenarios
* If log loss is allowed when the buffer is full, the speed is tied with `fmtlog` for the fastest speed in **Scenario 1**
* Use `format` formatting style
* Supports blocking mode when the buffer is full, and will not lose logs

disadvantages
* Log loss may occur in `quill::QueueType::BoundedDropping` mode
* In `quill::QueueType::BoundedBlocking` mode, the test of **Scene 1** cannot be completed

### A little extra consideration
`haclog` is developed in plain C, while `fmtlog`, `Nanolog` and `quill` are developed in C++; when it comes to the log library scenario, theoretically the upper limit of C++ implementation speed will be a little higher, as shown in the following two aspects  
* Compilation-time calculation: C++ can pre-calculate the log parameter information at compile-time, while the log library implemented in plain C needs to calculate it during the first run
* Log front-end serialization
  * C needs to traverse va_list at runtime, and the generated assembly code is serialized parameter by parameter through a loop. Whether it is judging the precalculated type through switch, or calling a preset function pointer, it may bring a little extra overhead
  * C++ performs serialization through Variadic template, and the assembly code can be implemented in the form of flat expansion, exchanging space for time

## Summary
* `fmtlog` and `quill` use the format formatting style, which is easy to write
  * In **Scenario 1**, `fmtlog_drop` 和 `quill_bounded_dropping` performs well. However, as analyzed in the previous section, the speed of this scenario is partly achieved by log loss, which requires special attention in the usage scenario.
  * Both also support blocking mode when the buffer is full.
* `haclog` performs well in **Scenario 2**, but in **Scenario 1** when the buffer is full, it can ensure that no logs are lost, but the efficiency is greatly reduced
* `Nanolog` has high efficiency and throughput in both scenarios. Under pressure, it can ensure that logs are not lost without sacrificing large amount efficiency. In scenarios where log loss is not tolerated, it's the absolute king. However, its high throughput is achieved at the cost of non-real-time readability of logs, which also makes tools such as `tail` unusable.

It can be seen that none of the current asynchronous logs can crush other log libraries in all aspects, but they all make trade-offs in some aspects.  