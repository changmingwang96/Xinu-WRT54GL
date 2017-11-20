/**
 * @file     xsh_palindrome.c
 * @provides xsh_palindrome
 *
 * $Id$
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <stdio.h>
#include <kernel.h>
#include <stdlib.h>
#include <string.h>

/**
 * Shell command echos input text to standard out.
 * @param stdin descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_palindrome(ushort stdout, ushort stdin, ushort stderr, ushort nargs, char *args[])
{
//    int i;  /* counter for looping through arguments */
    
    /* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
    {
        fprintf(stdout, "Usage: clear\n");
        fprintf(stdout, "Clears the terminal.\n");
        fprintf(stdout, "\t--help\t display this help and exit\n");
        return SYSERR;
    }
    char *input;
    input = args[1];
    int l = 0;
    int h = strlen(input) - 1;
    while (h>1) {
        if(input[l++] != input [h--]){
            fprintf(stdout, "No\n");
            return;
        }
    }
    fprintf(stdout, "Yes\n");
    
        

    
    
    
//    /* loop through the arguments printing each as it is displayed */
//    for ( i = 1; i < nargs; i++ )
//    {
//        fprintf(stdout, "%s ", args[i]);
//    }
//
//    /* Just so the next prompt doesn't run on to this line */
//    fprintf(stdout, "\n");
//
//    /* there were no errors so, return OK */
    return OK;
}
