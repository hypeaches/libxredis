#include "x/redis/command.h"

namespace x{namespace redis{

connection_pool* command::default_connection_pool = nullptr;

command::command()
{
    connection_pool_ = default_connection_pool;
}

command::command(connection_pool* pool)
{
    connection_pool_ = pool;
}

}}