#include <atomic>
#include <thread>
#include <vector>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

#define ITER_COUNT 10000
#define REPEAT_COUNT 5

#define MIN_TIME 3.0

std::once_flag init_flag;

#define LOG_FUNC(num)                                                \
	void log_func##num(LogMsg &msg)                                  \
	{                                                                \
		SPDLOG_INFO("u64: {}, i64: {}, u32: {}, i32: {}, s: {}",     \
					(unsigned long long)msg.u64, (long long)msg.i64, \
					(unsigned long)msg.u32, (long)msg.i32, msg.s);   \
	}

EXPAND_FUNCS

class SpdlogAsyncFixture : public benchmark::Fixture {
public:
	SpdlogAsyncFixture()
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
			try {
				spdlog::init_thread_pool(8 * 1024, 1);

				auto logger = spdlog::basic_logger_mt<spdlog::async_factory>(
					"root", "logs/spdlog_async.log");
				logger->set_level(spdlog::level::debug);
				logger->set_pattern("%l|%E.%F|%s|%!|%t - %v");

				spdlog::set_default_logger(logger);
			} catch (const spdlog::spdlog_ex &ex) {
				fprintf(stderr, "log init failed: %s\n", ex.what());
			}
			SPDLOG_INFO("init success");
		});
	}

public:
	std::vector<LogMsg> log_msgs;
};

BENCHMARK_DEFINE_F(SpdlogAsyncFixture, async)(benchmark::State &state)
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
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)->Threads(1)->MinTime(MIN_TIME);
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)
	->Threads((std::thread::hardware_concurrency() / 2) > 0 ?
				  (std::thread::hardware_concurrency() / 2) :
				  1)
	->MinTime(MIN_TIME);
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)
	->Threads(std::thread::hardware_concurrency() - 1 > 0 ?
				  (std::thread::hardware_concurrency() - 1) :
				  1)
	->MinTime(MIN_TIME);

// iteration * repeat
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)
	->Threads(1)
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)
	->Threads((std::thread::hardware_concurrency() / 2) > 0 ?
				  (std::thread::hardware_concurrency() / 2) :
				  1)
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)
	->Threads(std::thread::hardware_concurrency())
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);
BENCHMARK_REGISTER_F(SpdlogAsyncFixture, async)
	->Threads(std::thread::hardware_concurrency() * 2)
	->Iterations(ITER_COUNT)
	->Repetitions(REPEAT_COUNT);

BENCHMARK_MAIN();
