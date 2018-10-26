#include "x/redis/errorinfo.h"
#include <x/string/stringbuf.h>

namespace x{namespace redis{

namespace
{

    const char* errmsg[] = {
        "ok",
    };
    const char* unkown_error_msg = "unknown error";

}

errorinfo::errorinfo()
{
    buf = new x::stringbuf();
}

errorinfo::~errorinfo()
{
    if (buf)
    {
        delete buf;
        buf = nullptr;
    }
}

const char* errorinfo::error_message() const
{
    return buf->buffer();
}

void errorinfo::set_error_message(const char* host, int port, int ec)
{
    const char* msg = nullptr;
    if ((ec >= error_code_ok) && (ec < error_code_unknown))
    {
        msg = errmsg[ec];
    }
    else
    {
        msg = unkown_error_msg;
    }

    set_error_message(host, port, msg);
}

void errorinfo::set_error_message(const char* host, int port, const char* errmsg)
{
    if (!buf->empty())
    {
        buf->append(";")
    }
    buf->append(host)
        .append(":")
        .append(port)
        .append(":")
        .append(msg);
}

}}
