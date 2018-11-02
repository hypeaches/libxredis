#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

struct redisContext;

namespace x{namespace redis{

class conf;
class errorinfo;

class connection
{
public:
    connection();
    virtual ~connection();

    void set_conf(conf* c);
    redisContext* context() { return cntx_; }

    bool connect(errorinfo& err);

private:
    void reset_context();

private:
    conf* conf_;
    redisContext* cntx_;

};

}}

#endif
