#include "connection_pool_impl.h"
#include "x/redis/conf.h"
#include "connection.h"

namespace x{namespace redis{

connection* conn;

connection_pool_impl::~connection_pool_impl()
{
    if (conn)
    {
        delete conn;
        conn = nullptr;
    }
}

connection* connection_pool_impl::create()
{
    return conn;
}

void connection_pool_impl::release(connection* conn)
{

}

bool connection_pool_impl::init(const conf* c)
{
    conf_ = c;
    conn = new connection();
    conn->set_conf(c);
    return conn->connect();
}

const conf* connection_pool_impl::get_conf() const
{
    return conf_;
}


}}