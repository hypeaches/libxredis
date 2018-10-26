#ifndef LIBXREDIS_CONNECTIONPOOL_H
#define LIBXREDIS_CONNECTIONPOOL_H

namespace x{namespace redis{

class connection;

class connection_pool
{
public:
    virtual ~connection_pool();
    /// 从连接池获取一个连接
    virtual connection* create() = 0;
    /// 返还连接
    virtual void release(connection* conn) = 0;
    /// 获取连接重试次数
    virtual int conn_retry_times() = 0;
    /// 获取连接超时时间，单位：毫秒
    virtual int conn_timeout() = 0;
    /// 获取读写重试次数
    virtual int rw_retry_times() = 0;
    /// 获取读写超时时间
    virtual int rw_timeout() = 0;
    /// 增加连接，只允许在进程初始化阶段调用
    virtual bool add(const char* host, int port) = 0;
    /// 获取默认实现的连接池
    static connection_pool* default();
};

}}

#endif
