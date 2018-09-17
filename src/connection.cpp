#include "x/redis/connection.h"
#include <sys/time.h>
#include <hiredis.h>
#include <x/string/stringbuf.h>
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

connection::connection()
{
    cntx_ = nullptr;
    hostname_ = nullptr;
    is_used_ = false;
    conn_retry_times_ = 1;
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

int connection::connect()
{
    timeval tv;
    tv.tv_sec = timeout_ / 1000;
    tv.tv_usec = timeout_ % 1000 * 1000;

    for (int i = 0; i < conn_retry_times(); ++i)
    {
        reset_context();
        cntx_ = redisConnectWithTimeout(hostname_, port_, tv);
        if (cntx_ && (cntx_->err == 0))
        {
            return error_code_ok;
        }
    }
    int ret = error_code_allocate_redis_context_failed;
    if (!cntx_)
    {
        ret = error_code_allocate_redis_context_failed;
    }
    else if (cntx_->err)
    {
        ret = error_code_reply_error;
    }
    reset_context();
    return ret;
}

connection* connection::lend()
{
    connection* conn = (is_used_ || !cntx_) ? nullptr : this;
    is_used_ = true;
    return conn;
}

void connection::give_back(x::redis::connection*)
{
    is_used_ = false;
}

int connection::conn_retry_times()
{
    return conn_retry_times_;
}

int connection::retry_times()
{
    return retry_times_;
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
