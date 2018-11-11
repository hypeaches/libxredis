#ifndef LIBXREDIS_CONNECTIONPOOL_H
#define LIBXREDIS_CONNECTIONPOOL_H

namespace x{namespace redis{

class conf;
class connection;

class connection_pool
{
public:
    virtual ~connection_pool();
    /// 从连接池获取一个连接
    virtual connection* create() = 0;
    /// 返还连接
    virtual void release(connection* conn) = 0;
    /// 初始化
    virtual bool init(const conf* c) = 0;
    /// 获取配置
    virtual const conf* get_conf() const = 0;
    /// 获取默认实现的连接池
    static connection_pool* default_pool();
};

}}

#endif
