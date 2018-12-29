#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

#include <string>
#include <vector>

namespace x{namespace redis{

struct options;

class command
{
public:
    command();
    ~command();

public:
    enum {
        exec_ok = 0,
        exec_null,
        exec_failed
    };
    static void init(const options* opt);
    static bool add_pool(const char* host, int port);

public:
    bool exec(const std::string& cmd);
    bool exec(const std::string& cmd, std::string& req);
    bool exec(const std::string& cmd, long long int& req);
    bool exec(const std::string& cmd, std::vector<std::string>& req);
    bool exec(const std::vector<std::string>& cmds);
    bool exec(const std::vector<std::string>& cmds, std::vector<std::string>& req);
};

}}

#endif
