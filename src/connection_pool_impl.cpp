#include "connection_pool_impl.h"

namespace x{namespace redis{

connection_pool_impl::connection_pool_impl()
{
}

connection_pool_impl::~connection_pool_impl()
{
}

connection* connection_pool_impl::create()
{
    return pool_->create();
}

void connection_pool_impl::release(connection* conn)
{
    pool_->release(conn);
}

int connection_pool_impl::conn_retry_times()
{
    return conf_.conn_retry_times();
}

int connection_pool_impl::conn_timeout()
{
    return conf_.conn_timeout();
}

int connection_pool_impl::rw_retry_times()
{
    return conf_.rw_retry_times();
}

int connection_pool_impl::rw_timeout()
{
    return conf_.rw_timeout();
}

bool connection_pool_impl::add(const char* host, int port)
{
    conf_.set_host(host, port);
    connection* conn = new connection;
    conn->set_conf(&conf_);
    errorinfo err;
    bool ret = false;
    if (conn->connect(err))
    {
        pool_.add(conn);
        ret = true;
    }
    return ret;
}

}}
