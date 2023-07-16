#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESCOKET(s) close (s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)


int main() {
    
    puts("Configuring Local addreesses");
    struct addrinfo hints;
    memset(&hints , 0 , sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address; 
    getaddrinfo(0, "8080",&hints,&bind_address);

    puts(" creating socket ....\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
                    bind_address->ai_protocol);
    
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr,"socket() failed . (%d)\n",GETSOCKETERRNO());
        return 1;
    }

    
    puts( "Binding socket to local address ...\n");
    if (bind(socket_listen,
            bind_address->ai_addr, bind_address->ai_addrlen)) {
                fprintf(stderr, "bind() failed. (%d)\n",GETSOCKETERRNO());
                return 1;
            }

    freeaddrinfo(bind_address);

    puts("Listening .....\n");
    if(listen(socket_listen,10) < 0) {
        fprintf(stderr," listen failed (%d)\n",GETSOCKETERRNO());
        return 1;
    }
    puts("Waiting for connections ....\n");
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    SOCKET socket_client = accept(socket_listen,(struct sockaddr*) &client_address,&client_len);
    if(!ISVALIDSOCKET(socket_client)){
        fprintf(stderr,"accept() failed.(%d)\n",GETSOCKETERRNO());
        return 1;
    }

    printf("Client is connected... ");
    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client_address,
    client_len, address_buffer, sizeof(address_buffer), 0, 0,NI_NUMERICHOST);
    printf("%s\n", address_buffer);

    time_t timer;
    time(&timer);

    printf("local time is : %s", ctime(&timer));
    return 0;
}