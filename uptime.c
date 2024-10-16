#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    //uses uptime syscall to calc uptime in ticks
    int ticks = uptime();
    printf("Program lasted %d ticks", ticks);
}