#ifndef __EVER_SVR_H_
#define __EVER_SVR_H_

#include <stdio.h> 
#include <string.h> 
#include <iostream> 
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>    
#include <netdb.h> 
#include <event.h>
#include "cmdProcessor.hpp"
#define MAX_BUF_LEN 1500
class EvServer{
public:
    void serve();
    void initServer();
    void exit(int );
    int isDaemon;
    void daemonize(void);
private:
    int m_stop;
    //CmdProcessor *cmd_processor;

};
#endif
