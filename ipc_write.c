#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main(int argc,char* argv[]) {
    int shmid;
    key_t key;
    char *shm, *ptr;

    // Generate a key
    key = ftok("shmfile", 'R');

    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    // Attach the shared memory segment
    shm = shmat(shmid, NULL, 0);


    // Write to the shared memory
    ptr = shm;
    if(argc<2){
        sprintf(ptr, "Hello, shared memory!\nNo messages were passed from CLI\n");
    }else{
        char buff[100]="";
        for (int i = 1; i < argc; i++) {
            strcat(buff, argv[i]);
            if (i < argc - 1) strcat(buff, " ");  // Add space between args
        }
        sprintf(ptr, "Hello, shared memory!\nHere's the message from the CLI:\n%s\n",buff);
    }
    printf("data written to shared memory \n");
    // Detach the shared memory segment
    shmdt(shm);

    return 0;
}

