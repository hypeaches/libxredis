#ifndef LIBXREDIS_ERROR_H
#define LIBXREDIS_ERROR_H

namespace x{namespace redis{

class errorinfo
{
public:
    enum
    {
        error_code_ok,
        error_code_redis_error,
        error_code_allocate_redis_context_failed,
        error_code_no_available_conn,
        error_code_no_redis_reply,
    };

    int error_code;
    const char* message;

    errorinfo();
    ~errorinfo();
    void set(int error_code);
    void set(const char* msg);
    static void set(int error_code, errorinfo* err);
    static void set(const char* msg, errorinfo* err);

private:
    errorinfo(errorinfo&& other);
    errorinfo(const errorinfo& other);
    errorinfo& operator=(errorinfo&& other);
    errorinfo& operator=(const errorinfo& other);
};

}}

#endif
