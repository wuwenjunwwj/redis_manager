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


typedef void (*commandProc)(Request& );

typedef struct Command{
    std::string cmdKey;
    commandProc proc;
    //Key key;
    //DataType type; 
    //Action action;
    Command(std::string _cmdKey, commandProc _proc){
        cmdKey = _cmdKey;
        proc = _proc;
        //key = (Key)_key;
        //type = (DataType)_type;
        //action=(Action)_action;
    }

} Command;

static Command CommandTable[]={
    //key data_type action
    {"010", zgetUrlInfoCmd}
    /*{"sgetUrlInfo","getUrlInfoCmd",0,3,0},
    
    {"zsetUrlInfo","setUrlInfoCmd",0,4,1},
    {"ssetUrlInfo","setUrlInfoCmd",0,3,1},
    
    {"zdelUrlInfo","setUrlInfoCmd",0,4,2},
    {"sdelUrlInfo","setUrlInfoCmd",0,3,2},
    
    {"zgetSiteInfo","getSiteInfoCmd",1,4,0},
    {"sgetSiteInfo","getSiteInfoCmd",1,3,0},
    
    {"zsetSiteInfo","setSiteInfoCmd",1,4,1},
    {"sgetSiteInfo","getSiteInfoCmd",1,3,1},
    
    {"zdelSiteInfo","delSiteInfoCmd",1,4,2},
    {"sgetSiteInfo","getSiteInfoCmd",1,3,2}*/
};
#endif
