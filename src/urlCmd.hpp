#ifndef _URL_CMD
#define _URL_CMD
#include <string>
#include<vector>
#include <iostream>
#include "redis_util/redis_cmd.hpp"

struct Request;
struct Response;
void zgetUrlInfoCmd(Request& request, Response& response);

void sgetUrlInfo(Request& request, Response& response);
//get batch url info
void sgetBatchUrlInfo(std::vector<std::string> urls);

void zgetBatchUrlInfo(std::vector<std::string> urls);

//set 1 url info
void ssetUrlInfo(std::string url);
void zsetUrlInfo(std::string url, std::string score);
//batch set url info
void ssetBatchUrlInfo(std::vector<std::string> urls);
void zsetBatchUrlInfo(std::vector<std::string> urls, std::vector<std::string> scores);


// del 1 url info
void zdelUrlInfo(std::string url);
void sdelUrlInfo(std::string url);
// batch del url info
void zdelBatchUrlInfo(std::string url);
void sdelBatchUrlInfo(std::string url);

#endif
