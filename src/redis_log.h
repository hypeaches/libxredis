#ifndef LIBXREDIS_REDISLOG_H
#define LIBXREDIS_REDISLOG_H

#ifndef XREDISLOG
#define XREDISLOG(ip, port, cmd, errmsg) printf("redis msg:%s|%d|%s|%s\n", ip, port, cmd, errmsg)
#endif

#endif
