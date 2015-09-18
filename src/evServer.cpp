#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/uio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <locale.h>
#include "evServer.hpp"
using namespace std;
void EvServer::daemonize(void){
    int fd;
    if (fork() != 0) exit(0); 
    setsid(); 
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
}
//todo
struct event_base* base;   
CmdProcessor *cmd_processor=  new CmdProcessor();
//cmd_processor ->loadCmdTable();

void onRead(int iCliFd, short iEvent, void *arg) 
{ 
    int iLen; 
    char buf[1500]; 
   
    iLen = recv(iCliFd, buf, 1500, 0); 
   
    if (iLen <= 0) { 
        cout << "Client Close" << endl; 
   
        struct event *pEvRead = (struct event*)arg; 
        event_del(pEvRead); 
        delete pEvRead; 
   
        close(iCliFd); 
        return; 
    }   
   
    buf[iLen] = 0;  
    cmd_processor -> processInputBuffer(buf);
    cout << "Client Info:" << buf << endl; 

} 
   
void onAccept(int iSvrFd, short iEvent, void *arg) 
{ 
    int iCliFd; 
    cout<<"onAccept"<<endl;
    struct sockaddr_in sCliAddr; 
   
    socklen_t iSinSize = sizeof(sCliAddr); 
    iCliFd = accept(iSvrFd, (struct sockaddr*)&sCliAddr, &iSinSize); 
   
    struct event *pEvRead = new event; 
    event_set(pEvRead, iCliFd, EV_READ|EV_PERSIST, onRead, pEvRead);
    event_base_set(base, pEvRead);
    event_add(pEvRead, NULL);
}
void EvServer::initServer(){
    int iSvrFd;   
    struct sockaddr_in sSvrAddr; 
                     
    memset(&sSvrAddr, 0, sizeof(sSvrAddr));   
    sSvrAddr.sin_family = AF_INET;   
    sSvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");    
    sSvrAddr.sin_port = htons(8888);        
                                   
    iSvrFd = socket(AF_INET, SOCK_STREAM, 0);   
    bind(iSvrFd, (struct sockaddr*)&sSvrAddr, sizeof(sSvrAddr));   
    listen(iSvrFd, 10); 
    cmd_processor->loadCmdTable();

    base = event_base_new(); 
    struct event evListen;
    event_set(&evListen, iSvrFd, EV_READ|EV_PERSIST, onAccept, NULL);
    event_base_set(base, &evListen);
    event_add(&evListen, NULL);
    cout<<"in initserver"<<endl;
    event_base_dispatch(base);
    cout<<"after initserver"<<endl;

    //init process;
    //cmd_processor = new CmdProcessor();
}
void EvServer::serve(){
    cout<<"in serve"<<endl;
    //event_base_dispatch(base);
}
void EvServer::exit(int){
}
