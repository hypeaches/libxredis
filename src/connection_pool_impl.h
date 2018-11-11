#ifndef LIBXREDIS_CONNECTIONPOOLIMPL_H
#define LIBXREDIS_CONNECTIONPOOLIMPL_H

#include "x/redis/connection_pool.h"

namespace x{namespace redis{

class connection_pool_impl : public connection_pool
{
public:
    virtual ~connection_pool_impl();
    /// 从连接池获取一个连接
    virtual connection* create() override;
    /// 返还连接
    virtual void release(connection* conn) override;
    /// 初始化
    virtual bool init(const conf* c) override;
    /// 获取配置
    virtual const conf* get_conf() const override;
    /// 获取默认实现的连接池
    static connection_pool* default_pool();

private:
    const conf* conf_;
};

}}

#endif