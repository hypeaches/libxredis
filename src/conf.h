#ifndef LIBXREDIS_CONF_H
#define LIBXREDIS_CONF_H

#include <sys/time.h>
#include <string>

namespace x{namespace redis{

class conf
{
public:
    conf();

public:
    const char* host() const {return host_.c_str();}
    int port() const {return port_;}
    void set_host(const char* host, int port);
    /// 获取连接重试次数
    int conn_retry_times() const {return conn_retry_times;}
    /// 设置连接重试次数
    void set_conn_retry_times(int retry_times);
    /// 获取连接超时时间，单位：毫秒
    timeval conn_timeout() const {return conn_timeout_;}
    /// 设置连接超时时间，单位：毫秒
    void set_conn_timeout(int timeout);
    /// 获取读写重试次数
    int rw_retry_times() const {return rw_retry_times;}
    /// 设置读写重试次数
    void set_rw_retry_times(int retry_times);
    /// 获取读写超时时间，单位：毫秒
    int rw_timeout() const {return rw_timeout_;}
    /// 设置读写超时时间，单位：毫秒
    void set_rw_timeout(int timeout);

private:
    std::string host_;
    int port_;
    int conn_retry_times_;
    timeval conn_timeout_;
    int rw_retry_times_;
    timeval rw_timeout_;
};

}}

#endif
