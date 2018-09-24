#include "connection_guard.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool.h"

namespace x{namespace redis{

connection_guard::connection_guard(connection*& conn, connection_pool* pool)
    : conn_(conn)
    , pool_(pool)
{
}

connection_guard::~connection_guard()
{
    pool_->release(conn_);
    conn_ = nullptr;
}

}}
