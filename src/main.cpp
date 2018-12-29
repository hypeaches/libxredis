#include <iostream>
#include <iomanip>
#include <x/redis/options.h>
#include <x/redis/command.h>

timeval timesub(const timeval& tv1, const timeval& tv2);
void print(const char* str, const timeval& tv);

int main()
{
	x::redis::options opt;
    x::redis::command::init(&opt);
    x::redis::command::add_pool("127.0.0.1", 6379);
    x::redis::command cmd;
    cmd.exec("get key1");
    return 0;
}

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
