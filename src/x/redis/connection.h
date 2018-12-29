#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

#include <string>

struct redisContext;

namespace x{namespace redis{

struct options;

class connection
{
public:
    connection();
    ~connection();
    bool init(const std::string& host, int port, const options* opt);
    bool connect();
    bool disconnect();
    const options* option();
    redisContext* context() { return context_; }

private:
    int port_;
    std::string host_;
    const options* opt_;
    redisContext* context_;
};

}}

#endif