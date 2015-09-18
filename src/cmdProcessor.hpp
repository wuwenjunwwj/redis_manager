#include <string>
#include <map>
#include "cmdType.hpp"
#include "data_interface.hpp"
class CmdProcessor{
public:
    void processInputBuffer(const char* buf);
    void processCommand();
    void loadCmdTable();
    void make_call(Request& request);
    void decode(const char* buf, Request& request);
private:
    //void registor_cmdProcessor(std::string cmd_key, commandProc proc);
    std::map<std::string, commandProc> m_processMap; 

};
