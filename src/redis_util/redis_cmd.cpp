#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include "redis_cmd.hpp"
using namespace std;
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
    //printf("zrem count  %ld\n", r->integer);
    if(r != NULL)freeReplyObject(r);
    
}
Redis_Response*  zget_by_kv(redisContext* c, std::string key, std::string value){
    redisReply* r = (redisReply*)redisCommand(c, "ZRANGE %s  0 -1", key.c_str());
    Redis_Response* redis_response = new Redis_Response();
    if(r->elements==0){
        redis_response->err = (REDIS_ERROR)_REDIS_KEY_NOT_EXIST;
        redis_response->data_context = "";

    }   
    else{
        for (size_t i = 0; i < r->elements; i++) {
        redisReply* childReply = r->element[i];
        if (childReply->type == REDIS_REPLY_STRING){
             std::string value_str = childReply->str;
             unsigned int found = value_str.find(PATH_PREFIX);
             size_t path_len = 0;
             if(found == std::string::npos){
                 redis_response->err  = (REDIS_ERROR)_REDIS_VALUE_NOT_EXIST;
                 redis_response->data_context = ""; 
             }   
             unsigned int found2 = value_str.find(", ");
             if(found2 == std::string::npos)
                 path_len = value_str.length() -  PATH_PREFIX_LEN -2; 
             else
                 path_len = found2 -  PATH_PREFIX_LEN -2 ;
             std::string path = value_str.substr(found+8,path_len);
             std::cout<<"the path is "<<path<<std::endl;
             if(path =="/forum.php?mod=forumdisplay&fid=12\"}"){
                 redis_response->data_context = value_str;
                 redis_response->err = (REDIS_ERROR)_REDIS_OK;
             }   
             redis_response->data_context = "KEY: "+ key +"\t"+"VALUE: "+value_str + "\n";
        }   
    }   
   }
    return redis_response;
}

/*int main(int argc, char **argv){
    struct timeval timeout = {2, 0}; 
    redisContext* context = connect("127.0.0.1", 6399, timeout);
    zrem_by_key_score(context, "page_rank", "8");
    if(context != NULL)
        redisFree(context);
    return 0;
}*/
