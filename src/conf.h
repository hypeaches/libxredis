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
    void set_host(const char* host, int port);
    /// 设置连接重试次数
    void set_conn_retry_time(int retry_time);
    /// 设置连接超时时间，单位：毫秒
    void set_conn_timeout(int timeout);
    /// 设置读写重试次数
    void set_rw_retry_time(int retry_time);
    /// 设置读写超时时间，单位：毫秒
    void set_rw_timeout(int timeout);

private:
    std::string host_;
    int port_;
    int conn_retry_time_;
    timeval conn_timeout_;
    int rw_retry_time_;
    timeval rw_timeout_;
};

}}

#endif
