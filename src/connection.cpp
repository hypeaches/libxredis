#include "x/redis/connection.h"
#include <sys/time.h>
#include <hiredis.h>
#include "x/redis/log.h"
#include "x/redis/options.h"

namespace x{namespace redis{

connection::connection()
{
    opt_ = nullptr;
    context_ = nullptr;
}

connection::~connection()
{
    opt_ = nullptr;
    if (context_)
    {
        redisFree(context_);
        context_ = nullptr;
    }
}

bool connection::init(const options* opt)
{
    opt_ = opt;
    return true;
}

bool connection::connect()
{
    timeval timeout;
    timeout.tv_sec = opt_->connect_timeout / 1000;
    timeout.tv_usec = opt_->connect_timeout % 1000 * 1000;

    context_ = redisConnectWithTimeout(
        opt_->host.c_str(),
        opt_->port,
        timeout
    );
    if (!context_)
    {
        XREDISLOG_WARNING(
            opt_->host.c_str(),
            opt_->port,
            "connect failed",
            ""
        );
        return false;
    }
    if (context_->err)
    {
        XREDISLOG_WARNING(
            opt_->host.c_str(),
            opt_->port,
            context_->errstr,
            ""
        );
        return false;
    }

    return true;
}

bool connection::disconnect()
{
    if (context_)
    {
        redisFree(context_);
        context_ = nullptr;
    }
    return true;
}


}}