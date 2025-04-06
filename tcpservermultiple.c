#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{   
    int server_socket,client_socket;
    char buffer[1024];
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_size;
    
    server_socket=socket(AF_INET,SOCK_STREAM,0);//cREATED THE SOCKET FOR THE SERVER
    
    server_addr.sin_family=AF_INET;//CONFIGURED THESOCKET WITH THE IP ADDRESS
    server_addr.sin_port=htons(12345);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    
    bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));//BINDED
    
    listen(server_socket,1);
    printf("waiting for connection...");
    
    addr_size=sizeof(client_addr);
    client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&addr_size);
    printf("client connected...");
    
    while(1)
    {
        recv(client_socket,buffer,1024,0);
        buffer[strcspn(buffer, "\n")] = 0;
        printf("client:%s",buffer);
        if(strcmp(buffer,"exit")==0)
        {
            break;
        }
        fgets(buffer,1024,stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(client_socket,buffer,strlen(buffer),0);
        if(strcmp(buffer,"exit")==0)
        {
            break;
        }
    }
    close(client_socket);
    close(server_socket);
    return 0;
}