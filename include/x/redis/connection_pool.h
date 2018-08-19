#ifndef LIBXREDIS_CONNECTIONPOOL_H
#define LIBXREDIS_CONNECTIONPOOL_H

namespace x{namespace redis{

class connection;

class connection_pool
{
public:
    virtual ~connection_pool(){}
    virtual connection* lend() = 0;
    virtual void give_back(connection* conn) = 0;
};

}}

#endif
