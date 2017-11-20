#include <kernel.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INITSTK 0
#define INITPRIO 0

int counter1 = 0;
void proc11();
void proc22();
void proc33();
semaphore mutex1;


command xsh_mutex(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[]){
    mutex1 = newsem(1);
    counter1 = 0;
    ready(create((void *)proc11, INITSTK, INITPRIO, "PROC1", 2, 0, NULL), RESCHED_NO);
    ready(create((void *)proc22, INITSTK, INITPRIO, "PROC2", 2, 0, NULL), RESCHED_NO);
    ready(create((void *)proc33, INITSTK, INITPRIO, "PROC3", 2, 0, NULL), RESCHED_NO);
    return OK;
}
void proc11(){
    while(1){
        sleep(rand()/10);
        wait(mutex1);
        counter1++;
        signal(mutex1);
        printf("\nNow in proc11, the count is %d\n", counter1);
    }
}
void proc22(){
    while(1){
        sleep(rand()/10);
        wait(mutex1);
        counter1++;
        signal(mutex1);
        printf("\nNow in proc22, the count is %d\n", counter1);
    }
}
void proc33(){
    while(1){
        sleep(rand()/10);
        wait(mutex1);
        counter1++;
        signal(mutex1);
        printf("\nNow in proc33, the count is %d\n", counter1);
    }
}
