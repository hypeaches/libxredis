#include "x/redis/connection.h"
#include <hiredis.h>
#include "x/redis/errorinfo.h"

namespace x{namespace redis{

connection::connection()
{
    conf_ = nullptr;
    cntx_ = nullptr;
}

connection::~connection()
{
    if (cntx_)
    {
        redisFree(cntx_);
        cntx_ = nullptr;
    }
}

void connection::set_conf(conf* c)
{
    conf_ = c;
}

bool connection::connect(errorinfo& err)
{
    for (int i = 0; i < conf_->conn_retry_times(); ++i)
    {
        reset_context();
        cntx_ = redisConnectWithTimeout(conf_->host(), conf_->port(), conf_->conn_timeout());
        if (cntx_ && (cntx_->err == 0))
        {
            return true;
        }
    }
    if (!cntx_)
    {
        err.set_error_message(conf_->host(), conf_->port(), error_code_redis_context_allocate_failed);
    }
    else if (cntx_->err)
    {
        err.set_error_message(conf_->host(), conf_->port(), cntx_->err);
    }
    reset_context();
    return false;
}

void connection::reset_context()
{
    if (cntx_)
    {
        redisFree(cntx_);
        cntx_ = nullptr;
    }
}

}}
