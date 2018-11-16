#ifndef LIBXREDIS_CONNECTIONGUARD_H
#define LIBXREDIS_CONNECTIONGUARD_H

namespace x{namespace redis{

class connection;
class connection_pool;

class connection_guard
{
public:
	connection_guard(connection* conn, connection_pool* pool);
	~connection_guard();

private:
	connection* conn_;
	connection_pool* pool_;
};

}}

#endif
