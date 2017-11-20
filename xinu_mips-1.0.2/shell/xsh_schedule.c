#include <stdio.h>
#include <kernel.h>
#include <ctype.h>
#include <clock.h>
#define NFRAME 6
#define NSLOT 2
#define NFRAME1 10

#define SLOT_T 5000

int tps,slot=0,frame=0;
long int now,then;

void one() {
    printf("Task 1 running\n");
    sleep(500);
}


void two() {
    printf("Task 2 running\n");
    sleep(500);
}

void three() {
    printf("Task 3 running\n");
    sleep(500);
}

void four(){
    printf("Task 4 running\n");
    sleep(500);
}
/*void burn() {
 *
 *     clock_t bstart = times(&n);
 *
 *
 *         while ((( now = times(&n)) - then) < SLOT_T * tps / 1000) {
 *
 *              }
 *
 *                printf (" brn time = %2.2dms\n\n", (times(&n)-bstart)*1000/tps);
 *                      then = now;
 *                            cycle = CYCLEX;
 *                                  }*/
void burn() { printf (" brn cycle \n ");}
void burn1() {printf (" brn 0.2 cycle \n ");}
void (*ttable[NFRAME][NSLOT])() = {
    {one, one},
    {two, burn},
    {one, one},
    {two, burn},
    {one, one},
    {three,burn}};
void (*ttable2[NFRAME1][NSLOT])() = {
    {one, three},
    {two, burn1},
    {four, four},
    {one, burn},
    {two, burn1},
    {one, burn},
    {two, burn1},
    {one, burn},
    {one, burn},
    {two, burn1}};

command xsh_schedule(ushort stdout, ushort stdin, ushort stderr, ushort nargs, char *args[]) {

    if(strncmp(args[1],"first",5) == 0){
        now = clocktime;
        tps = 100;
        printf("clock ticks/sec = %d\n\n", tps);
        //    then = void clock_update(&n);
        while (1) {
            printf(" \n Starting a new hyperperiod \n");
            for (frame=0; frame <NFRAME; frame++)
            { printf ("\n Starting a new frame \n");
                for (slot=0; slot<NSLOT; slot++)
                    (*ttable[frame][slot])();
            }}
    }else if(strncmp(args[1],"second",6) == 0){
        now = clocktime;
        tps = 100;
        printf("clock ticks/sec = %d\n\n", tps);
        //    then = void clock_update(&n);
        while (1) {
            printf(" \n Starting a new hyperperiod \n");
            for (frame=0; frame <NFRAME1; frame++)
            { printf ("\n Starting a new frame \n");
                for (slot=0; slot<NSLOT; slot++)
                    (*ttable2[frame][slot])();
            }}
    }
    return OK;
}

