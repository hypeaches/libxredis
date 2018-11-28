#ifndef LIBXREDIS_REDISLOG_H
#define LIBXREDIS_REDISLOG_H

#ifndef XREDISLOG_FATAL
#define XREDISLOG_FATAL(ip, port, cmd, errmsg) printf("redis msg:%s|%d|%s|%s\n", ip, port, cmd, errmsg)
#endif

#ifndef XREDISLOG_WARNING
#define XREDISLOG_WARNING(ip, port, cmd, errmsg) printf("redis msg:%s|%d|%s|%s\n", ip, port, cmd, errmsg)
#endif

#ifndef XREDISLOG_INFO
#define XREDISLOG_INFO(ip, port, cmd, errmsg) printf("redis msg:%s|%d|%s|%s\n", ip, port, cmd, errmsg)
#endif

#ifndef XREDISLOG_DEBUG
#define XREDISLOG_DEBUG(ip, port, cmd, errmsg) printf("redis msg:%s|%d|%s|%s\n", ip, port, cmd, errmsg)
#endif

#endif
