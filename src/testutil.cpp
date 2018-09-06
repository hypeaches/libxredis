#include "testutil.h"
#include <hiredis.h>
#include <cstdio>

namespace x{namespace redis{

namespace
{

void print_redisreply1(const redisReply* reply)
{
    printf("%s:%d\n", "type", reply->type);
    printf("%s:%lld\n", "integer", reply->integer);
    printf("%s:%llu\n", "len", reply->len);
    printf("%s:%s\n", "str", reply->str ? reply->str : "nullptr");
    printf("%s:%llu\n", "elements", reply->elements);
}

void print_redisreply2(const redisReply* reply)
{
    printf("%s:%d\n", "type", reply->type);
    printf("%s:%lld\n", "integer", reply->integer);
    printf("%s:%llu\n", "len", reply->len);
    printf("%s:%s\n", "str", reply->str ? reply->str : "nullptr");
    printf("%s:%llu\n", "elements", reply->elements);
}

}

void testutil::print_redisreply(const redisReply* reply)
{
    printf("**********redisReply**********\n");
    print_redisreply1(reply);
    printf("%s:", "elements");
    if (!reply->elements)
    {
        printf("nullptr\n");
    }
    else
    {
        for (size_t i = 0; i < reply->elements; ++i)
        {
            print_redisreply2(reply);
        }
    }
}

}}
