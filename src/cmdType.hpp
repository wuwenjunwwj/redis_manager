#ifndef __CMDTYPE__
#define __CMDTYPE__
#include <string>
#include <iostream>
//#include "data_interface.hpp"
#include "urlCmd.hpp"
using namespace std;

//redis data-type
enum DataType{
    t_string = 0, 
    t_hash,
    t_list,
    t_set = 3,
    t_zet
};

enum Action{
    look = 0,
    insert,
    rem,
    batch_look,
    batch_insert,
    batch_rem
    
};

enum Key{
    url = 0,
    site 
};

typedef struct Request{
    std::string host;
    int port;
    std::string data_context;
    Key key;
    DataType  data_type;
    Action action;
//std::string func_key;
}Request;

enum ResponseError{
    REDIS_OK = 0,
    REDIS_CONNECT_ERROR = 1,
    REDIS_KEY_NOT_EXIST = 2,
    REDIS_VALUE_NOT_EXIST = 3,
    BAD_REQUEST_DATA
};

typedef struct Response{
    ResponseError err; //todo change
    std::string data_context;
}Response;

typedef void (*commandProc)(Request& request, Response& response);

typedef struct Command{
    std::string cmdKey;
    commandProc proc;
    Command(std::string _cmdKey, commandProc _proc){
        cmdKey = _cmdKey;
        proc = _proc;
    }

} Command;

static Command CommandTable[]={
    //key data_type action
    {"010", zgetUrlInfoCmd}
};
#endif
