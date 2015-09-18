#ifndef  DATA_INTERFACE
#define  DATA_INTERFACE
typedef struct Request{
    std::string url;
    int data_type;
    int action;
}Request;

typedef struct Response{
    int status;
}Response;
#endif

