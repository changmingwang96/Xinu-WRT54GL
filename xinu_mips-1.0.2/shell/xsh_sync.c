
#include <kernel.h>
#include <semaphore.h>
#include <stdio.h>
#include <tty.h>
#include <string.h>
#include <stdlib.h>


#define INITSTK 0
#define INITPRIO 0
void proc1();
void proc2();
void proc3();

semaphore synch12;
semaphore synch23;
semaphore synch31;
int counter = 0;

command xsh_sync(ushort stdin, ushort stdout, ushort stderr,
                  ushort nargs, char *args[])
{
    synch12 = newsem(0);
    synch23 = newsem(0);
    synch31 = newsem(0);
    
    ready(create((void *)proc1, INITSTK, INITPRIO, "PROC1", 2, 0, NULL), RESCHED_NO);
    ready(create((void *)proc2, INITSTK, INITPRIO, "PROC2", 2, 0, NULL), RESCHED_NO);
    ready(create((void *)proc3, INITSTK, INITPRIO, "PROC3", 2, 0, NULL), RESCHED_NO);
    signal(synch31);
    counter = 0;
    return OK;
}

void proc1(){
    while(1){
        sleep(rand()/200);
        wait(synch31);
        counter++;
        printf("\nNow in proc1, the count is %d\n", counter);
        signal(synch12);
    }
}
void proc2(){
    while(1){
        sleep(rand()/100);
        wait(synch12);
        counter = counter + 2;
        printf("\nNow in proc2, the count is %d\n", counter);
        signal(synch23);
    }
}
void proc3(){
    while(1){
        sleep(rand()/300);
        wait(synch23);
        counter = counter + 3;
        printf("\nNow in proc3, the count is %d\n", counter);
        signal(synch31);
    }
}
