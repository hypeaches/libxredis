#include "x/redis/errorinfo.h"
#include <x/string/stringbuf.h>
#include "x/redis/command.h"
#include <cstdio>
namespace x{namespace redis{

namespace
{

    const char* errmsg[] = {
        "ok",
        "allocate redis context failed",
        "no available connection",
        "no redis reply",
        "redis reply nil",
        "redis reply error",
    };
    const char* unkown_error_msg = "unknown error";

}

errorinfo::errorinfo()
{
    host = nullptr;
    port = 0;
    message_max_size = 1024;
    message = new char[message_max_size];
    buf = new x::stringbuf(message, message_max_size);
}

errorinfo::~errorinfo()
{
    if (message)
    {
        delete message;
        message = nullptr;
    }
    if (buf)
    {
        delete buf;
        buf = nullptr;
    }
}

void errorinfo::set_error_message(int ec)
{
    const char* msg = nullptr;
    if ((ec > error_code_ok) && (ec < error_code_reply_error))
    {
        msg = errmsg[ec];
    }
    else
    {
        msg = unkown_error_msg;
    }

    const char* phost = nullptr;
    if (host)
    {
        phost = host;
    }
    else
    {
        host = "";
    }

    snprintf(message, message_max_size, "redis error:%s:%s:%d", msg, phost, port);
}

void errorinfo::set_error_message(const char* errmsg)
{
    const char* msg = nullptr;
    if (errmsg)
    {
        msg = errmsg;
    }
    else
    {
        msg = unkown_error_msg;
    }

    const char* phost = nullptr;
    if (host)
    {
        phost = host;
    }
    else
    {
        host = "";
    }

    snprintf(message, message_max_size, "redis error:%s:%s:%d", msg, phost, port);
}

}}
