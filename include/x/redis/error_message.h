#ifndef LIBXREDIS_ERRORMESSAGE_H
#define LIBXREDIS_ERRORMESSAGE_H

namespace x{namespace redis{

class error_message
{
public:
    error_message();
    virtual ~error_message();
    const char* errmsg() const {return errmsg_;}

protected:
    void reset_error();

protected:
    char* errmsg_;
    int errmsg_len_;
    int errno_;
};

}}

#endif
