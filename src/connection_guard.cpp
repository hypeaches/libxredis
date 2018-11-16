#include "connection_guard.h"
#include "x/redis/connection_pool.h"
#include "connection.h"

namespace x{namespace redis{

connection_guard::connection_guard(connection* conn, connection_pool* pool)
{
	conn_ = conn;
	pool_ = pool;
}

connection_guard::~connection_guard()
{
	if (conn_ && pool_)
	{
		pool_->release(conn_);
	}
}

}}
