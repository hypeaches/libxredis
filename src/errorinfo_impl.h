#ifndef LIBXREDIS_ERRORINFOIMPL_H
#define LIBXREDIS_ERRORINFOIMPL_H

namespace x{namespace redis{

class errorinfo;

class errorinfo_impl
{
public:
    static void set(const char* host, int port, int error_code, errorinfo* err);
    static void set(const char* host, int port, const char* msg, errorinfo* err);
};

}}

#endif
