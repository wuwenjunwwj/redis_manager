#include<iostream>
#include "thirdparty/rapidjson/document.h"
#include "thirdparty/rapidjson/reader.h"
#include "thirdparty/rapidjson/rapidjson.h"
#include "thirdparty/rapidjson/stringbuffer.h"   
#include "thirdparty/rapidjson/writer.h"   
#include "thirdparty/rapidjson/prettywriter.h" 
#include "thirdparty/rapidjson/filereadstream.h" 
#include "thirdparty/rapidjson/filewritestream.h" 
class jsonRequestParser{
public:
    void parse(const char* json1, Request& request){
        //const char json1[] = " { \"host\" : \"127.0.0.1\", \"port\" : 6379 , \"url\" : \"http://007hw.com/forum.php?mod=forumdisplay&fid=24\", \"action\": 0, \"type\":1 }";
        rapidjson::Document document;
        document.Parse<rapidjson::kParseDefaultFlags>(json1);
        if(!document.IsObject()){
            std::cout<<"bad json str"<<std::endl;
        }
        if(document.HasMember("host") && document["host"].IsString()){
            request.host = document["host"].GetString();
            std::cout<<"host:"<< request.host<<std::endl;
            
        }
        if(document.HasMember("port") && document["port"].IsInt()){
            request.port = document["port"].GetInt();
            std::cout<<"port: "<<request.port<<std::endl;
        }

        if(document.HasMember("url") && document["url"].IsString()){
            request.key= url;
            request.data_context = document["url"].GetString();
            std::cout<<"url: "<<request.data_context<<std::endl;
        }


        if(document.HasMember("site") && document["site"].IsString()){
            request.key= site;
            request.data_context = document["site"].GetString();;
            std::cout<<"site: "<<request.data_context<<std::endl;
        }
        
        if(document.HasMember("action") && document["action"].IsInt()){
            request.action = (Action)document["action"].GetInt();
            std::cout<<"action: "<<request.action<<std::endl;
        }

        if(document.HasMember("type") && document["type"].IsInt()){
            request.data_type = (DataType)document["type"].GetInt();
            std::cout<<"port: "<<request.data_type<<std::endl;
        }

    }
};
