#include <atomic>
#include <filesystem>
#include <mutex>
#include <thread>
#include <vector>
#include "log_msg/log_msg.h"
#include "gbenchmark/log_gbenchmark.h"
#include "glog/logging.h"

std::once_flag init_flag;

#define LOG_FUNC(num)                                             \
	void log_func##num(LogMsg &msg)                               \
	{                                                             \
		LOG(INFO) << "u64: " << msg.u64 << ", i64: " << msg.i64   \
				  << ", u32: " << msg.u32 << ", i32: " << msg.i32 \
				  << ", s: " << msg.s;                            \
	}

EXPAND_FUNCS

void CustomPrefix(std::ostream &s, const google::LogMessageInfo &l, void *)
{
	s << l.severity << '|' << std::setw(4) << 1900 + l.time.year() << '-'
	  << std::setw(2) << 1 + l.time.month() << '-' << std::setw(2)
	  << l.time.day() << 'T' << std::setw(2) << l.time.hour() << ':'
	  << std::setw(2) << l.time.min() << ':' << std::setw(2) << l.time.sec()
	  << '.' << std::setw(6) << l.time.usec() << '|' << l.filename << ':'
	  << l.line_number << '|' << std::setw(5) << l.thread_id << " - ";
}

class GlogFixture : public benchmark::Fixture {
public:
	GlogFixture()
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

			FLAGS_logbufsecs = 0;
			FLAGS_log_dir = "./logs";
			FLAGS_alsologtostderr = 0;
			FLAGS_timestamp_in_logfile_name = false;

			google::SetLogDestination(google::GLOG_INFO,
									  "logs/gbenchmark_glog.info.log");
			google::SetLogDestination(google::GLOG_WARNING,
									  "logs/gbenchmark_glog.warn.log");
			google::SetLogDestination(google::GLOG_ERROR,
									  "logs/gbenchmark_glog.error.log");

			google::InitGoogleLogging("gbenchmark_glog", &CustomPrefix);
		});
	}

public:
	std::vector<LogMsg> log_msgs;
};

// min time
RUN_GBENCHMARK(GlogFixture, write)
