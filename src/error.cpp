#include "x/redis/errorinfo.h"
#include "x/string/stringbuf.h"
#include <cstdio>

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

}

errorinfo::errorinfo()
{
    this->error_code = errorinfo::error_code_ok;
    message = errmsg[this->error_code];
}

errorinfo::~errorinfo()
{
    if (errorinfo::error_code_redis_error == this->error_code)
    {
        delete message;
    }
    message = nullptr;
    this->error_code = errorinfo::error_code_ok;
}

errorinfo::errorinfo(errorinfo&& other)
{
    this->error_code = other.error_code;
    message = other.message;
    other.message = nullptr;
    other.error_code = errorinfo::error_code_ok;
}

errorinfo::errorinfo(const errorinfo& other)
{
    this->error_code = other.error_code;
    message = other.message;
}

errorinfo& errorinfo::operator=(errorinfo&& other)
{
    this->error_code = other.error_code;
    message = other.message;
    other.message = nullptr;
    other.error_code = errorinfo::error_code_ok;
    return *this;
}

errorinfo& errorinfo::operator=(const errorinfo& other)
{
    this->error_code = other.error_code;
    message = other.message;
    return *this;
}

void errorinfo::set(int error_code)
{
    this->error_code = error_code;
    message = errmsg[this->error_code];
}

void errorinfo::set(const char* msg)
{
    this->error_code = errorinfo::error_code_redis_error;
    message = x::stringbuf(128)
        .append(msg)
        .moved_buffer();
}

void errorinfo::set(int error_code, errorinfo* err)
{
    if (err)
    {
        err->set(error_code);
    }
}

void errorinfo::set(const char* msg, errorinfo* err)
{
    if (err)
    {
        err->set(msg);
    }
}

}}
