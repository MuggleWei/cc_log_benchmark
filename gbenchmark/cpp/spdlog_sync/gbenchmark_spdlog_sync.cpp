#include <atomic>
#include <thread>
#include <vector>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "gbenchmark/log_gbenchmark.h"

std::once_flag init_flag;

#define LOG_FUNC(num)                                                \
	void log_func##num(LogMsg &msg)                                  \
	{                                                                \
		SPDLOG_INFO("u64: {}, i64: {}, u32: {}, i32: {}, s: {}",     \
					(unsigned long long)msg.u64, (long long)msg.i64, \
					(unsigned long)msg.u32, (long)msg.i32, msg.s);   \
	}

EXPAND_FUNCS

class SpdlogSyncFixture : public benchmark::Fixture {
public:
	SpdlogSyncFixture()
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
				auto logger =
					spdlog::basic_logger_mt("root", "logs/spdlog_basic.log");
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

BENCHMARK_DEFINE_F(SpdlogSyncFixture, sync)(benchmark::State &state)
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
RUN_GBENCHMARK(SpdlogSyncFixture, sync)