#include <iostream>
#include <x/redis/connection.h>
#include <x/redis/command.h>
#include <x/redis/errorinfo.h>

int main()
{
    x::redis::connection conn;
    conn.set_host("127.0.0.1", 6379, 1500);
    int ec = conn.connect();
    if (ec)
    {
        std::cout<<x::redis::errorinfo::message(ec)<<std::endl;
        return 1;
    }

    x::redis::command cmd(&conn);
    
    int ret = 0;
    //ret = cmd.get("key1");
    //cmd.get("key1");
    cmd.exec_integer(NULL, "mget", "k1", "k2", "k3");
    std::cout<<"command ret: "<<ret<<std::endl;
    return 0;
}
