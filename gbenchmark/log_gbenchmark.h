#ifndef LOG_GBENCHMARK_H_
#define LOG_GBENCHMARK_H_

#include "benchmark/benchmark.h"

#ifndef CUSTOM_TEARDOWN
static void DoTeardown(const benchmark::State &)
{
}
#else
static void DoTeardown(const benchmark::State &);
#endif

#ifndef MIN_TIME
	#define MIN_TIME 3
#endif
#if MIN_TIME
	#define RUN_GBENCHMARK_MIN_TIME(fixture, name) \
		BENCHMARK_REGISTER_F(fixture, name)        \
			->Threads(1)                           \
			->MinTime(MIN_TIME)                    \
			->Teardown(DoTeardown);                \
		BENCHMARK_REGISTER_F(fixture, name)        \
			->Threads(2)                           \
			->MinTime(MIN_TIME)                    \
			->Teardown(DoTeardown);                \
		BENCHMARK_REGISTER_F(fixture, name)        \
			->Threads(4)                           \
			->MinTime(MIN_TIME)                    \
			->Teardown(DoTeardown);                \
		BENCHMARK_REGISTER_F(fixture, name)        \
			->Threads(8)                           \
			->MinTime(MIN_TIME)                    \
			->Teardown(DoTeardown);
#else
	#define RUN_GBENCHMARK_MIN_TIME(fixture, name)
#endif

#ifndef ITER_COUNT
	#define ITER_COUNT 2000
	#define REPEAT_COUNT 5
#endif
#if ITER_COUNT
	#define RUN_GBENCHMARK_ITER_REPEAT(fixture, name)                 \
		BENCHMARK_REGISTER_F(fixture, name)                           \
			->Threads(1)                                              \
			->Iterations(ITER_COUNT)                                  \
			->Repetitions(REPEAT_COUNT)                               \
			->Teardown(DoTeardown);                                   \
		BENCHMARK_REGISTER_F(fixture, name)                           \
			->Threads((std::thread::hardware_concurrency() / 4) > 0 ? \
						  (std::thread::hardware_concurrency() / 4) : \
						  1)                                          \
			->Iterations(ITER_COUNT)                                  \
			->Repetitions(REPEAT_COUNT)                               \
			->Teardown(DoTeardown);                                   \
		BENCHMARK_REGISTER_F(fixture, name)                           \
			->Threads((std::thread::hardware_concurrency() / 2) > 0 ? \
						  (std::thread::hardware_concurrency() / 2) : \
						  1)                                          \
			->Iterations(ITER_COUNT)                                  \
			->Repetitions(REPEAT_COUNT)                               \
			->Teardown(DoTeardown);                                   \
		BENCHMARK_REGISTER_F(fixture, name)                           \
			->Threads(std::thread::hardware_concurrency())            \
			->Iterations(ITER_COUNT)                                  \
			->Repetitions(REPEAT_COUNT)                               \
			->Teardown(DoTeardown);                                   \
		BENCHMARK_REGISTER_F(fixture, name)                           \
			->Threads(std::thread::hardware_concurrency() * 2)        \
			->Iterations(ITER_COUNT)                                  \
			->Repetitions(REPEAT_COUNT)                               \
			->Teardown(DoTeardown);
#else
	#define RUN_GBENCHMARK_ITER_REPEAT(fixture, name)
#endif

#define RUN_GBENCHMARK(fixture, name)                                         \
	BENCHMARK_DEFINE_F(fixture, name)(benchmark::State & state)               \
	{                                                                         \
		static thread_local int idx = 0;                                      \
		const int nfuncs = sizeof(log_funcs) / sizeof(log_funcs[0]);          \
		const int n_msg = (int)log_msgs.size();                               \
		if (log_msgs.size() < nfuncs) {                                       \
			fprintf(stderr, "number of log message < nfuncs is not allowed"); \
			exit(EXIT_FAILURE);                                               \
		}                                                                     \
                                                                              \
		for (auto _ : state) {                                                \
			log_funcs[idx % nfuncs](log_msgs[idx]);                           \
			idx = (idx + 1) % n_msg;                                          \
		}                                                                     \
	}                                                                         \
	RUN_GBENCHMARK_ITER_REPEAT(fixture, name)                                 \
	RUN_GBENCHMARK_MIN_TIME(fixture, name)                                    \
	BENCHMARK_MAIN();

#endif // !LOG_GBENCHMARK_H_
