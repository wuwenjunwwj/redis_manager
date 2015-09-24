#include "cmdProcessor.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;
void CmdProcessor::loadCmdTable(){
     int command_nums = sizeof(CommandTable)/sizeof(struct Command);
     for(int i=0; i<command_nums; i++){
         m_processMap[CommandTable[i].cmdKey] = CommandTable[i].proc;

     }
}
// make real call
void CmdProcessor::make_call(std::string func_key, Request& request, Response& response){
    std::cout<<"in really make_call"<<std::endl;
    m_processMap[func_key](request, response);
}

std::vector<std::string> split(std::string s, std::string delimiter){
    vector<std::string> str_vec;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        str_vec.push_back(token);
        s.erase(0, pos + delimiter.length());
    }   
    str_vec.push_back(s);
    return str_vec;

}

std::string  CmdProcessor::decode(const char* buf, Request& request){
    //const char* json1 = " { \"host\" : \"127.0.0.1\", \"port\" : 6379 , \"url\" : \"http://007hw.com/forum.php?mod=forumdisplay&fid=24\", \"action\": 0, \"type\":1 }";
    jsonRequestParser* _parser = new jsonRequestParser();
    //_parser->parse(json1, request);
    _parser->parse(buf, request);
    stringstream ss;
    ss << request.key<<request.data_type<<request.action;
    std::string func_key = ss.str();
    return func_key;

}
const char*  CmdProcessor::processInputBuffer(const char* buf){
    cout<<"processMessage"<<buf<<std::endl;
    std::string buf_str = buf;
    Request request;
    std::string func_key = decode(buf,request);
    std::cout<<"func_key"<< func_key<<std::endl;
    Response response;
    make_call(func_key, request, response);
    //const char* response_str = response.data_context;
    return response.data_context.c_str();
}
/*int main(){
    CmdProcessor* a = new CmdProcessor();
    a-> loadCmdTable();
}*/
