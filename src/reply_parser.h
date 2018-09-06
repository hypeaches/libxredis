#ifndef LIBXREDIS_REPLYPARSER_H
#define LIBXREDIS_REPLYPARSER_H

struct redisReply;

namespace x{namespace redis{

class connection;
class errorinfo;

class reply_parser
{
public:
    static int int_reply(redisReply*& reply, const connection* conn, errorinfo* err);
};

}}

#endif
