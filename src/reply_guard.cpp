#include "reply_guard.h"
#include <hiredis.h>

namespace x{namespace redis{

reply_guard::reply_guard(redisReply*& reply)
    : reply_(reply)
{
}

reply_guard::~reply_guard()
{
    if (reply_)
    {
        freeReplyObject(reply_);
        reply_ = NULL;
    }
}

}}
