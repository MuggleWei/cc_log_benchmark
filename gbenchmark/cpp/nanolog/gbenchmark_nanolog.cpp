#include <atomic>
#include <filesystem>
#include <thread>
#include <vector>
#include <array>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
#include "NanoLogCpp17.h"
using namespace NanoLog::LogLevels;
#include "gbenchmark/log_gbenchmark.h"

std::once_flag init_flag;

#define LOG_FUNC(num)                                                       \
	void log_func##num(LogMsg &msg)                                         \
	{                                                                       \
		NANO_LOG(NOTICE, "u64: %llu, i64: %lld, u32: %lu, i32: %ld, s: %s", \
				 (unsigned long long)msg.u64, (long long)msg.i64,           \
				 (unsigned long)msg.u32, (long)msg.i32, msg.s);             \
	}

EXPAND_FUNCS

class NanologFixture : public benchmark::Fixture {
public:
	NanologFixture()
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
			std::filesystem::create_directories("logs");
			NanoLog::setLogFile("logs/nanolog_basic.log");
			NanoLog::setLogLevel(NOTICE);
			NANO_LOG(NOTICE, "init success");
		});
		NanoLog::preallocate();
	}

public:
	std::vector<LogMsg> log_msgs;
};

BENCHMARK_DEFINE_F(NanologFixture, write)(benchmark::State &state)
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
RUN_GBENCHMARK(NanologFixture, write)