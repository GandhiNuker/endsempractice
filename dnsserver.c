#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[100];
    socklen_t len = sizeof(client_addr);

    char *reply = "Not Found";

    char *domain[] ={"google.com","gmail.com"};
    char *ip[] = {"8.8.8.8","1.1.1.1"};

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Server waiting...\n");

    recvfrom(server_fd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client_addr, &len);

    for(int i = 0 ; i < 2 ; i++){
        if(strcmp(buffer,domain[i])==0)
        reply = ip[i];
    }

    printf("Client: %s\n", buffer);

    sendto(server_fd, reply, strlen(reply)+1, 0,
           (struct sockaddr *)&client_addr, len);

    close(server_fd);

    return 0;
}
