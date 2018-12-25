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
    static int init(const options& opt);

public:
    int exec(const std::string& cmd);
    int exec(const std::string& cmd, std::string& req);
    int exec(const std::string& cmd, long long int& req);
    int exec(const std::string& cmd, std::vector<std::string>& req);
    int exec(const std::vector<std::string>& cmds);
    int exec(const std::vector<std::string>& cmds, std::vector<std::string>& req);
};

}}

#endif
