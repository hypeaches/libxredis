#ifndef LIBXREDIS_ERRORINFO_H
#define LIBXREDIS_ERRORINFO_H

namespace x{namespace redis{

class errorinfo
{
public:
    enum
    {
        error_code_ok,
        error_code_unkown,
        error_code_redis_error,
        error_code_allocate_redis_context_failed,
        error_code_no_available_conn,
        error_code_no_redis_reply,
    };

    int error_code;
    const char* message;

    errorinfo();
    ~errorinfo();

private:
    errorinfo(errorinfo&& other);
    errorinfo(const errorinfo& other);
    errorinfo& operator=(errorinfo&& other);
    errorinfo& operator=(const errorinfo& other);
};

}}

#endif
