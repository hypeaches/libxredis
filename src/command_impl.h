#ifndef LIBXREDIS_COMMANDIMPL_H
#define LIBXREDIS_COMMANDIMPL_H

#include "command_buffer.h"

namespace x{namespace redis{

class connection_pool;

class command_impl
{
public:
	void set_connection_pool(connection_pool* pool);
	bool build(const char* cmd);
	bool exec();

private:
    connection_pool* connection_pool_;
	command_buffer cmdbuf_;
};

}}

#endif
