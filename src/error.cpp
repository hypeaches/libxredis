#include "x/redis/error.h"
#include "x/string/stringbuf.h"
#include <cstdio>

namespace x{namespace redis{

namespace
{

    const char* errmsg[] = {
        "ok",
        "redis error",
        "allocate redis context failed"
        "no available connection",
        "no redis reply",
    };

}

error::error()
{
    this->errno = error::errno_ok;
    message = errmsg[this->errno];
}

error::~error()
{
    if (error::errno_redis_error == this->errno)
    {
        delete message;
    }
    message = nullptr;
    this->errno = error::errno_ok;
}

error::error(error&& other)
{
    errno = other.errno;
    message = other.message;
    other.message = nullptr;
    other.errno = error::errno_ok;
}

error::error(const error& other)
{
    errno = other.errno;
    message = other.message;
}

error& error::operator=(error&& other)
{
    errno = other.errno;
    message = other.message;
    other.message = nullptr;
    other.errno = error::errno_ok;
    return *this;
}

error& error::operator=(const error& other)
{
    errno = other.errno;
    message = other.message;
    return *this;
}

void error::set(int errno)
{
    this->errno = errno;
    message = errmsg[errno];
}

void error::set(const char* msg)
{
    this->errno = error::errno_redis_error;
    message = x::stringbuf(128)
        .append(msg)
        .moved_buffer();
}

void error::set(int errno, error* err)
{
    if (err)
    {
        err->set(errno);
    }
}

void error::set(const char* msg, error* err)
{
    if (err)
    {
        err->set(msg);
    }
}

}}
