#include "x/redis/connection.h"
#include <sys/time.h>
#include <hiredis.h>
#include <x/string/stringbuf.h>

namespace x{namespace redis{

connection::connection()
{
    cntx_ = nullptr;
    hostname_ = nullptr;
    is_used_ = false;
}

connection::~connection()
{
    if (cntx_)
    {
        redisFree(cntx_);
        cntx_ = nullptr;
    }
    if (hostname_)
    {
        delete hostname_;
        hostname_ = nullptr;
    }
}
void connection::set_host(const char* hostname, int port, int timeout)
{
    if (hostname_)
    {
        delete hostname_;
        hostname_ = nullptr;
    }
    hostname_ = x::stringbuf(128)
        .append(hostname)
        .moved_buffer();
    port_ = port;
    timeout_ = timeout;
}

error connection::connect()
{
    reset_context();

    timeval tv;
    tv.tv_sec = timeout_ / 1000;
    tv.tv_usec = timeout_ % 1000 * 1000;
    cntx_ = redisConnectWithTimeout(hostname_, port_, tv);
    if (!cntx_)
    {
        return error(error::errno_allocate_redis_context_failed);
    }
    if (cntx_->err)
    {
        return error(cntx_->errstr);
    }
    return error(error::errno_ok);
}

connection* connection::lend()
{
    connection* conn = is_used_ ? nullptr : this;
    is_used_ = true;
    return conn;
}

void connection::give_back(x::redis::connection*)
{
    is_used_ = false;
}

void connection::reset_context()
{
    if (cntx_)
    {
        redisFree(cntx_);
        cntx_ = nullptr;
    }
}

}}
