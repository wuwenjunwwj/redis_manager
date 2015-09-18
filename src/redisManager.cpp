#include <stdio.h> 
#include <string.h> 
#include <iostream> 
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>     
#include <netdb.h> 
   
#include <event.h> 
#include "evServer.hpp"
using namespace std; 
   
   
int main(){
    EvServer* _server = new EvServer();
    _server->initServer();
    _server->serve();
    return 0; 
}
