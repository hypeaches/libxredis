#include "errorinfo_impl.h"
#include "x/string/stringbuf.h"
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

namespace
{

    const char* errmsg[] = {
        "ok",
        "redis errorinfo",
        "allocate redis context failed"
        "no available connection",
        "no redis reply",
    };

    const int error_buf_default_size = 128;

}

void errorinfo_impl::set(const char* host, int port, int error_code, errorinfo* err)
{
    if (err)
    {
        err->error_code = error_code;
        if (error_code == errorinfo::error_code_ok)
        {
            err->message = errmsg[errorinfo::error_code_ok];
        }
        else
        {
            err->message = x::stringbuf(error_buf_default_size)
                .append("redis error:")
                .append(host).append(":")
                .append(port).append(":")
                .append(errmsg[error_code])
                .moved_buffer();
        }
    }
}

void errorinfo_impl::set(const char* host, int port, const char* msg, errorinfo* err)
{
    if (err)
    {
        err->error_code = errorinfo::error_code_redis_error;
        err->message = x::stringbuf(error_buf_default_size)
            .append("redis error:")
            .append(host).append(":")
            .append(port).append(":")
            .append(msg)
            .moved_buffer();
    }
}

}}
