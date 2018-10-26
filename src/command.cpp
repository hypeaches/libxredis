#include "x/redis/command.h"
#include <x/pool/objectpool.h>
#include "command_impl.h"

namespace x{namespace redis{

command::command()
{
    impl_ = x::objectpool<x::redis::command_impl>::create();
}

command::~command()
{
    x::objectpool<x::redis::command_impl>::release(impl_);
    impl_ = nullptr;
}

int command::init(int count)
{
    return x::objectpool<x::redis::command_impl>::init(count);
}

command& command::start_build(const char* op)
{
    if (impl_)
    {
        impl_->start_build(op);
    }
    return *this;
}

command& command::stop_build()
{
    if (impl_)
    {
        impl_->stop_build();
    }
    return *this;
}
#if 0
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
#endif

}}
