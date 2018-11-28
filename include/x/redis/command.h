#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

#include <functional>

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
    int count();
    command& build(const char* cmd);
    bool exec();
    bool exec(long long int& integer);
    bool exec(const std::function<void(int index, long long int* integer, const char* string)>& cb);

private:
    connection_pool* connection_pool_;
    command_impl* impl_;
};

}}

#endif
