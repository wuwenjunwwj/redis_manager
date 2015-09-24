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
    if(m_processMap[func_key]){
        m_processMap[func_key](request, response);
    }
    else{
        //response.err = BAD_REQUEST_DATA;
        response.data_context = "bad command ";
    }
}


std::string  CmdProcessor::decode(const char* buf, Request& request){
    //const char* json1 = " { \"host\" : \"127.0.0.1\", \"port\" : 6379 , \"url\" : \"http://007hw.com/forum.php?mod=forumdisplay&fid=24\", \"action\": 0, \"type\":1 }";
    request.reset();
    jsonRequestParser* _parser = new jsonRequestParser();
    _parser->parse(buf, request);
    stringstream ss;
    std::cout<<"request.key"<<std::endl;

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
    return response.data_context.c_str();
}
