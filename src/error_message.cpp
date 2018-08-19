#include "x/redis/error_message.h"
#include <cstdio>
namespace x{namespace redis{

error_message::error_message()
{
    errmsg_len_ = 1024;
    errmsg_ = new char[errmsg_len_];
}

error_message::~error_message()
{
    if (errmsg_)
    {
        delete errmsg_;
        errmsg_ = nullptr;
        errmsg_len_ = 0;
    }
}

void error_message::reset_error()
{
    errmsg_[0] = 0;
}

}}
