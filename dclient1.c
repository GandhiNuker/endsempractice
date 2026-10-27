#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){

    int client_fd, n, header_done = 0;
    struct sockaddr_in server_addr;
    char buffer[1000];
    socklen_t len = sizeof(server_addr);

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    connect(client_fd,(struct sockaddr*)&server_addr,len);

    char *request = "GET /index.html HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    send(client_fd,request,strlen(request),0);

    FILE *fp = fopen("downloaded_index.html","wb");

    while((n = recv(client_fd,buffer,sizeof(buffer)-1,0)) > 0){
        buffer[n] = '\0';
        char *body = buffer;
        int size = n;

        if(header_done == 0){
            char *p = strstr(buffer,"\r\n\r\n");
            if(p != NULL){
                body = p + 4;
                size = n - (body - buffer);
                header_done = 1;
            }
        }
        fwrite(body,1,size,fp);
    }

    fclose(fp);
    close(client_fd);
    printf("File downloaded successfully\n");

    return 0;
}
