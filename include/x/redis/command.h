#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

namespace x{namespace redis{

class connection_pool;
class errorinfo;

class command
{
public:
    command(connection_pool* pool);

    //字符串操作
public:
    int append(const char* key, const char* val, errorinfo* err = nullptr);

private:
    connection_pool* pool_;
};

}}

#endif
