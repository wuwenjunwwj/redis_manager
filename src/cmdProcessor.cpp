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
         //stringstream ss;
         //ss << CommandTable[i].type<<CommandTable[i].action<<CommandTable[i].key;
         //std::string key_str = ss.str();
         m_processMap[CommandTable[i].cmdKey] = CommandTable[i].proc;
        // std::cout<<"insert key="<<key_str<<" value="<<CommandTable[i].proc<<std::endl;

     }
}
// make real call
void CmdProcessor::make_call(std::string func_key, Request& request){
    std::cout<<"in really make_call"<<std::endl;
    //todo:400\n
    //(m_processMap["400"])("hihi");
    m_processMap[func_key](request);
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
//std::set<std::string> key_set;

std::string  CmdProcessor::decode(const char* buf, Request& request){
    std::string s = "host127.0.0.1&port=6379&url=\"http://www.baidu.com\"&action=0&type=1";
    std::string delimiter = "&";
    std::vector<std::string> str_vec = split(s, delimiter);
    for(size_t i=0; i<str_vec.size(); i++){
        std::string kv_delimiter = "=";
        std::cout<<str_vec[i]<<std::endl;
        std::vector<std::string> kv_vec = split(str_vec[i],  kv_delimiter);
        if(kv_vec.size() >=2){
            std::string key_str = kv_vec[0];
            std::string value_str = kv_vec[1];
            std::cout<<"the key is: "<<key_str <<" the value is: "<<value_str<<std::endl;
            if(key_str == "url"){
                request.key= url;
                request.data_context = value_str;
                std::cout<<"request.key"<<request.key<<std::endl;
            }
            else if(key_str == "site"){
                request.key = site;
                request.data_context = value_str;
            }
            else if(key_str == "action"){
                request.action = Action(atoi(value_str.c_str()));
                std::cout<<"request.action"<<request.action<<std::endl;
            }
            else if(key_str == "type")
                request.data_type = DataType(atoi(value_str.c_str()));
            else
                std::cout<<"just skip"<<std::endl;
        }
        else{
            cout<<"decode error,just skip the str"<<str_vec[i]<<std::endl;
        }

    }

        stringstream ss; 
        ss << request.key<<request.data_type<<request.action;
        std::string func_key = ss.str();
        std::cout<<"func_key" <<func_key<<std::endl;
    return func_key;

}
void CmdProcessor::processInputBuffer(const char* buf){
    cout<<"hello, processMessage"<<buf<<std::endl;
    std::string buf_str = buf;
    Request request;
    std::string func_key = decode(buf,request);
    std::cout<<"func_key"<< func_key<<std::endl;
    make_call(func_key, request);
}
/*int main(){
    CmdProcessor* a = new CmdProcessor();
    a-> loadCmdTable();
}*/
