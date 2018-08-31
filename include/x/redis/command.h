#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

#include "x/redis/error.h"

namespace x{namespace redis{

class connection_pool;

class command
{
public:
    command(connection_pool* pool);

    //字符串操作
public:
    error append(const char* key, const char* val);

private:
    connection_pool* pool_;
};

}}

#endif
