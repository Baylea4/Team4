#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main() 

{ 

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 

    { 

        perror("socket"); 

        return -1; 

    } 

    printf("socket..............\n"); 


    struct sockaddr_in myaddr; 
    memset(&myaddr, 0, sizeof(myaddr)); 
    myaddr.sin_family       = AF_INET; 
    myaddr.sin_port         = htons(5000); 
    myaddr.sin_addr.s_addr = INADDR_ANY; 
 

 if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))

    { 

        perror("bind"); 

        return -1; 

    } 

    printf("bind..........\n"); 

 

    if (0 > listen(sockfd, 8))
    { 

        perror("listen"); 

        return -1; 

    } 

    printf("listen............\n"); 


    int connfd = accept(sockfd, NULL, NULL);
    if (connfd < 0) 
    { 

        perror("accept"); 

        return -1; 
    } 
    printf("accept..............\n"); 
    char buf[100];
    int ret; 
    while (1) 
    { 

        memset(buf, 0, sizeof(buf)); 
        ret = read(connfd, buf, sizeof(buf)); 
        if (0 > ret) 

        { 

            perror("read"); 

            break; 

        }
        else if (0 == ret) 
        { 

            printf("write close!\n"); 
            break; 

        } 
        printf("recv: "); 
        fputs(buf, stdout);
    } 
    close(sockfd); 
    close(connfd);
    return 0; 

} 