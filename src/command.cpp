#include "x/redis/command.h"
#include <hiredis.h>
#include <x/string/stringbuf.h>
#include "connection_guard.h"
#include "reply_guard.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool.h"
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

command::command(connection_pool* pool)
{
    pool_ = pool;
}

int command::exec(const char* cmd, long long int* rep)
{
    redisReply* reply = NULL;
    int ret = do_redis_command(cmd, reply);
    if (!reply)
    {
        return ret;
    }
    reply_guard guard(reply);

    ret = 0;
    if (REDIS_REPLY_INTEGER == reply->type)
    {
        if (rep)
        {
            *rep = reply->integer;
        }
        ret = error_code_ok;
    }
    else if (REDIS_REPLY_NIL == reply->type)
    {
        ret = error_code_reply_nil;
    }
    else if (REDIS_REPLY_ERROR == reply->type)
    {
        ret = error_code_reply_error;
    }
    return ret;
}

int command::do_redis_command(const char* cmd, redisReply*& rep)
{
    rep = NULL;
    connection* conn = pool_->lend();
    if (!conn)
    {
        return error_code_no_available_conn;
    }
    connection_guard guard(conn, pool_);
    rep = static_cast<redisReply*>(redisCommand(conn->context(), cmd));
    if (!rep)
    {
        return error_code_no_redis_reply;
    }
    return error_code_ok;
}

}}
