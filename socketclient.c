/*************************************************************************
	> File Name: socketclient.c
	> Author: Li Wen
	> Mail: loneavon1@gmail.com 
	> Created Time: 2014年02月24日 星期一 00时53分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

const int maxline = 4096;


int main(int argc, char** argv)
{
        int    sockfd, retnum;
        char    recvline[4096], sendline[4096];
        struct sockaddr_in    servaddr;

    if( argc != 2 ){
            printf("usage: ./client <ipaddress>\n");
            exit(0);
            
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
            printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
            exit(0);
            
    }

        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0 ){
            printf("inet_pton error for %s\n",argv[1]);
            exit(0);
            
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 ){
            printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
            exit(0);
            
    }

        printf("send msg to server: \n");
        fgets(sendline, 4096, stdin);
        if( send(sockfd, sendline, strlen(sendline), 0) < 0 )
    {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            exit(0);
            
    }
    if ( retnum=recv(sockfd,recvline,maxline,0) < 0 ){
            printf("recv msg error: %s(errno: %d)\n",strerror(errno), errno);
            exit(0);
        
    }
//    recvline[retnum] = '\0';
    printf("%s\n",recvline);
        close(sockfd);
        exit(0);

}
