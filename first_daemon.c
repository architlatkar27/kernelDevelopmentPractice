#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

// Source: https://www.thegeekstuff.com/2012/02/c-daemon-process/

int main(int argc, char** argv){
    pid_t process_id = 0;
    FILE *fp = NULL;
    pid_t sid = 0;
    process_id = fork();
    if(process_id < 0){ // if fork syscall fails then simply exit
        printf("fork failed\n");
        exit(1);
    }
    if(process_id > 0){
        printf("process id of child: %d \n", process_id);
        exit(0);
    }
    sid = setsid(); // create a new session for daemon
    if(sid < 0){ // session was not created
        exit(1);
    }
    // its good to change the working directory of the daemon
    chdir("/");
    close(STDIN_FILENO); // close stderr, stdin, stdout
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    // open a new file to write something
    fp = fopen("LOGFILE.txt", "w+");
    //int i=0;
    while(1){
        sleep(1);
        fprintf(fp,"Writing something\n");
        fflush(fp);
        // we can call some other function that will do useful work for daemon
        //i++;
    }
    fclose(fp);


    return 0;
}