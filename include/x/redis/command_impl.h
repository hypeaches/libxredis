#ifndef LIBXREDIS_COMMANDIMPL_H
#define LIBXREDIS_COMMANDIMPL_H

#include <x/string/stringbuf.h>

namespace x{namespace redis{

class command_impl
{
private:
    connection_pool* pool_;
    x::stringbuf buf_;
    bool is_build_start_;
};

}}

#endif
