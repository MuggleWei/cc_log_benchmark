#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "log_msg/log_msg.h"
// NOTE: reckless stuck in MIN_TIME benchmark
#define MIN_TIME 0
#include "gbenchmark/log_gbenchmark.h"
#include "reckless/severity_log.hpp"
#include "reckless/file_writer.hpp"

using log_t = reckless::severity_log<
	reckless::indent<4>, // 4 spaces of indent
	'|', // Field separator
	reckless::severity_field, // Show severity marker (D/I/W/E) first
	reckless::timestamp_field // Then timestamp field
	>;

reckless::file_writer writer("logs/gbenchmark_reckless.log");
log_t g_log(&writer);

std::once_flag init_flag;

#define LOG_FUNC(num)                                                 \
	void log_func##num(LogMsg &msg)                                   \
	{                                                                 \
		g_log.info("u64: %llu, i64: %lld, u32: %lu, i32: %ld, s: %s", \
				   (unsigned long long)msg.u64, (long long)msg.i64,   \
				   (unsigned long)msg.u32, (long)msg.i32, msg.s);     \
	}

EXPAND_FUNCS

class RecklessFixture : public benchmark::Fixture {
public:
	RecklessFixture()
	{
		if (!LoadLogMsg(log_msgs)) {
			fprintf(stderr,
					"failed load random data, Run gen_random_data first");
			exit(EXIT_FAILURE);
		}
	}

	void SetUp(const benchmark::State &)
	{
		std::call_once(init_flag, []() {});
	}

	void TearDown(const benchmark::State &)
	{
	}

public:
	std::vector<LogMsg> log_msgs;
};

RUN_GBENCHMARK(RecklessFixture, write);
