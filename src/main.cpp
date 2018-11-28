#include <iostream>
#define XREDISLOG(ip, port, cmd, errmsg) printf("redis msg:%s|%d|%s|%s\n", ip, port, cmd, errmsg)
#include <x/redis/conf.h>
#include <x/redis/connection_pool.h>
#include <x/redis/command.h>
//#include <x/redis/errorinfo.h>
#include <memory>
#include <functional>


timeval timesub(const timeval& tv1, const timeval& tv2);
void print(const char* str, const timeval& tv);

// 测试多个短命令执行
void test_xredis_1();
void test_xredis_11();
void test_hiredis_1();

int main()
{
	x::redis::conf c;
	x::redis::connection_pool* pool = x::redis::connection_pool::default_pool();
	pool->init(&c);
	x::redis::command::default_connection_pool = pool;
	x::redis::command cmd;

    std::cout<<"test libxredis and hiredis\n";
	cmd.build("set k1 v1").build("set k2 v2").build("set k3 v3");
	std::cout<<cmd.exec()<<std::endl;
    return 0;
}

void test_xredis_1();
void test_xredis_11();
void test_hiredis_1();

timeval timesub(const timeval& tv1, const timeval& tv2)
{
    timeval tv;
    tv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    tv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if (tv.tv_sec > 0 && tv.tv_usec < 0)
    {
        tv.tv_sec -= 1;
        tv.tv_usec += 1000000;
    }
    return tv;
}

void print(const char* str, const timeval& tv)
{
    std::cout<<std::setw(27)<<str<<":"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}
