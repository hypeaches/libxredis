#include "connection_pool_impl.h"

namespace x{namespace redis{

connection_pool_impl::~connection_pool_impl()
{
}

connection* connection_pool_impl::create()
{
}

void connection_pool_impl::release(connection* conn)
{
}

int connection_pool_impl::conn_retry_times()
{
}

int connection_pool_impl::conn_timeout()
{
}

int connection_pool_impl::rw_retry_times()
{
}

int connection_pool_impl::rw_timeout()
{
}

bool connection_pool_impl::add(const char* host, int port)
{
}

}}
