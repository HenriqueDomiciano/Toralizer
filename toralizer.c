#include "toralizer.h"



int connect(int s2, const struct sockaddr *sock2, socklen_t addrlen){

    int s ;
    Req *req;
    Resp *resp;  
    int sucess; 
    char buff[RESPSIZE]; 
    char tmp[512]; 
    int (*p)(int , const struct sockaddr*,socklen_t);
    struct sockaddr_in sock; 

    p = dlsym(RTLD_NEXT,"connect");

    s = socket(AF_INET, SOCK_STREAM,0);

    if (s<0){
        perror("socket"); 
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);
    if (p(s,(struct sockaddr *)&sock,sizeof(sock)))
    {
        perror("connect"); 
        return -1 ;
    };

    printf("Connected to proxy\n"); 
    
    /*Creating an request*/

    req = request((struct sockaddr_in *)sock2); 
    write(s,req, REQSIZE);
    memset(buff,0,RESPSIZE); 

    if(read(s,buff,RESPSIZE)<0)
    {
        perror("read");
        free(req);
        close(s);
        printf("FAILED TO READ");

        return -1 ; 
    }
    resp = (Resp *)buff;

    sucess = (resp->cd == 90);


    if (!sucess){
        fprintf(stderr,"Unable to transverse the proxy"
        " error code %d\n",resp->cd);
        close(s); 
        free(req);
        return -1; 
    }
    dup2(s,s2);
    free(req);
    /*
    memset(tmp,0,sizeof(tmp)); 
    snprintf(tmp,511,
    "HEAD / HTTP/1.0\r\n" 
    "Host: www.networktechnology.org\r\n"
    "\r\n"); 

    write(s,tmp,strlen(tmp)); 

    memset(tmp,0,512); 
    read(s,tmp,511); 

    printf("RESPONSE:'%s'\n",tmp); 
    */
    return 0 ;
}

Req *request(struct sockaddr_in *sock2){
    Req *req ; 
    req = malloc(REQSIZE);
    req->dstip = sock2->sin_addr.s_addr;
    req->dstport = sock2->sin_port ;
    req->vn = 4; 
    req->cd = 1;
    strncpy(req->userid,USERNAME,8); 
    return req;
}


