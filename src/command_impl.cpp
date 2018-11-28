#include "command_impl.h"
#include <memory>
#include <hiredis.h>
#include "x/redis/conf.h"
#include "x/redis/connection_pool.h"
#include "connection.h"
#include "connection_guard.h"
#include "redis_log.h"

namespace x{namespace redis{

command_impl::command_impl()
{
    connection_pool_ = nullptr;
    cmd_count_ = 0;
}

void command_impl::set_connection_pool(connection_pool* pool)
{
	connection_pool_ = pool;
}

int command_impl::count()
{
    return cmd_count_;
}

bool command_impl::build(const char* cmd)
{
    ++cmd_count_;
	return cmdbuf_.append(cmd);
}

bool command_impl::exec()
{
    return exec([](int, long long int*, const char*){});
}

bool command_impl::exec(long long int& integer)
{
    bool ret = false;
    exec([&ret, &integer](int, long long int* num, const char*){
        if (num)
        {
            integer = *num;
            ret = true;
        }
    });
    return ret;
}

bool command_impl::exec(const std::function<void(int index, long long int* integer, const char* string)>& cb)
{
	const conf* c = connection_pool_->get_conf();
	int rw_retry_times = c->rw_retry_times();
	redisReply* reply = nullptr;
	connection* conn = nullptr;
	int cmd_size = 0;
	int ok = 0;
    XREDISLOG("127.0.0.1", 6079, "test", "test msg");
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
		if (cmd_size != cmd_count_) {
			conn->reconnect();
			continue;
		}
		for (int i = 0; i < cmd_size; i++)
		{
			reply = nullptr;
			if (REDIS_OK != redisGetReply(conn->context(), (void**)&reply))
			{
				//todo
                cb(i, nullptr, nullptr);
				conn->reconnect();
				continue;
			}
			ok++;
            parse(i, reply, cb);
			freeReplyObject(reply);
		}
	}
	return (ok == cmd_size);
}

bool command_impl::parse(int index, redisReply* reply, const std::function<void(int index, long long int* integer, const char* string)>& cb)
{
    bool ret = true;
    if (REDIS_REPLY_ARRAY == reply->type)
    {
        for (int i = 0; i < reply->elements; i++)
        {
            parse_reply(index, reply->element[i], cb);
        }
    }
    else
    {
        ret = parse_reply(index, reply, cb);
    }
    return ret;
}

bool command_impl::parse_reply(int index, redisReply* reply, const std::function<void(int index, long long int* integer, const char* string)>& cb)
{
    bool ret = false;
    if (REDIS_REPLY_STRING == reply->type)
    {
        ret = true;
        cb(index, nullptr, reply->str);
    }
    else if (REDIS_REPLY_INTEGER == reply->type)
    {
        ret = true;
        cb(index, &reply->integer, nullptr);
    }
    else if (REDIS_REPLY_STATUS == reply->type)
    {
        if (strcasecmp(reply->str, "OK") == 0)
        {
            ret = true;
        }
        cb(index, nullptr, nullptr);
    }
    else if (REDIS_REPLY_NIL == reply->type)
    {
        cb(index, nullptr, nullptr);
    }
    else if (REDIS_REPLY_ERROR == reply->type)
    {
        cb(index, nullptr, nullptr);
    }
    return ret;
}

}}
