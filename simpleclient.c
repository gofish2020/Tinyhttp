#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


void request_write(int client) {
    char buf[1024];

    sprintf(buf, "GET / HTTP1.1\r\n");
    write(client, buf, strlen(buf));
    sprintf(buf, "Accept: text/html\r\n");
    write(client, buf, strlen(buf));
    sprintf(buf, "\r\n");
    write(client, buf, strlen(buf));

}

void response_read ( int client) {
    char res[1024];
    read(client, res, 1024);
    printf("%s", res);
    char page[4096];
    read(client, page, 4096);
    printf("%s", page);
}

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(4000);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    }

    request_write(sockfd);
    response_read(sockfd);
    close(sockfd);
    exit(0);
}


