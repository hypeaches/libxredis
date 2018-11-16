#ifndef LIBXREDIS_COMMANDBUFFER_H
#define LIBXREDIS_COMMANDBUFFER_H

#include <x/string/stringbuf.h>

namespace x{namespace redis{

class connection;

class command_buffer
{
public:
    command_buffer();
    bool append(const char* cmd);
    int build_command(connection* conn);

private:
    const char* get_next_command();

private:
    int cmd_count_;
    const char* cmd_;
    x::stringbuf buf_;
};

}}

#endif
