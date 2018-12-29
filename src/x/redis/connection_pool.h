#ifndef LIBXREDIS_CONNECTION_POOL_H
#define LIBXREDIS_CONNECTION_POOL_H

#include <vector>

namespace x{namespace redis{

struct options;
class connection;

class connection_pool
{
public:
    ~connection_pool();
    bool init(const options* opt);
    connection* create();
    void release(connection* conn);
    void increase();

private:
    int real_size_;
    const options* opt_;
    std::vector<connection*> pool_;
};

}}

#endif