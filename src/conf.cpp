#include "x/redis/conf.h"
#include <cstring>

namespace x{namespace redis{

namespace {

void set_timeout(int t, timeval& timeout)
{
    timeout.tv_sec = t / 1000;
    timeout.tv_usec = (t % 1000) * 1000;
}

}

conf::conf()
{
    host_ = nullptr;
    set_host("127.0.0.1", 6379);
    set_connect_retry_times(1);
    set_connect_timeout(1000);
    set_rw_retry_times(1);
    set_rw_timeout(1000);
}

void conf::set_host(const char* host, int port)
{
    if (!host)
    {
        host = "127.0.0.1";
    }
    int len = strlen(host);
    if (host_)
    {
        delete[] host_;
    }

    host_ = new char[len + 1];
    memcpy(host_, host, len);
    host_[len] = 0;
    port_ = port;
}

void conf::set_connect_retry_times(int retry_times)
{
    connect_retry_times_ = retry_times;
}

void conf::set_connect_timeout(int timeout)
{
    set_timeout(timeout, connect_timeout_);
}

void conf::set_connect_max_num(int max_num)
{
    connect_max_num_ = max_num;
}

void conf::set_rw_retry_times(int retry_times)
{
    rw_retry_times_ = retry_times;
}

void conf::set_rw_timeout(int timeout)
{
    set_timeout(timeout, rw_timeout_);
}

const char* conf::host() const
{
    return host_;
}

int conf::port() const
{
    return port_;
}

int conf::connect_retry_times() const
{
    return connect_retry_times_;
}

timeval conf::connect_timeout() const
{
    return connect_timeout_;
}

int conf::connect_max_num() const
{
    return connect_max_num_;
}

int conf::rw_retry_times() const
{
    return rw_retry_times_;
}

timeval conf::rw_timeout() const
{
    return rw_timeout_;
}

}}
