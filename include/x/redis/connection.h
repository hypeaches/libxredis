#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

#include "x/redis/connection_pool.h"
#include "x/redis/error.h"

struct redisContext;

namespace x{namespace redis{

class connection : public x::redis::connection_pool
{
public:
    connection();
    ~connection();
    void set_host(const char* hostname, int port, int timeout);
    error connect();
    redisContext* context() {return cntx_;}

public:
    virtual x::redis::connection* lend() override;
    virtual void give_back(x::redis::connection* conn) override;

private:
    void reset_context();

private:
    redisContext* cntx_;
    char* hostname_;
    int port_;
    int timeout_;
    bool is_used_;
};

}}

#endif
