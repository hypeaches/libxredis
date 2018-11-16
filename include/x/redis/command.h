#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

namespace x{namespace redis{

class command_impl;
class connection_pool;

class command
{
public:
    command();
    command(connection_pool* pool);
    ~command();
    static connection_pool* default_connection_pool;

public:
    command& build(const char* cmd);
    bool exec();

private:
    connection_pool* connection_pool_;
    command_impl* impl_;
};

}}

#endif
