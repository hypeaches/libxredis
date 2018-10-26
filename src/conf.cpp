#include "conf.h"

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
    set_host("127.0.0.1", 6739);
    set_conn_retry_time(3);
    set_conn_timeout(1000);
    set_rw_retry_time(3);
    set_rw_timeout(1000);
}

void conf::set_host(const char* host, int port)
{
    host_ = host;
    port_ = port;
}

void conf::set_conn_retry_time(int retry_time)
{
    conn_retry_time = retry_time;
}

void conf::set_conn_timeout(int timeout)
{
    set_timeout(timeout, conn_timeout_);
}

void conf::set_rw_retry_time(int retry_time)
{
    rw_retry_time = retry_time;
}

void conf::set_rw_timeout(int timeout)
{
    set_timeout(timeout, rw_timeout_);
}

}}
