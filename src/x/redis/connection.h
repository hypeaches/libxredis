#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

struct redisContext;

namespace x{namespace redis{

struct options;

class connection
{
public:
    connection();
    ~connection();
    bool init(const options& opt);
    bool connect();
    bool disconnect();
    redisContext* context() { return context_; }

private:
    const options* opt_;
    redisContext* context_;
};

}}

#endif