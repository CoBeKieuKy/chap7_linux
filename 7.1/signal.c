#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

volatile sig_atomic_t print_flag = false;
volatile sig_atomic_t print_flag2 = false;
volatile sig_atomic_t time = 0;

void handle_alarm( int sig ) {
    print_flag = true;
    time++;
}

void handle_cancel(int sig){
    print_flag2 = true;
}

int main() {
  int settime =3;
    signal( SIGALRM, handle_alarm ); // Install handler first,
    signal( SIGINT, handle_cancel);
    alarm( 1 ); // before scheduling it to be called.
    printf("input settime: ");
    scanf("%d",&settime);
    for (;;) {
        signal(SIGINT, handle_cancel);

        if (print_flag) {
          if(time == settime){
            printf( "done\n");
            break;
          }
          print_flag = false;
          alarm( 1 );
        }
        if(print_flag2){
          printf("done\n");
          break;
        }
        print_flag2 = false;
    }
}