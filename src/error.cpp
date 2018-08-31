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

error::error(int errno)
{
    printf("error(int errno)\n");
    reference_count = new int;
    *reference_count = 1;
    this->errno = errno;
    message = errmsg[errno];
}

error::error(const char* msg)
{
    printf("error(const char* msg)\n");
    reference_count = new int;
    *reference_count = 1;
    printf("test:%d\n", error::errno_redis_error);
    this->errno = (int)error::errno_redis_error;
    message = x::stringbuf(128)
        .append(msg)
        .moved_buffer();
    printf("test:%s\n", msg);
}

error::~error()
{
    printf("~error() 1\n");
    (*reference_count)--;
    if ((0 == *reference_count) && ((int)error::errno_redis_error == this->errno))
    {
        printf("~error() 2\n");
        delete message;
        delete reference_count;
    }
    message = nullptr;
    reference_count = nullptr;
}

error::error(error&& other)
{
    printf("error(error&& other)\n");
    reference_count = other.reference_count;
    (*reference_count)++;
    errno = other.errno;
    message = other.message;
    other.message = nullptr;
}

error::error(const error& other)
{
    printf("error(const error& other)\n");
    reference_count = other.reference_count;
    (*reference_count)++;
    errno = other.errno;
    message = other.message;
}

error& error::operator=(error&& other)
{
    printf("operator=(error&& other)\n");
    reference_count = other.reference_count;
    (*reference_count)++;
    errno = other.errno;
    message = other.message;
    other.message = nullptr;
    return *this;
}

error& error::operator=(const error& other)
{
    printf("operator=(const error& other)\n");
    reference_count = other.reference_count;
    (*reference_count)++;
    errno = other.errno;
    message = other.message;
    return *this;
}

}}
