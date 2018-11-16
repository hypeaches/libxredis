#include "command_impl.h"
#include <memory>
#include <hiredis.h>
#include "x/redis/conf.h"
#include "x/redis/connection_pool.h"
#include "connection.h"
#include "connection_guard.h"

namespace x{namespace redis{

void command_impl::set_connection_pool(connection_pool* pool)
{
	connection_pool_ = pool;
}

bool command_impl::build(const char* cmd)
{
	return cmdbuf_.append(cmd);
}

bool command_impl::exec()
{
	const conf* c = connection_pool_->get_conf();
	int rw_retry_times = c->rw_retry_times();
	redisReply* reply = nullptr;
	connection* conn = nullptr;
	int cmd_size = 0;
	int ok = 0;
	for (int i = 0; i < rw_retry_times; i++)
	{
		ok = 0;
		conn = connection_pool_->create();
		if (!conn)
		{
			continue;
		}
		connection_guard guard(conn, connection_pool_);
		cmd_size = cmdbuf_.build_command(conn);
		if (cmd_size <= 0) {
			conn->reconnect();
			continue;
		}
		for (int i = 0; i < cmd_size; i++)
		{
			reply = nullptr;
			if (REDIS_OK != redisGetReply(conn->context(), (void**)&reply))
			{
				//todo
				conn->reconnect();
				continue;
			}
			ok++;
			freeReplyObject(reply);
		}
	}
	return (ok == cmd_size);
}

}}
