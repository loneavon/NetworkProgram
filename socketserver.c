/*************************************************************************
	> File Name: socketserver.c
	> Author: Li Wen
	> Mail: loneavon1@gmail.com 
	> Created Time: 2014年02月24日 星期一 00时52分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

const int maxline = 4096;
const char * retmeg="It's server ackmeggage!\n";

int main(int argc, char** argv)
{
        int    listenfd, connfd;
        struct sockaddr_in     servaddr;
        char    buff[4096];
        int     n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1  ){
            printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
            exit(0);
            
    }

        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(6666);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1 ){
            printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
            exit(0);
            
    }

    if( listen(listenfd, 10) == -1 ){
            printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
            exit(0);
            
    }

        printf("======waiting for client's request======\n");
    while(1){
        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1 ){
                    printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
                    continue;
                
        }
            n = recv(connfd, buff, maxline, 0);
            buff[n] = '\0';
            printf("recv msg from client: %s\n", buff);
            if ( send(connfd,retmeg,strlen(retmeg),0) < 0 ){
                printf("send msg error: %s (errno: %d)\n",strerror(errno),errno);
            }
            close(connfd);
            
    }

        close(listenfd);

}

