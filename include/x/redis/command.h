#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

#include "x/redis/command_impl.h"

namespace x{namespace redis{

class connection_pool;

class command
{
public:
    command();
    ~command();
    static int init(int count);

public:
    template <typename ...T>
    command& build(T... args);
    command& start_build(const char* op);
    command& stop_build();

public:
    enum
    {
        result_ok = 0,
        result_failed,
        result_half
    };
    int exec(long long int& res);
    int exec(std::string& res);
    int exec(std::vector<std::string>& res, int count_per_op);
    int exec(std::vector<std::vector<std::string>>& res, int count_per_op);

public:
    const char* error_message() const;

private:
    x::redis::command_impl* impl_;
};

template <typename ...T>
command& command::build(T ...args)
{
    if (impl_)
    {
        impl_->build(args...);
    }
    return *this;
}

}}

#endif
