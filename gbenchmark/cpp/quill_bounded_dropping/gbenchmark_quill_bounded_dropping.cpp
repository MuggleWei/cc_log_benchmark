#include <filesystem>
#include <mutex>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/Logger.h"
#include "quill/LogMacros.h"
#include "quill/sinks/FileSink.h"

std::once_flag init_flag;

struct CustomFrontendOptions {
	static constexpr quill::QueueType queue_type =
		quill::QueueType::BoundedDropping;
	static constexpr uint32_t initial_queue_capacity = 4 * 1024 * 1024;
	static constexpr uint32_t blocking_queue_retry_interval_ns = 800;
	static constexpr bool huge_pages_enabled = false;
};

using CustomFrontend = quill::FrontendImpl<CustomFrontendOptions>;
using CustomLogger = quill::LoggerImpl<CustomFrontendOptions>;

CustomLogger *logger = nullptr;

#define LOG_FUNC(num)                                                 \
	void log_func##num(LogMsg &msg)                                   \
	{                                                                 \
		LOG_INFO(logger, "u64: {}, i64: {}, u32: {}, i32: {}, s: {}", \
				 (unsigned long long)msg.u64, (long long)msg.i64,     \
				 (unsigned long)msg.u32, (long)msg.i32, msg.s);       \
	}

EXPAND_FUNCS

class QuillBoundedBlockingFixture : public benchmark::Fixture {
public:
	QuillBoundedBlockingFixture()
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

			// start the backend thread
			quill::BackendOptions backend_options;
			quill::Backend::start(backend_options);

			// frontend
			auto sink = CustomFrontend::create_or_get_sink<quill::FileSink>(
				"logs/gbenchmark_quill_bounded_dropping.log");
			logger = CustomFrontend::create_or_get_logger(
				"root", std::move(sink),
				quill::PatternFormatterOptions("[%(log_level)]|"
											   "[%(time)]|"
											   "[%(short_source_location)]|"
											   "[%(caller_function)]|"
											   "[%(thread_id)]"
											   " - %(message)",
											   "%H:%M:%S.%Qms"));
			logger->set_log_level(quill::LogLevel::TraceL3);
			logger->init_backtrace(2u, quill::LogLevel::Critical);
		});

		CustomFrontend::preallocate();
	}

public:
	std::vector<LogMsg> log_msgs;
};

// min time
RUN_GBENCHMARK(QuillBoundedBlockingFixture, write)
