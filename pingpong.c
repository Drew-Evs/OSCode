#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    //holds the file descriptors for read and write
    int p[2];

    //creates the pipe
    pipe(p);

    //reads pipe value of parent
    int readVal = getpid();
    printf("%d: Recieved Ping\n", readVal);

    //forks child and recieves pong and pid of child
    if (fork() == 0) {
        int readVal = getpid();
        printf("%d: Recieved Pong\n", readVal);
    }
}