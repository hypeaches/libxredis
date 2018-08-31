#include <iostream>
#include <x/redis/connection.h>

int main()
{
    x::redis::connection conn;
    conn.set_host("127.0.0.1", 16378, 1500);
    x::redis::error err = conn.connect();
    if (err.message)
    {
        std::cout<<err.message<<std::endl;
    }
    return 0;
}
