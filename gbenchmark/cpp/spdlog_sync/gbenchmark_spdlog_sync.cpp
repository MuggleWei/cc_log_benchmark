#include <atomic>
#include <thread>
#include <vector>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

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
				auto logger = spdlog::basic_logger_mt(
					"root", "logs/gbenchmark_spdlog_sync.log", true);
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

// min time
RUN_GBENCHMARK(SpdlogSyncFixture, sync)
