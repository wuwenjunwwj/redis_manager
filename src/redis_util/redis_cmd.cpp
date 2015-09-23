#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include "redis_cmd.hpp"
#include "redis_client.hpp"
#include "redis_str_parser.cpp"
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
    if(r != NULL)freeReplyObject(r);
    
}
//get data from zset by key && value
Redis_Response*  zget_by_kv(std::string key, std::string value){
    Redis_Response* redis_response = new Redis_Response();
    Redis* r = new Redis("127.0.0.1", "0", 6379);
    if(r -> connect()== -1) 
        return NULL;
    Reply* reply = r -> zrange(key, 0, -1);
    if(reply!=NULL){
        value = "/forum.php?mod=forumdisplay&fid=102";
        for(size_t i=0; i<(reply->str_vec).size(); i++){
            std::string member = reply->str_vec[i];
            std::map<std::string ,std::string> str_map = split(member,",",":");
            std::cout<<"value: "<<value<<std::endl;
            if(str_map.find("path")->second == value){
                std::cout<<"MATCHED"<<std::endl;
                redis_response->data_context = "KEY: "+ key +"\t"+"VALUE: "+member + "\n";
                break;
            }
        }
    }   
    delete r;
    return redis_response;
}

//add data to zset according key&&value
Redis_Response*  zset_by_kv(std::string key, std::string value, std::string score){
    Redis_Response* redis_response = new Redis_Response();
    Redis* r = new Redis("127.0.0.1", "0", 6379);
    if(r -> connect()== -1)
        return NULL;
    Reply* reply = r -> zrange(key, 0, -1);
    if(reply!=NULL){
        for(size_t i=0; i<(reply->str_vec).size(); i++){
            if(reply!=NULL)std::cout<<"the members is: "<<reply->str_vec[i]<<std::endl;
        }
    }
    return redis_response;
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
