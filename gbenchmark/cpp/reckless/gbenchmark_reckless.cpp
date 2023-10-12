#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
// #include "gbenchmark/log_gbenchmark.h"
#include "reckless/severity_log.hpp"
#include "reckless/file_writer.hpp"

using log_t = reckless::severity_log<
	reckless::indent<4>, // 4 spaces of indent
	'|', // Field separator
	reckless::severity_field, // Show severity marker (D/I/W/E) first
	reckless::timestamp_field // Then timestamp field
	>;

reckless::file_writer writer("logs/gbenchmark_reckless.log");
log_t g_log(&writer);

std::once_flag init_flag;

#define LOG_FUNC(num)                                                 \
	void log_func##num(LogMsg &msg)                                   \
	{                                                                 \
		g_log.info("u64: %llu, i64: %lld, u32: %lu, i32: %ld, s: %s", \
				   (unsigned long long)msg.u64, (long long)msg.i64,   \
				   (unsigned long)msg.u32, (long)msg.i32, msg.s);     \
	}

EXPAND_FUNCS

class RecklessFixture : public benchmark::Fixture {
public:
	RecklessFixture()
	{
		if (!LoadLogMsg(log_msgs)) {
			fprintf(stderr,
					"failed load random data, Run gen_random_data first");
			exit(EXIT_FAILURE);
		}
	}

	void SetUp(const benchmark::State &)
	{
		std::call_once(init_flag, []() {});
	}

	void TearDown(const benchmark::State &)
	{
	}

public:
	std::vector<LogMsg> log_msgs;
};

#define ITER_COUNT 10000
#define REPEAT_COUNT 5
#define MIN_TIME 3.0

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
	/* NOTE: reckless google benchmark Infinite running!!! */                 \
	/* min time */                                                            \
	/* BENCHMARK_REGISTER_F(fixture, name)->Threads(1)->MinTime(MIN_TIME); */ \
	/* BENCHMARK_REGISTER_F(fixture, name)->Threads(2)->MinTime(MIN_TIME); */ \
	/* BENCHMARK_REGISTER_F(fixture, name)->Threads(4)->MinTime(MIN_TIME); */ \
	/* iteration * repeat */                                                  \
	BENCHMARK_REGISTER_F(fixture, name)                                       \
		->Threads(1)                                                          \
		->Iterations(ITER_COUNT)                                              \
		->Repetitions(REPEAT_COUNT);                                          \
	BENCHMARK_REGISTER_F(fixture, name)                                       \
		->Threads((std::thread::hardware_concurrency() / 2) > 0 ?             \
					  (std::thread::hardware_concurrency() / 2) :             \
					  1)                                                      \
		->Iterations(ITER_COUNT)                                              \
		->Repetitions(REPEAT_COUNT);                                          \
	BENCHMARK_REGISTER_F(fixture, name)                                       \
		->Threads(std::thread::hardware_concurrency())                        \
		->Iterations(ITER_COUNT)                                              \
		->Repetitions(REPEAT_COUNT);                                          \
	BENCHMARK_REGISTER_F(fixture, name)                                       \
		->Threads(std::thread::hardware_concurrency() * 2)                    \
		->Iterations(ITER_COUNT)                                              \
		->Repetitions(REPEAT_COUNT);                                          \
	/* gbenchmark main*/                                                      \
	BENCHMARK_MAIN();

RUN_GBENCHMARK(RecklessFixture, write);
