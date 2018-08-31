#include "x/redis/command.h"
#include "hiredis.h"
#include "x/string/stringbuf.h"
#include "connection_guard.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool.h"
#include "x/redis/error.h"

namespace x{namespace redis{

command::command(connection_pool* pool)
{
    pool_ = pool;
}

int command::append(const char* key, const char* val, error* err)
{
    connection* conn = pool_->lend();
    if (!conn)
    {
        error::set(error::errno_no_available_conn, err);
        return -1;
    }
    connection_guard grard(conn, pool_);

    const char* cmd = x::stringbuf()
        .append("append ")
        .append(key).append(" ")
        .append(val)
        .buffer();
    redisReply* reply = static_cast<redisReply*>(redisCommand(conn->context(), cmd));
    if (!reply)
    {
        error::set(error::errno_no_redis_reply, err);
        return false;
    }

    error::set(error::errno_ok, err);
    return true;
}

}}
