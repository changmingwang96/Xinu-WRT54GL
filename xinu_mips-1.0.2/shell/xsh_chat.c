#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define message_length 50

char user1[] = "ming";
char pw1[] = "0217";
char user2[] = "shuo";
char pw2[] = "0729";


local chat(ushort in,ushort out,char *username){
    char message[message_length];
    int exit = 0;
    int i;
    
    while(exit == 0){
        //clean the message buffer
        for(i = 0; i < message_length ;i++){
            message[i] = '\0';
        }
        //get the message
        read(in,message,message_length);
        //exit function let user log off
        if(strncmp(message,"exit",4) == 0){
            exit = 1;
            strcpy(message,"** logging off **");
        }
        //send the chat message
        fprintf(out,"%s: ", username);
        write(out,message,strlen(message));
    }
    
    return OK;
}

command xsh_chat(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]){
    char input_id[30];
    char input_pw[30];
    int chatstatus = 0;
    do{
        fprintf(stdout,"\nEnter your username :");
        read(stdin,input_id,30);
        fprintf(stdout,"\nEnter your password :");
        read(stdin,input_pw,30);
       
      if((strncmp(input_id, user1, 4) == 0 && strncmp(input_pw, pw1, 4) == 0 ) || (strncmp(input_id, user2, 4) == 0 && strncmp(input_pw, pw2, 4) == 0 )){
        input_id[4] = '\0';
        fprintf(stdout, "\n log in sucess!!\n");
        fprintf (stdout, "\nWelcome %s !\n", input_id);
        fprintf(stdout, "\nType exit to quit! \n");
        chatstatus = 1;
        }else{
        fprintf(stdout, "Log in failed !\n");
        fprintf(stdout, "Please try again !\n");
    }
    
    
  }while(chatstatus == 0);
          
          if(stdin == TTY0){
              chat(TTY0,TTY1,input_id);
          }else if(stdin == TTY1){
              chat(TTY1,TTY0,input_id);
          }
          
          return OK;
}
