#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
int secs, usecs;

volatile sig_atomic_t print_flag = false;

void handle_alarm( int sig ) {
    print_flag = true;
}

int main(){
    struct timespec nsecs, nsecs2;
    signal(SIGALRM, handle_alarm);

    printf("Input secs need to sleep: ");
    scanf("%i",&secs);
    alarm(1);
    sleep(secs);
    printf("\nSleep in %i (secs) finished!",secs);
    
    printf("\nInput usecs need to sleep: ");
    scanf("%i",&usecs);
    alarm(1);
    usleep(usecs);
    printf("\nSleep in %i (usecs) finished!",usecs);

    printf("\nStart nano sleep in \n");
    nsecs.tv_sec = 4;
    // nsecs.tv_nsec = 100000000L;
    nsecs.tv_nsec = 0;

    nanosleep(&nsecs,&nsecs2);
    alarm(1);
    printf("\nthe time left: %i",(int)nsecs2.tv_sec);
    return 0;
};
