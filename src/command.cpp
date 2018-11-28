#include "x/redis/command.h"
#include "command_impl.h"

namespace x{namespace redis{

connection_pool* command::default_connection_pool = nullptr;

command::command()
{
    connection_pool_ = default_connection_pool;
    static command_impl impl;
    impl.set_connection_pool(connection_pool_);
    impl_ = &impl;
}

command::command(connection_pool* pool)
{
    connection_pool_ = pool;
    static command_impl impl;
    impl.set_connection_pool(connection_pool_);
    impl_ = &impl;
}

command::~command()
{
}

int command::count()
{
    return impl_->count();
}

command& command::build(const char* cmd)
{
    impl_->build(cmd);
    return *this;
}

bool command::exec()
{
    return impl_->exec();
}

bool command::exec(long long int& integer)
{
    return impl_->exec(integer);
}

bool command::exec(const std::function<void(int index, long long int* integer, const char* string)>& cb)
{
    return impl_->exec(cb);
}

}}
