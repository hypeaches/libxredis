#include <iostream>
#include <x/redis/connection.h>
#include <x/redis/errorinfo.h>

int main()
{
    x::redis::connection conn;
    conn.set_host("127.0.0.1", 16378, 1500);
    x::redis::errorinfo err;
    if (!conn.connect(&err))
    {
        std::cout<<err.message<<std::endl;
    }
    return 0;
}
