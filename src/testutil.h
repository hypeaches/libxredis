#ifndef LIBXREDIS_TESTUTIL_H
#define LIBXREDIS_TESTUTIL_H

#include <cstring>

struct redisReply;

namespace x{namespace redis{

class testutil
{
public:
    static void print_redisreply(const redisReply* reply);
};

}}

#endif
