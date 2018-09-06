#include "x/redis/command.h"
#include "hiredis.h"
#include "connection_guard.h"
#include "errorinfo_impl.h"
#include "reply_parser.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool.h"
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

command::command(connection_pool* pool)
{
    pool_ = pool;
}

int command::append(const char* key, const char* val, errorinfo* err)
{
    connection* conn = pool_->lend();
    if (!conn)
    {
        errorinfo_impl::set(nullptr, 0, errorinfo::error_code_no_available_conn, err);
        return -1;
    }
    connection_guard guard(conn, pool_);

    redisReply* reply = static_cast<redisReply*>(redisCommand(conn->context(), "append %s %s", key, val));
    return reply_parser::int_reply(reply, conn, err);
}

}}
