#include "reply_parser.h"
#include <hiredis.h>
#include "errorinfo_impl.h"
#include "reply_guard.h"
#include "testutil.h"
#include "x/redis/connection.h"
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

int reply_parser::int_reply(redisReply*& reply, const connection* conn, errorinfo* err)
{
    if (!reply)
    {
        errorinfo_impl::set(conn->host(), conn->port(), errorinfo::error_code_no_redis_reply, err);
        return -1;
    }
    reply_guard guard(reply);
    testutil::print_redisreply(reply);

    if (reply->type == REDIS_REPLY_INTEGER)
    {
        errorinfo_impl::set(conn->host(), conn->port(), errorinfo::error_code_ok, err);
        return reply->integer;
    }
    else if (reply->type == REDIS_REPLY_ERROR)
    {
        errorinfo_impl::set(conn->host(), conn->port(), reply->str, err);
        return -1;
    }

    errorinfo_impl::set(conn->host(), conn->port(), errorinfo::error_code_unkown, err);
    return -1;
}

}}
