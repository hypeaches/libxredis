#include "x/redis/errorinfo.h"

namespace x{namespace redis{

namespace
{

    const char* errmsg[] = {
        "ok",
        "redis context allocate failed",
    };
    const char* unkown_error_msg = "unknown error";

}

const char* errorinfo::error_message() const
{
    return buf_.buffer();
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
    if (!buf_.empty())
    {
        buf_.append(";")
    }
    buf_.append(host)
        .append(":")
        .append(port)
        .append(":")
        .append(msg);
}

}}
