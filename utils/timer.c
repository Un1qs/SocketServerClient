#include <stdio.h>
#include <time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESCOKET(s) close (s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)


int main() {
    time_t timer;
    time(&timer);

    printf("local time is : %s", ctime(&timer));
    return 0;
}