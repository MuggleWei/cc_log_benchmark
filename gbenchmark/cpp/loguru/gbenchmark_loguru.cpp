#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "loguru.hpp"
#include "loguru.cpp"

std::once_flag init_flag;

#define LOG_FUNC(num)                                                  \
	void log_func##num(LogMsg &msg)                                    \
	{                                                                  \
		LOG_F(INFO, "u64: %llu, i64: %lld, u32: %lu, i32: %ld, s: %s", \
			  (unsigned long long)msg.u64, (long long)msg.i64,         \
			  (unsigned long)msg.u32, (long)msg.i32, msg.s);           \
	}

EXPAND_FUNCS

class LoguruFixture : public benchmark::Fixture {
public:
	LoguruFixture()
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
			loguru::add_file("logs/gbenchmark_loguru.log", loguru::Truncate,
							 loguru::Verbosity_INFO);
			loguru::g_stderr_verbosity = loguru::Verbosity_INVALID;
			LOG_F(INFO, "success init loguru");
		});
	}

	void TearDown(const benchmark::State &)
	{
	}

public:
	std::vector<LogMsg> log_msgs;
};

RUN_GBENCHMARK(LoguruFixture, write)
