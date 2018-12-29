#include "x/redis/options.h"

namespace x{namespace redis{

options::options()
{
    port = 6379;
    retry_times = 3;
    read_write_timeout = 1000;
    pool_max_connections = 1;
    pool_max_connections = 5;
    host = "127.0.0.1";
}

}}