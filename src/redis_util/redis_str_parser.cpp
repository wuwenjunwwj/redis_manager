#include <iostream>
#include <boost/regex.hpp>
#include <map>
//{"path": "/", "refer": "http://www.chinasuv.cn/plus/list.php?tid=41"}
//
std::string ltrim(const std::string& str) { 
    return str.substr(str.find_first_not_of(" \n\r\t\"{")); 
} 

std::string rtrim(const std::string& str) { 
    return str.substr(0,str.find_last_not_of(" \n\r\t\"}")+1); 
} 

std::string trim(const std::string& str){ 
    return ltrim(rtrim(str)); 
}

std::pair<std::string , std::string> split_kv(std::string s, std::string delimiter){
    std::pair<std::string, std::string> kv_pair;
    std::string key_str, value_str;
    size_t pos;
    if((pos = s.find(delimiter)) != std::string::npos){
        key_str = s.substr(0,pos);
        std::cout<<trim(key_str)<<std::endl;
    }
    value_str = s.erase(0, pos + delimiter.length());
    std::cout<<trim(value_str)<<std::endl;
    kv_pair = std::make_pair(trim(key_str), trim(value_str));
    return kv_pair;
}

std::map<std::string, std::string> split(std::string s, std::string str_delimiter, std::string kv_delimiter){
    std::map<std::string, std::string> str_map;
    size_t pos = 0;
    std::string token;
    std::string key_str;
    std::string token2;
    while ((pos = s.find(str_delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        str_map.insert(split_kv(token, kv_delimiter));
        s.erase(0, pos + str_delimiter.length());
        str_map.insert(split_kv(s, kv_delimiter));
    }
    str_map.insert(split_kv(s, kv_delimiter));
    std::map<std::string,std::string>::iterator it;
    for (it=str_map.begin(); it!=str_map.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    return str_map;

}

/*int main(){
    //std::string value = "{\"path\": \"/\", \"refer\": \"http://www.chinasuv.cn/plus/list.php?tid=41\"}";
    std::string value = "{\"path\": \"/\"";
    split(value,",",":");
    std::cout<<"the str is "<< value<<std::endl;
}*/
