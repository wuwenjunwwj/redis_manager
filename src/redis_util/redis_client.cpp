#include "redis_client.hpp"
using namespace std;
Reply* end_command(redisReply* reply){
    if (!reply){
        cout<<"error"<<endl;
        throw runtime_error( "Redis error" );
    }   
    else{
    }
    Reply* r = new Reply(reply);
    std::cout<<"wwj debug in end_command"<<std::endl;
    std::cout<<"wwj debug in end_command reply->type: "<<reply->type<<std::endl;
    return r;
}

Redis::Redis(std::string host="127.0.0.1", std::string db_idx = "0", int port=6379){
    this -> host = host;
    this -> port = port;
    this -> db_idx = db_idx;
}

int Redis::connect(){
    struct timeval timeout = {2, 0}; 
    this -> _context = (redisContext*)redisConnectWithTimeout((this->host).c_str(), this->port, timeout);
    if ((NULL == this -> _context)|| (this -> _context->err)){
        if (this -> _context){
            std::cout<<"connect error: "<< _context->errstr << std::endl;
            return -1;
        }
        else{
            redisFree(this->_context);
            std::cout<<"connect error: "<< std::endl;
            return -1;
        }
    }
    return 0;

}

Reply* Redis::set(std::string key, std::string value){
    redisReply* r;
    r = (redisReply*)redisCommand( this -> _context, "SET %s %s", key.c_str(), value.c_str());
    return end_command(r);
}

Reply* Redis::smembers(std::string key){
    redisReply* r;
    r = (redisReply*)redisCommand( this -> _context, "SMEMBERS %s", key.c_str());
    return end_command(r);
}

Reply* Redis::zrange(std::string key, int min, int  max){
    redisReply* r;
    r = (redisReply*)redisCommand( this -> _context, "ZRANGE  %s  0 -1", key.c_str());
    std::cout<<"the key is-----------------"<<key<<std::endl;
    return end_command(r);
}

Reply* Redis::zrangbyscore(std::string key, std::string min, std::string max){
    redisReply* r;
    r = (redisReply*)redisCommand( this -> _context, "SET %s ", key.c_str());
    return end_command(r);
}

Reply* Redis::zrem(std::string key, std::string member){
    redisReply* r;
    r = (redisReply*)redisCommand( this -> _context, "SET %s ", key.c_str());
    return end_command(r);
}

Reply* Redis::zadd(std::string key, std::string score, std::string member){
    redisReply* r;
    r = (redisReply*)redisCommand( this -> _context, "SET %s ", key.c_str());
    return end_command(r);
}
