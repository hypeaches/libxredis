#ifndef LIBXREDIS_COMMANDIMPL_H
#define LIBXREDIS_COMMANDIMPL_H

#include <memory>
#include <functional>
#include "command_buffer.h"

struct redisReply;

namespace x{namespace redis{

class connection_pool;

class command_impl
{
public:
    command_impl();

public:
	void set_connection_pool(connection_pool* pool);
    int count();
	bool build(const char* cmd);
	bool exec();
    bool exec(long long int& integer);
    bool exec(const std::function<void(int index, long long int* integer, const char* string)>& cb);

private:
    bool parse(int index, redisReply* reply, const std::function<void(int index, long long int* integer, const char* string)>& cb);
    bool parse_reply(int index, redisReply* reply, const std::function<void(int index, long long int* integer, const char* string)>& cb);

private:
    connection_pool* connection_pool_;
	command_buffer cmdbuf_;
    int cmd_count_;
};

}}

#endif
