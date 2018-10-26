#ifndef LIBXREDIS_CONNECTIONPOOLIMPL_H
#define LIBXREDIS_CONNECTIONPOOLIMPL_H

#include <vector>
#include <x/pool/objectpool.h"
#include "x/redis/connection_pool.h"
#include "conf.h"

namespace x{namespace redis{

class connection;

class connection_pool_impl : public connection_pool
{
public:
    connection_pool_impl();
    virtual ~connection_pool_impl();
    /// 从连接池获取一个连接
    virtual connection* create() override;
    /// 返还连接
    virtual void release(connection* conn) override;
    /// 获取连接重试次数
    virtual int conn_retry_times() override;
    /// 获取连接超时时间，单位：毫秒
    virtual int conn_timeout() override;
    /// 获取读写重试次数
    virtual int rw_retry_times() override;
    /// 获取读写超时时间
    virtual int rw_timeout() override;
    /// 增加连接
    virtual bool add(const char* host, int port) override;

private:
    conf conf_;
    x::objectpool<connection> pool_;
};

}}

#endif
