#include "x/redis/connection_pool.h"
#include "connection_pool_impl.h"

namespace x{namespace redis{

connection_pool::~connection_pool(){}

connection_pool* connection_pool::default()
{
    static connection_pool_impl impl;
    return &impl;
}

}}
