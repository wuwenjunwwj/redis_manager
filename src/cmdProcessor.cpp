#include "cmdProcessor.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
void CmdProcessor::loadCmdTable(){
     int command_nums = sizeof(CommandTable)/sizeof(struct Command);
     for(int i=0; i<command_nums; i++){
         stringstream ss;
         ss << CommandTable[i].type<<CommandTable[i].action<<CommandTable[i].key;
         std::string key_str = ss.str();
         m_processMap[key_str] = CommandTable[i].proc;
         std::cout<<"insert key="<<key_str<<" value="<<CommandTable[i].proc<<std::endl;

     }
}
// make real call
void CmdProcessor::make_call(Request& request){
    //todo:400\n
    //(m_processMap["400"])("hihi");
}
void CmdProcessor::decode(const char* buf, Request& request){

}
void CmdProcessor::processInputBuffer(const char* buf){
    cout<<"hello, processMessage"<<buf<<std::endl;
    std::string buf_str = buf;
    Request request;
    decode(buf,request);
    //todo:parse buf str
    //Example of request
    //host="127.0.0.1&&port=6379&&"url="http://www.baidu.com"&&action="look"&&type="zset"

    make_call(request);
    //(m_processMap["400"])("hihi");
}
/*int main(){
    CmdProcessor* a = new CmdProcessor();
    a-> loadCmdTable();
}*/
