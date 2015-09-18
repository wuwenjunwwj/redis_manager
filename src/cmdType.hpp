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

typedef void (*commandProc)(Request& request);

typedef struct Command{
    std::string cmdName;
    commandProc proc;
    Key key;
    DataType type; 
    Action action;
    Command(std::string _cmdName, commandProc _proc, int _key, int _type, int _action){
        cmdName = _cmdName;
        proc = _proc;
        key = (Key)_key;
        type = (DataType)_type;
        action=(Action)_action;
    }

} Command;

static Command CommandTable[]={
    {"zgetUrlInfo", zgetUrlInfoCmd, 0,4,0},
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
