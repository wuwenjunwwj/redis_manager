#ifndef __REDIS_CMD__
#define __REDIS_CMD__
#include <string>
#include "redis_client.hpp"
enum REDIS_ERROR{
    _REDIS_OK = 0 ,
    _REDIS_CONNECT_ERROR = 1,
    _REDIS_KEY_NOT_EXIST = 2,
    _REDIS_VALUE_NOT_EXIST = 3
};

typedef struct Redis_Response{
    REDIS_ERROR err;
    std::string data_context;
}Redis_Response;

#endif
