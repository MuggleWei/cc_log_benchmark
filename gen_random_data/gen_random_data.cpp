#include "log_msg.h"

int main()
{
	std::vector<LogMsg> log_msgs;
	GenLogMsgArray(10000, log_msgs);

	DumpsLogMsg(log_msgs);

	return 0;
}
