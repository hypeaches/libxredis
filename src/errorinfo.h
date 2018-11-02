#ifndef LIBXREDIS_ERRORINFO_H
#define LIBXREDIS_ERRORINFO_H

#include <x/string/stringbuf.h>

namespace x{namespace redis{

enum
{
    error_code_ok,
    error_code_redis_context_allocate_failed,
    error_code_unknown
};

class errorinfo
{
public:
    const char* error_message() const;
    void set_error_message(const char* host, int port, int ec);
    void set_error_message(const char* host, int port, const char* msg);

private:
    x::stringbuf buf_;
};

}}

#endif
