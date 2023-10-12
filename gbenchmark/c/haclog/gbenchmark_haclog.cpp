#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
#include "haclog/haclog.h"

#define ITER_COUNT 10000
#define REPEAT_COUNT 5

#define MIN_TIME 3.0

std::once_flag init_flag;

#define LOG_FUNC(num)                                                  \
	void log_func##num(LogMsg &msg)                                    \
	{                                                                  \
		HACLOG_INFO("u64: %llu, i64: %lld, u32: %lu, i32: %ld, s: %s", \
					(unsigned long long)msg.u64, (long long)msg.i64,   \
					(unsigned long)msg.u32, (long)msg.i32, msg.s);     \
	}

EXPAND_FUNCS

class HaclogFixture : public benchmark::Fixture {
public:
	HaclogFixture()
	{
		if (!LoadLogMsg(log_msgs)) {
			fprintf(stderr,
					"failed load random data, Run gen_random_data first");
			exit(EXIT_FAILURE);
		}
	}

	void SetUp(const benchmark::State &)
	{
		std::call_once(init_flag, []() {
			static haclog_file_handler_t file_handler = {};
			if (haclog_file_handler_init(&file_handler, "logs/haclog_basic.log",
										 "w") != 0) {
				exit(EXIT_FAILURE);
			}
			haclog_handler_set_level((haclog_handler_t *)&file_handler,
									 HACLOG_LEVEL_DEBUG);
			haclog_context_add_handler((haclog_handler_t *)&file_handler);

			haclog_context_set_bytes_buf_size(4 * 1024 * 1024);

			haclog_backend_run();
			HACLOG_INFO("init success");
		});
		haclog_thread_context_init();
	}

	void TearDown(const benchmark::State &)
	{
		haclog_thread_context_cleanup();
	}

public:
	std::vector<LogMsg> log_msgs;
};

BENCHMARK_DEFINE_F(HaclogFixture, write)(benchmark::State &state)
{
	static thread_local int idx = 0;
	const int nfuncs = sizeof(log_funcs) / sizeof(log_funcs[0]);
	const int n_msg = (int)log_msgs.size();
	if (log_msgs.size() < nfuncs) {
		fprintf(stderr, "number of log message < nfuncs is not allowed");
		exit(EXIT_FAILURE);
	}

	for (auto _ : state) {
		log_funcs[idx % nfuncs](log_msgs[idx]);
		idx = (idx + 1) % n_msg;
	}
}

// min time
BENCHMARK_REGISTER_F(HaclogFixture, write)->Threads(1)->MinTime(MIN_TIME);
BENCHMARK_REGISTER_F(HaclogFixture, write)
	->Threads((std::thread::hardware_concurrency() / 2) > 0 ?
				  (std::thread::hardware_concurrency() / 2) :
				  1)
	->MinTime(MIN_TIME);
BENCHMARK_REGISTER_F(HaclogFixture, write)
	->Threads(std::thread::hardware_concurrency() - 1 > 0 ?
				  (std::thread::hardware_concurrency() - 1) :
				  1)
	->MinTime(MIN_TIME);

// iteration * repeat
BENCHMARK_REGISTER_F(HaclogFixture, write)
	->Threads(1)
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);
BENCHMARK_REGISTER_F(HaclogFixture, write)
	->Threads((std::thread::hardware_concurrency() / 2) > 0 ?
				  (std::thread::hardware_concurrency() / 2) :
				  1)
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);
BENCHMARK_REGISTER_F(HaclogFixture, write)
	->Threads(std::thread::hardware_concurrency())
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);
BENCHMARK_REGISTER_F(HaclogFixture, write)
	->Threads(std::thread::hardware_concurrency() * 2)
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);

BENCHMARK_MAIN();
