#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[100];

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer,"\n")] = '\0';

    sendto(client_fd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    recvfrom(client_fd, buffer, sizeof(buffer), 0, NULL, NULL);

    printf("Server: %s\n", buffer);

    close(client_fd);

    return 0;
}
