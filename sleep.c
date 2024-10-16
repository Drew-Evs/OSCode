//includes the atoi 
#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    //confirms that entered correctly
    if (argc != 2) {
        printf("Usage: Sleep integer");
        exit(1);
    }
    
    //converts to integer
    int time = atoi(argv[1]);

    //calls the system sleep 
    sleep(time);

    exit(0);
}