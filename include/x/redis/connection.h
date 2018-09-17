#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

#include "x/redis/connection_pool.h"

struct redisContext;

namespace x{namespace redis{

class errorinfo;

class connection : public x::redis::connection_pool
{
public:
    connection();
    ~connection();
    void set_host(const char* hostname, int port, int timeout);
    int connect();
    redisContext* context() { return cntx_; }
    const char* host() const { return hostname_; }
    int port() const { return port_; }

public:
    virtual x::redis::connection* lend() override;
    virtual void give_back(x::redis::connection* conn) override;
    virtual int conn_retry_times() override;
    virtual int retry_times() override;

private:
    void reset_context();

private:
    redisContext* cntx_;
    char* hostname_;
    int port_;
    int timeout_;
    bool is_used_;

    int conn_retry_times_;
    int retry_times_;
};

}}

#endif
