#include <atomic>
#include <filesystem>
#include <thread>
#include <vector>
#include <array>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "NanoLogCpp17.h"
using namespace NanoLog::LogLevels;

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
			NanoLog::setLogFile("logs/gbenchmark_nanolog.log");
			NanoLog::setLogLevel(NOTICE);
			NANO_LOG(NOTICE, "init success");
		});
		NanoLog::preallocate();
	}

public:
	std::vector<LogMsg> log_msgs;
};

// min time
RUN_GBENCHMARK(NanologFixture, write)
