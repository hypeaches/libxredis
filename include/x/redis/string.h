#ifndef LIBXREDIS_STRING_H
#define LIBXREDIS_STRING_H

namespace x{namespace redis{

class string
{
public:
    string();
    string(const char* str);
    string(const char* str, int len);
    string(string&& other);
    string(const string& other);
    string& operator=(string&& other);
    string& operator=(const string& other);
};

}}

#endif
