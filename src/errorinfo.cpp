#include "x/redis/errorinfo.h"
#include "x/redis/command.h"

namespace x{namespace redis{

namespace
{

    const char* errmsg[] = {
        "ok",
        "allocate redis context failed",
        "no available connection",
        "no redis reply",
        "redis reply nil"
        "redis reply error",
    };
    const char* unkown_error_msg = "unknown error";

}

const char* errorinfo::message(int ec)
{
    if ((ec >= error_code_ok) && (ec <= error_code_reply_error))
    {
        return errmsg[ec];
    }
    return unkown_error_msg;
}

}}
