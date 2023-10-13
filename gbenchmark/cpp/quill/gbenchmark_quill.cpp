#include <atomic>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>
#include "benchmark/benchmark.h"
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#define QUILL_QUEUE_CAPACITY 4194304
#include "quill/Quill.h"

std::once_flag init_flag;

quill::Logger *logger = nullptr;

#define LOG_FUNC(num)                                                 \
	void log_func##num(LogMsg &msg)                                   \
	{                                                                 \
		LOG_INFO(logger, "u64: {}, i64: {}, u32: {}, i32: {}, s: {}", \
				 (unsigned long long)msg.u64, (long long)msg.i64,     \
				 (unsigned long)msg.u32, (long)msg.i32, msg.s);       \
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

			quill::configure([]() {
				quill::Config cfg;
				cfg.default_queue_capacity = 8 * 1024 * 1024;
				return cfg;
			}());
			quill::start();

			logger = quill::create_logger(
				"file_logger",
				quill::file_handler("logs/gbenchmark_quill.log", []() {
					quill::FileHandlerConfig cfg;
					cfg.set_open_mode('w');
					cfg.set_pattern("[%(level_name)]|"
									"[%(ascii_time)]|"
									"[%(filename):%(lineno)]|"
									"[%(function_name)]|"
									"[%(thread)]"
									" - %(message)",
									"%H:%M:%S.%Qms");
					return cfg;
				}()));
			logger->set_log_level(quill::LogLevel::TraceL3);
			logger->init_backtrace(2u, quill::LogLevel::Critical);
		});
	}

public:
	std::vector<LogMsg> log_msgs;
};

// min time
RUN_GBENCHMARK(FmtlogFixture, write)
