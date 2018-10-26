#ifndef LIBXREDIS_ERRORINFO_H
#define LIBXREDIS_ERRORINFO_H

namespace x{

    class stringbuf;

}

namespace x{namespace redis{

enum
{
    error_code_ok,
    error_code_unknown
};

class errorinfo
{
public:
    errorinfo();
    ~errorinfo();
    const char* error_message() const;
    void set_error_message(const char* host, int port, int ec);
    void set_error_message(const char* host, int port, const char* msg);

private:
    x::stringbuf* buf;
};

}}

#endif
