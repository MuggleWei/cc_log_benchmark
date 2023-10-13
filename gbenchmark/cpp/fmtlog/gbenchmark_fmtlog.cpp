#include <atomic>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#define FMTLOG_BLOCK 1
#include "fmtlog.h"

std::once_flag init_flag;

#define LOG_FUNC(num)                                                    \
	void log_func##num(LogMsg &msg)                                      \
	{                                                                    \
		FMTLOG(fmtlog::INF, "u64: {}, i64: {}, u32: {}, i32: {}, s: {}", \
			   (unsigned long long)msg.u64, (long long)msg.i64,          \
			   (unsigned long)msg.u32, (long)msg.i32, msg.s);            \
	}

EXPAND_FUNCS

class FmtlogFixture : public benchmark::Fixture {
public:
	FmtlogFixture()
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
			fmtlog::setLogFile("logs/gbenchmark_fmt.log");
			fmtlog::setHeaderPattern("{l}|{YmdHMSF}|{s}|{t} - ");

			FMTLOG(fmtlog::INF, "hello");
		});
	}

public:
	std::vector<LogMsg> log_msgs;
};

// min time
RUN_GBENCHMARK(FmtlogFixture, write)
