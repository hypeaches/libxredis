#include "connection.h"
#include <hiredis.h>
#include "x/redis/conf.h"

namespace x{namespace redis{

connection::connection()
{
    conf_ = nullptr;
    context_ = nullptr;
}

void connection::set_conf(const conf* c)
{
    conf_ = c;
}

bool connection::connect()
{
    if (!conf_)
    {
        //todo:
    }

    bool ret = false;
    int port = conf_->port();
    const char* host = conf_->host();
    int retry_times = conf_->connect_retry_times();
    timeval connect_timeout = conf_->connect_timeout();
    
    for (int i = 0; i < retry_times; i++)
    {
        context_ = redisConnectWithTimeout(host, port, connect_timeout);
        if (!context_)
        {
            //todo:创建context失败
        }
        else if (context_->err)
        {
            //todo:redis返回一个错误
        }
        else
        {
            ret = true;
            break;
        }
        reset_context();
    }
    return ret;
}

bool connection::reconnect()
{
	reset_context();
	return connect();
}

redisContext* connection::context()
{
    return context_;
}

void connection::reset_context()
{
    if (context_)
    {
        redisFree(context_);
        context_ = nullptr;
    }
}

}}
