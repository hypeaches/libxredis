#include "x/redis/connection.h"
#include <sys/time.h>
#include <hiredis.h>
#include <x/string/stringbuf.h>
#include "errorinfo_impl.h"
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

connection::connection()
{
    cntx_ = nullptr;
    hostname_ = nullptr;
    is_used_ = false;
    conn_retry_times_ = 1;
    read_retry_times_ = 1;
    write_retry_times_ = 1;
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

bool connection::connect(errorinfo* err)
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
            errorinfo_impl::set(hostname_, port_, errorinfo::error_code_ok, err);
            return true;
        }
    }
    if (!cntx_)
    {
        errorinfo_impl::set(hostname_, port_, errorinfo::error_code_allocate_redis_context_failed, err);
    }
    else if (cntx_->err)
    {
        errorinfo_impl::set(hostname_, port_, cntx_->errstr, err);
    }
    return false;
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
