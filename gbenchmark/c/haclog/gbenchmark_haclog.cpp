#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "haclog/haclog.h"

std::once_flag init_flag;

#define LOG_FUNC(num)                                                  \
	void log_func##num(LogMsg &msg)                                    \
	{                                                                  \
		HACLOG_INFO("u64: %llu, i64: %lld, u32: %lu, i32: %ld, s: %s", \
					(unsigned long long)msg.u64, (long long)msg.i64,   \
					(unsigned long)msg.u32, (long)msg.i32, msg.s);     \
	}

EXPAND_FUNCS

class HaclogFixture : public benchmark::Fixture {
public:
	HaclogFixture()
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
			static haclog_file_handler_t file_handler = {};
			if (haclog_file_handler_init(
					&file_handler, "logs/gbenchmark_haclog.log", "w") != 0) {
				exit(EXIT_FAILURE);
			}
			haclog_handler_set_level((haclog_handler_t *)&file_handler,
									 HACLOG_LEVEL_DEBUG);
			haclog_context_add_handler((haclog_handler_t *)&file_handler);

			haclog_context_set_bytes_buf_size(4 * 1024 * 1024);

			haclog_backend_run();
			HACLOG_INFO("init success");
		});
		haclog_thread_context_init();
	}

	void TearDown(const benchmark::State &)
	{
		haclog_thread_context_cleanup();
	}

public:
	std::vector<LogMsg> log_msgs;
};

RUN_GBENCHMARK(HaclogFixture, write)
