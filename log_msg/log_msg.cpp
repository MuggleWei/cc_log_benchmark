#include "log_msg.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void GenLogMsgArray(uint32_t cnt, std::vector<LogMsg> &log_msgs)
{
	log_msgs.clear();

	log_msgs.reserve(cnt);

	srand(time(NULL));
	for (uint32_t i = 0; i < cnt; i++) {
		log_msgs.emplace_back(LogMsg{});
		LogMsg &msg = log_msgs[i];
		msg.u64 = (uint64_t)i;
		msg.u32 = (uint32_t)i;
		msg.i64 = (int64_t)i;
		msg.i32 = (int32_t)i;
		for (int i = 0; i < (int)sizeof(msg.s) - 1 - 3; i++) {
			msg.s[i] = (rand() % 26) + 'a';
		}
		char *p = msg.s;
		p += sizeof(msg.s) - 1 - 3;
		memcpy(p, "end", 3);
		msg.s[sizeof(msg.s) - 1] = '\0';
	}
}

bool DumpsLogMsg(std::vector<LogMsg> &log_msgs)
{
	FILE *fp = fopen("random_data.bin", "wb");
	if (fp == nullptr) {
		fprintf(stderr, "failed open random_data.bin for write\n");
		return false;
	}

	for (LogMsg &msg : log_msgs) {
		fwrite(&msg, sizeof(msg), 1, fp);
	}

	fclose(fp);

	return true;
}

bool LoadLogMsg(std::vector<LogMsg> &log_msgs)
{
	FILE *fp = fopen("random_data.bin", "rb");
	if (fp == nullptr) {
		fprintf(stderr, "failed open random_data.bin for read\n");
		return false;
	}

	fseek(fp, 0, SEEK_END);
	long num_bytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	size_t n = (size_t)num_bytes / sizeof(LogMsg);
	log_msgs.reserve(n);

	LogMsg msg;
	while (fread(&msg, sizeof(msg), 1, fp) == 1) {
		log_msgs.push_back(msg);
	}

	fclose(fp);

	return true;
}
