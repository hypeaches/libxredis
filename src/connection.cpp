#include "x/redis/connection.h"
#include <sys/time.h>
#include <hiredis.h>
#include <x/string/stringbuf.h>

namespace x{namespace redis{

connection::connection()
{
    cntx_ = nullptr;
    hostname_ = nullptr;
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

bool connection::connect()
{
    reset_error();
    reset_context();

    timeval tv;
    tv.tv_sec = timeout_ / 1000;
    tv.tv_usec = timeout_ % 1000 * 1000;
    cntx_ = redisConnectWithTimeout(hostname_, port_, tv);
    if (!cntx_)
    {
        x::stringbuf(errmsg_, errmsg_len_)
            .append("redis error : connection : can't allocate redis context");
        return false;
    }
    if (cntx_->err)
    {
        x::stringbuf(errmsg_, errmsg_len_)
            .append("redis error : connection : ")
            .append(cntx_->errstr);
        reset_context();
        return false;
    }
    return true;
}

connection* connection::lend()
{
    return this;
}

void connection::give_back(x::redis::connection*)
{
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
