#include "x/redis/errorinfo.h"

namespace x{namespace redis{

errorinfo::errorinfo()
{
    this->error_code = errorinfo::error_code_ok;
    message = nullptr;
}

errorinfo::~errorinfo()
{
    if (message && (this->error_code != errorinfo::error_code_ok))
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
    other.error_code = errorinfo::error_code_ok;
    other.message = nullptr;
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
    other.error_code = errorinfo::error_code_ok;
    other.message = nullptr;
    return *this;
}

errorinfo& errorinfo::operator=(const errorinfo& other)
{
    this->error_code = other.error_code;
    message = other.message;
    return *this;
}

}}
