#ifndef LIBXREDIS_REPLYGUARD_H
#define LIBXREDIS_REPLYGUARD_H

struct redisReply;

namespace x{namespace redis{

class reply_guard
{
public:
    reply_guard(redisReply*& reply);
    ~reply_guard();

private:
    redisReply* reply_;
};

}}

#endif
