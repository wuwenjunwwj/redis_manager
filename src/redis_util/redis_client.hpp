#ifndef _REDIS_CLIENT_
#define _REDIS_CLIENT_

#include "hiredis/hiredis.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

//typedef struct Reply:redisReply{
struct Reply:redisReply{
    std::vector<std::string> str_vec;
    size_t j;
    Reply(redisReply* r){
        std::cout<<"wwj debug in Reply construct"<<std::endl;
        switch(r->type) {
        case REDIS_REPLY_INTEGER:
            break; 
        case REDIS_REPLY_ARRAY:
            std::cout<<"wwj debug in Reply construct REDIS_REPLY_ARRAY1: "<<std::endl;
            if (r->element != NULL) {
            std::cout<<"wwj debug in Reply construct REDIS_REPLY_ARRAY"<<std::endl;
                for (j = 0; j < r->elements; j++){
                    if (r->element[j] != NULL && r->element[j]->type == REDIS_REPLY_STRING)
                        str_vec.push_back(r->element[j]->str);
                }
            }
            break;
        case REDIS_REPLY_ERROR:
        case REDIS_REPLY_STATUS:
        case REDIS_REPLY_STRING:
            break;
        }
    //todo:need free
    }
    //todo  put child element to vector
};
typedef struct Reply Reply;

class RedisException : public std::exception{
std::string _what;
public:
    RedisException(const char* cstr): _what(cstr) { }
    RedisException(const std::string& what): _what(what) { }
    virtual ~RedisException() throw() { }
    virtual const char* what() const throw(){
        return _what.c_str();
        }
    };

class Redis{
public:
    //Redis(std::string host="127.0.0.1", std::string db_idx = "0", int port=6379);
    Redis(std::string host, std::string db_idx, int port);
    int connect();
    Reply* set(std::string key, std::string value);
    Reply* smembers(std::string key);
    Reply* zrange(std::string key, int min, int max);
    Reply* zrangbyscore(std::string key, std::string min, std::string max);
    Reply* zrem(std::string key, std::string member);
    Reply* zadd(std::string key, std::string score, std::string member);
    redisContext * _context;
    std::string host;
    std::string db_idx;
    int port;
};
#endif
