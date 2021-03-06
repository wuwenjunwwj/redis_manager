#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

#include <string>
#include <map>
#include "cmdType.hpp"
#include "jsonReqeustParser.hpp"
class CmdProcessor{
public:
    const char* processInputBuffer(const char* buf);
    void processCommand();
    void loadCmdTable();
    void make_call(std::string func_key, Request& request, Response& response);
    std::string decode(const char* buf, Request& request);
private:
    std::map<std::string, commandProc> m_processMap; 

};

#endif
