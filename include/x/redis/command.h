#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

namespace x{namespace redis{

class connection_pool;

class command
{
public:
    command();
    command(connection_pool* pool);
    static connection_pool* default_connection_pool;

private:
    connection_pool* connection_pool_;
};

}}

#endif