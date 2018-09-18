#ifndef LIBXREDIS_ERRORINFO_H
#define LIBXREDIS_ERRORINFO_H

namespace x{namespace redis{

enum
{
    error_code_ok,
    error_code_allocate_redis_context_failed,
    error_code_no_available_conn,
    error_code_no_redis_reply,
    error_code_reply_nil,
    error_code_reply_error,
};

class errorinfo
{
public:
    const char* host;
    int port;
    char* message;
    int message_max_size;

    errorinfo();
    ~errorinfo();
    void set_error_message(int ec);
    void set_error_message(const char* msg);
};

}}

#endif
