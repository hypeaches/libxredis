#ifndef LIBXREDIS_CONF_H
#define LIBXREDIS_CONF_H

#include <sys/time.h>

namespace x{namespace redis{

class conf
{
public:
    conf();

public:
    void set_host(const char* host, int port);
    /// 设置连接重试次数
    void set_connect_retry_times(int retry_times);
    /// 设置连接超时时间，单位：毫秒
    void set_connect_timeout(int timeout);
    /// 设置连接池中连接数
    void set_connect_max_num(int max_num);
     /// 设置读写重试次数
    void set_rw_retry_times(int retry_times);
    /// 设置读写超时时间，单位：毫秒
    void set_rw_timeout(int timeout);

    const char* host() const;
    int port() const;
    /// 获取连接重试次数
    int connect_retry_times() const;
    /// 获取连接超时时间，单位：毫秒
    timeval connect_timeout() const;
    /// 获取连接池中连接数
    int connect_max_num() const;
    /// 获取读写重试次数
    int rw_retry_times() const;
    /// 获取读写超时时间，单位：毫秒
    timeval rw_timeout() const;
    
private:
    char* host_;
    int port_;
    int connect_retry_times_;
    timeval connect_timeout_;
    int connect_max_num_;
    int rw_retry_times_;
    timeval rw_timeout_;
};

}}

#endif
