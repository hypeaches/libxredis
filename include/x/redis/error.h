#ifndef LIBXREDIS_ERROR_H
#define LIBXREDIS_ERROR_H

namespace x{namespace redis{

struct error
{
    enum
    {
        errno_ok,
        errno_redis_error,
        errno_allocate_redis_context_failed,
        errno_no_available_conn,
        errno_no_redis_reply,
    };

    int errno;
    const char* message;
    int* reference_count;

    error(int errno);
    error(const char* msg);
    error(error&& other);
    error(const error& other);
    ~error();
    error& operator=(error&& other);
    error& operator=(const error& other);
};

}}

#endif
