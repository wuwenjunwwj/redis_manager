#include <iostream>
#include <string>
#include "parser/url_parser.c"
#define PATH_PREFIX  "\"path\": "
#define PATH_PREFIX_LEN 8
#define SITE_PREFIX "d:s:"
#define SITE_SUFFIX ":s"

std::string gen_url_key(const char* url){
    struct parsed_url* _parsed_url = parse_url(url);
    if(_parsed_url ==NULL){
        //response.err = (ResponseError)BAD_REQUEST_DATA;
        return "";
    }
    std::string _host = _parsed_url -> host ;
    return SITE_PREFIX + _host +SITE_SUFFIX;
}

std::string gen_url_value(const char* url){
    struct parsed_url* _parsed_url = parse_url(url);
    if(_parsed_url ==NULL){
        return "";
    }
    std::string _path = (_parsed_url ->path)?(_parsed_url ->path):("");
    _path = (_path!="")?("/"+_path):("");
    std::string _query = (_parsed_url ->query)?(_parsed_url ->query):("");
    _query = (_query!="")?("?"+_query):("");
    std::string _fragment = (_parsed_url ->fragment)?(_parsed_url ->fragment):("");
    _fragment = (_fragment!="")?("#"+_fragment):("");
    return _path +  _query + _fragment;
}

//todo: add spider info
