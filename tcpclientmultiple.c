#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{
    int client_socket;
    char buffer[1024];
    struct sockaddr_in server_addr;
    
    client_socket=socket(AF_INET,SOCK_STREAM,0);
    
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(12345);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    
    connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("client connected...");
    
    while(1)
    {
        fgets(buffer,1024,stdin);
        send(client_socket,buffer,strlen(buffer),0);
        if(strcmp(buffer,"exit\n")==0)
        {
            break;
        }
        recv(client_socket,buffer,1024,0);
        printf("server:%s",buffer);
        if(strcmp(buffer,"exit\n")==0)
        {
            break;
        }
    }
    close(client_socket);
    return 0;
}