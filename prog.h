#ifndef _PROG_H_
#define _PROG_H_

#include <stdio.h>

typedef enum {  // added our stuff here
    Func1, Func2, Func3, Assign
} ProgCode2;

typedef struct {
    ProgCode code;
    char* data;
    char* data2; // added this for the assignment 
} Command;

int cmds = 0;
Command program[1000];

void addCommand(Command cmd) {
    program[cmds++] = cmd;
}


#endif