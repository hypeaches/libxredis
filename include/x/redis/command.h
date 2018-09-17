#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

#include "cstdio"
#include <x/string/stringbuf.h>

struct redisReply;

namespace x{namespace redis{

class connection_pool;
class errorinfo;

class command
{
public:
    command(connection_pool* pool);

public:
    template <typename ...T>
    long long int exec_integer(T... args);
    int exec(const char* cmd, long long int* rep);

private:
    int do_redis_command(const char* cmd, redisReply*& rep);

private:
    connection_pool* pool_;
};

template <typename T>
void build_cmd(x::stringbuf& buf, T t)
{
    buf.append(t).append(" ");
}

template <typename T, typename ...Args>
void build_cmd(x::stringbuf& buf, T head, Args... args)
{
    buf.append(head).append(" ");
    build_cmd(buf, args...);
}

template <typename ...T>
long long int command::exec_integer(T ...args)
{
    x::stringbuf buf(1024);
    build_cmd(buf, args...);
    printf("%s\n", buf.buffer());
    return 0;
}

}}

#endif
