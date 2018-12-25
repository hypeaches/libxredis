#ifndef LIBXREDIS_OPTIONS_H
#define LIBXREDIS_OPTIONS_H

#include <string>

namespace x{namespace redis{

struct options
{
options();

int port;
int retry_times;
int connect_timeout;
int read_write_timeout;
int pool_max_connections;
std::string host;
};

}}

#endif