#include "command_buffer.h"
#include <cstring>
#include <hiredis.h>
#include "connection.h"

namespace x{namespace redis{

command_buffer::command_buffer()
	: buf_(4096)
{
	cmd_count_ = 0;
	cmd_ = nullptr;
}

bool command_buffer::append(const char* cmd)
{
	buf_.append(cmd).append("\0", 1);
	++cmd_count_;
	return true;
}

int command_buffer::build_command(connection* conn)
{
	cmd_ = buf_.buffer();
	for (int i = 0; i < cmd_count_; i++)
	{
		const char* cmd = get_next_command();
		if (REDIS_OK != redisAppendCommand(conn->context(), cmd))
		{
			return -1;
		}
	}
	return cmd_count_;
}

const char* command_buffer::get_next_command()
{
	//todo:越界检查
	const char* cmd = cmd_;
	cmd_ += (strlen(cmd_) + 1);
	return cmd;
}

}}
