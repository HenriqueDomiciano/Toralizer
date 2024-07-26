#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dlfcn.h>

#define PROXY "127.0.0.1"
#define PROXYPORT 9050


#define USERNAME "henrike"
#define REQSIZE sizeof(struct proxy_request)
#define RESPSIZE sizeof(struct proxy_response)


typedef unsigned char int8 ; 
typedef unsigned short int int16;
typedef unsigned int int32; 


struct  proxy_request
{
    int8 vn; 
    int8 cd; 
    int16 dstport; 
    int32 dstip; 
    unsigned char userid[8];
};

struct proxy_response {
    int8 vn; 
    int8 cd; 
    int16 _; 
    int32 __; 
}; 

typedef struct proxy_request Req ; 

typedef struct proxy_response Resp; 


Req* request(struct sockaddr_in*);

int (*p)(int , const struct sockaddr*,socklen_t);
