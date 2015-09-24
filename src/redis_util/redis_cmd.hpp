#ifndef __REDIS_CMD_H_
#define __REDIS_CMD_H_

#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include "cmdType.hpp"
#include "redis_client.hpp"
#include "redis_str_parser.cpp"
using namespace std;
#define REDIS_GET_OK 0
#define CONNECT_ERROR 1
#define KEY_NOT_EXIST 2
#define VALUE_NOT_EXIST 3

struct redis_result{
    int err_code;
    std::string desc;
};
redisContext* connect(string host, int port, timeval timeout){
    redisContext *pRedisContext = (redisContext*)redisConnectWithTimeout(host.c_str(), port, timeout);
    if ( (NULL == pRedisContext) || (pRedisContext->err) )
    {
        if (pRedisContext)
        {
            std::cout << "connect error:" << pRedisContext->errstr << std::endl;
        }
        else
        {
            std::cout << "connect error: can't allocate redis context." << std::endl;
        }
        return NULL ;
    }
    return pRedisContext;
}

redisReply* excute_ord_cmd(redisContext* pRedisContext, const char* cmd_str){
    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, cmd_str);
    if (!pRedisReply){
        cout<<"error"<<endl;
        throw runtime_error( "Redis error" );
    }
    else{
        cout<<"hihih"<<pRedisReply->integer<<endl;
        cout<<"hihih"<<pRedisReply->type<<endl;
        cout<<"hihih"<<pRedisReply->elements<<endl;
    }
    cout<<pRedisReply->str<< std::endl;
    return pRedisReply;
}

//batch set data
void mset_batch(redisContext *c, const vector<string> &vtKey, const vector<string> & vtVal ){
    if(vtKey.size() != vtVal.size()){   
        throw runtime_error( "Redis error" );
    }   

    string strCmd = "MSET";
    for(size_t i = 0; i < vtKey.size(); i++){   
        strCmd += " "+vtKey[i]+" "+vtVal[i];
    }   
    cout << "strCmd:" << strCmd << endl;

    void * r =  redisCommand(c, strCmd.c_str() );
    if ( !r )
        throw runtime_error( "Redis error" );
    freeReplyObject( r );
}

//remove the set data by key
void srem_by_key(redisContext *c, std::string key){
    redisReply* r;
    r = (redisReply*)redisCommand(c, "SMEMBERS %s", key.c_str());
    for (size_t i = 0; i < r->elements; i++) {
        redisReply* childReply = r->element[i];
        if (childReply->type == REDIS_REPLY_STRING){
            redisReply* r1 = (redisReply*)redisCommand(c, "SREM %s %s", key.c_str(), childReply->str);
            printf("srem %s  %s\n", key.c_str(),childReply->str);
            if(r1!=NULL)freeReplyObject(r1);

        }
    }
    if(r != NULL)freeReplyObject(r);
    
}

//remove the zset data by key
void zrem_by_key(redisContext *c, std::string key){
    redisReply* r;
    r = (redisReply*)redisCommand(c, "zrange %s 0 -1", key.c_str());
    for (size_t i = 0; i < r->elements; i++) {
        redisReply* childReply = r->element[i];
        if (childReply->type == REDIS_REPLY_STRING){
            redisReply* r1 = (redisReply*)redisCommand(c, "ZREM %s %s", key.c_str(), childReply->str);
            printf("zrem %s  %s\n", key.c_str(),childReply->str);
            if(r1!=NULL)freeReplyObject(r1);

        }
    }
    if(r != NULL)freeReplyObject(r);
    
}

//remove the zset by  key and score
void zrem_by_key_score(redisContext *c, std::string key, std::string score){
    redisReply* r;
    r = (redisReply*)redisCommand(c, "ZREMRANGEBYSCORE %s  %s %s", key.c_str(), score.c_str(), score.c_str());
    if(r != NULL)freeReplyObject(r);
    
}
//get data from zset by key && value
redis_result zget_by_kv(std::string host, int port, std::string key, std::string value){
    Redis* r = new Redis(host, "0", port);
    redis_result result;
    if(r -> connect()== -1){ 
        delete r;
        result.err_code = CONNECT_ERROR;
        result.desc = "redis connect error";
        return result;
    }
    std::string ret_str = "";
    Reply* reply = r -> zrange(key, 0, -1);
    if(reply!=NULL){
        for(size_t i=0; i<(reply->str_vec).size(); i++){
            std::string member = reply->str_vec[i];
            std::map<std::string ,std::string> str_map = split(member,",",":");
            std::cout<<"value: "<<value<<std::endl;
            if(str_map.find("path")->second == value){
                std::cout<<"MATCHED"<<std::endl;
                result.desc = member+"\n";
                result.err_code = REDIS_GET_OK;
                break;
            }
        }
        if(result.desc == ""){
            result.err_code = VALUE_NOT_EXIST;
            result.desc = "redis value not exist";
        }
    }
    else{
        result.err_code = KEY_NOT_EXIST;
        result.desc = "redis key not exist";
    }
    delete r;
    return result;
}

//add data to zset according key&&value
std::string  zset_by_kv(std::string key, std::string value, std::string score){
    Redis* r = new Redis("127.0.0.1", "0", 6379);
    if(r -> connect()== -1)
        return NULL;
    Reply* reply = r -> zrange(key, 0, -1);
    if(reply!=NULL){
        for(size_t i=0; i<(reply->str_vec).size(); i++){
            if(reply!=NULL)std::cout<<"the members is: "<<reply->str_vec[i]<<std::endl;
        }
    }
    return NULL;
}

// remove data by key&&value
//Redis_Response* zrem_by_kv(redisContext* c, std::string key, std::string value){
//}
/*int main(int argc, char **argv){
    struct timeval timeout = {2, 0}; 
    redisContext* context = connect("127.0.0.1", 6399, timeout);
    zrem_by_key_score(context, "page_rank", "8");
    if(context != NULL)
        redisFree(context);
    return 0;
}*/

#endif
