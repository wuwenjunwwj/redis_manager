#include "urlCmd.hpp"
#include <string>
#include<vector>
#include <iostream>
#include <cstdlib>
//#include "redis_util/redis_cmd.cpp"
#include "redis_util/gen_redis_kv.cpp"
using namespace std;
//get 1 url info

void zgetUrlInfoCmd(Request& request, Response& response){
    std::string key = gen_url_key(request.data_context.c_str());
    if(key == ""){
        response.err = BAD_REQUEST_DATA;
        response.data_context = "bad url\n";
        return;
    }
    std::string value = gen_url_value(request.data_context.c_str());
    if(value ==""){
        response.err = BAD_REQUEST_DATA;
        response.data_context = "bad url\n";
        return;

    }
    redis_result result = zget_by_kv(request.host, request.port, key, value);
    response.data_context = result.desc;

}
void zsetUrlInfoCmd(Request& request, Response& response){
    /*std::cout<<"Call zsetUrlINfoCmd Success"<<endl;
    struct timeval timeout = {2, 0}; 
    struct parsed_url* _parsed_url = parse_url(request.data_context.c_str());
    if(_parsed_url ==NULL){
        //response.err = (ResponseError)BAD_REQUEST_DATA;
        response.data_context = ""; 
        return;
    }   
    std::string host = _parsed_url -> host;
    std::string host_key = SITE_PREFIX +host +SITE_SUFFIX;
    redisContext* context = connect(request.host, request.port, timeout);
    if(context ==NULL){
        //response.err = REDIS_CONNECT_ERROR;
        return;
    }*/
    //todo sadd   

}
void sgelUrlInfo(Request& request){
    std::cout<<"call sgetUrlINfoCmd "<<endl;
}
//get batch url info
void sgetBatchUrlInfo(std::vector<std::string> urls){
}

void zgetBatchUrlInfo(std::vector<std::string> urls){
}

//set 1 url info
void ssetUrlInfo(std::string url){
}
void zsetUrlInfo(std::string url, std::string score){
}
//batch set url info
void ssetBatchUrlInfo(std::vector<std::string> urls){
}
void zsetBatchUrlInfo(std::vector<std::string> urls, std::vector<std::string> scores){
}


// del 1 url info
void zdelUrlInfo(std::string url){
}
void sdelUrlInfo(std::string url){
}
// batch del url info
void zdelBatchUrlInfo(std::string url){
}
void sdelBatchUrlInfo(std::string url){
}
