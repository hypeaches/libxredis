#include "x/redis/command.h"
#include "x/redis/connection_pool.h"

namespace x{namespace redis{

command::command()
{
}

command::~command()
{
}

int command::init(const options& opt)
{
    return 0;
}

int command::exec(const std::string& cmd, std::string& req) 
{
    return command::exec_failed;
}

int command::exec(const std::string& cmd, long long int& req) 
{
    return command::exec_failed;
}

int command::exec(const std::string& cmd) 
{
    return command::exec_failed;
}

int command::exec(const std::string& cmd, std::vector<std::string>& req) 
{
    return command::exec_failed;
}

int command::exec(const std::vector<std::string>& cmds) 
{
    return command::exec_failed;
}

int command::exec(const std::vector<std::string>& cmds, std::vector<std::string>& req) 
{
    return command::exec_failed;
}


}}
