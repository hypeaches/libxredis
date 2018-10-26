#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

struct redisContext;

namespace x{namespace redis{

class conf;

class connection
{
public:
    connection();
    virtual ~connection();

    void set_conf(conf* c);
    redisContext* context() { return cntx_; }

    int connect();

private:
    void reset_context();

private:
    redisContext* cntx_;
    conf* conf_;

};

}}

#endif
