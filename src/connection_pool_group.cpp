#include "x/redis/connection_pool_group.h"

#include <atomic>
#include <vector>
#include <mutex>

#include "x/redis/log.h"
#include "x/redis/options.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool.h"

namespace x{namespace redis{

namespace {

std::atomic<uint64_t> pool_group_index(0);
std::vector<const options*> options_group;
static thread_local std::vector<connection_pool*> pool_group;

}

connection_pool_group::~connection_pool_group()
{}

connection_pool_group::connection_pool_group()
{}

connection_pool_group::connection_pool_group(connection_pool_group&&)
{}

connection_pool_group::connection_pool_group(const connection_pool_group&)
{}

connection_pool_group& connection_pool_group::operator=(connection_pool_group&&)
{
    return *this;
}

connection_pool_group& connection_pool_group::operator=(const connection_pool_group&)
{
    return *this;
}

connection_pool_group* connection_pool_group::instance()
{
    static connection_pool_group group;
    return &group;
}

bool connection_pool_group::add_pool(const options* opt)
{
    options_group.push_back(opt);
    return true;
}

connection* connection_pool_group::create_connection(int& pool_index)
{
    init_group();
    uint64_t index = pool_group_index.fetch_add(1);
    uint64_t pool_group_size = static_cast<uint64_t>(pool_group.size());
    pool_index = static_cast<int>(index % pool_group_size);
    connection_pool* pool = pool_group[pool_index];
    connection* conn = pool->create();
    if (!conn)
    {
        pool->increase();
    }
    conn = pool->create();
    return nullptr;
}

void connection_pool_group::release_connection(connection* conn, int pool_index)
{
    if (conn)
    {
        pool_group[pool_index]->release(conn);
    }
}

bool connection_pool_group::init_group() {
    if (!pool_group.empty())
    {
        return true;
    }

    connection_pool* pool = nullptr;
    for (const options* opt : options_group)
    {
        pool = new connection_pool;
        pool->init(opt);
        pool_group.push_back(pool);
    }
    return true;
}

}}