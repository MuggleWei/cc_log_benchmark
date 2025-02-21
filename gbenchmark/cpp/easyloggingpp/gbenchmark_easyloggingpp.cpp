#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "easylogging++.h"

std::once_flag init_flag;

INITIALIZE_EASYLOGGINGPP

#define LOG_FUNC(num)                                             \
	void log_func##num(LogMsg &msg)                               \
	{                                                             \
		LOG(INFO) << "u64: " << msg.u64 << ", i64: " << msg.i64   \
				  << ", u32: " << msg.u32 << ", i32: " << msg.i32 \
				  << ", s: " << msg.s;                            \
	}

EXPAND_FUNCS

class EasyLoggingFixture : public benchmark::Fixture {
public:
	EasyLoggingFixture()
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
			el::Loggers::reconfigureAllLoggers(
				el::ConfigurationType::Format,
				"%level|%datetime|%fbase:%line|%func|%thread - %msg");
			el::Loggers::reconfigureAllLoggers(
				el::ConfigurationType::Filename,
				"logs/gbenchmark_easyloggingpp.log");
			el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile,
											   "true");
			el::Loggers::reconfigureAllLoggers(
				el::ConfigurationType::ToStandardOutput, "false");
			// el::Loggers::reconfigureAllLoggers(
			//     el::ConfigurationType::MaxLogFileSize, "1073741824");
		});
	}

	void TearDown(const benchmark::State &)
	{
	}

public:
	std::vector<LogMsg> log_msgs;
};

RUN_GBENCHMARK(EasyLoggingFixture, write)
