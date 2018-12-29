#include "x/redis/command.h"

#include <hiredis.h>

#include "x/redis/options.h"
#include "x/redis/connection_pool_group.h"

namespace x{namespace redis{


namespace
{

class connection_helper
{
public:
    connection_helper();
    ~connection_helper();

    int conn_index;
    connection* conn;
};

connection_helper::connection_helper()
{
    conn = connection_pool_group::instance()->create_connection(conn_index);
}

connection_helper::~connection_helper()
{
    connection_pool_group::instance()->release_connection(conn, conn_index);
}

}


command::command()
{
}

command::~command()
{
}

void command::init(const options* opt)
{
    connection_pool_group::instance()->init(opt);
}

bool command::add_pool(const char* host, int port)
{
    return connection_pool_group::instance()->add_pool(host, port);
}

bool command::exec(const std::string& cmd, std::string& req) 
{
    return false;
}

bool command::exec(const std::string& cmd, long long int& req) 
{
    return command::exec_failed;
}

bool command::exec(const std::string& cmd) 
{
    return command::exec_failed;
}

bool command::exec(const std::string& cmd, std::vector<std::string>& req) 
{
    return command::exec_failed;
}

bool command::exec(const std::vector<std::string>& cmds) 
{
    return command::exec_failed;
}

bool command::exec(const std::vector<std::string>& cmds, std::vector<std::string>& req) 
{
    return command::exec_failed;
}


}}
