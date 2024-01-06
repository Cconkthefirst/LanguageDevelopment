#ifndef _EVALEXPR_H_
#define _EVALEXPR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog.h"
#include "symbols.h"


typedef enum { identifier, func1gethtml, func2findwebimages, func3organizewebinfo } EXPRCODE; // one typdef

// Separate functions for whichever function
// instead of the operate function with the big switch statement
// then after command is added we can call whichever function we need in gencode 
void func1(char*op) { 
    Command cmdOp;
    cmdOp.code = Func1;
    addCommand(cmdOp);
}

void func2(char*op) {
    Command cmdOp;
    cmdOp.code = Func2;
    addCommand(cmdOp);
}

void func3(char*op) {
    Command cmdOp;
    cmdOp.code = Func3;
    addCommand(cmdOp); 
}


void gencode(EXPRCODE code, char* item) { // gencode works by looking at what function you saw, and calling a function instead of operate
    switch (code) {
        case func1gethtml: func1(item); break; 
        case func2findwebimages: func2(item); break;
        case func3organizewebinfo: func3(item); break;
    }
}

#endif