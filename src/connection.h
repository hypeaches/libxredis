#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

struct redisContext;

namespace x{namespace redis{

class conf;

class connection
{
public:
    connection();

public:
    void set_conf(const conf* c);
    bool connect();
	bool reconnect();
    redisContext* context();

private:
    void reset_context();

private:
    const conf* conf_;
    redisContext* context_;
};

}}

#endif
