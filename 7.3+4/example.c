#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

#define PROC_OK 0
#define PROC_NG -1

int main(void){
    printf("main :start\n");

    char*args[] = {"ls","-1",NULL};
    int iRet = 0;
    pid_t pid = 0, pid2 = 0;
    int status = 0;

    char *cmd = "ls";
    char *argv[3];
    argv[0] = "ls";
    argv[1] = "-ls";
    argv[2] = NULL;
    pid2  = fork();

    switch (pid = fork()){
    
    case -1:
    perror("processGenerate fork");
    exit(1);

    case 0:
    kill(pid,SIGALRM);
    kill(pid2,SIGALRM); //CAU 2

    iRet = execv("/bin/ls",args);
    // execvp(cmd, argv); //CAU 1
    printf("execv ret = %d\n",iRet);
    if(iRet == PROC_NG)
        exit(1);

    default:
    printf("Parent Process ChildProcPid = %d\n",pid);
    pid = wait(&status);// CAU 3 comment phan nay
    printf("pid = %d, status = %d\n",pid,status);
        break;
    }

    printf("main :end\n");
    return 0;
}