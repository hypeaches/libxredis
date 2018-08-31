#ifndef LIBXREDIS_ERROR_H
#define LIBXREDIS_ERROR_H

namespace x{namespace redis{

class error
{
public:
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

    error();
    ~error();
    void set(int errno);
    void set(const char* msg);
    static void set(int errno, error* err);
    static void set(const char* msg, error* err);

private:
    error(error&& other);
    error(const error& other);
    error& operator=(error&& other);
    error& operator=(const error& other);
};

}}

#endif
