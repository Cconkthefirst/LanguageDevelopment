#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include "prog.h"
#include <string.h> // added this to make red squiggles happy

typedef struct { // same
    char* name;
    int val;
} Symbol;

int symbolcount = 0;
Symbol* symboltable[100];

int getSymbolCount() { return symbolcount; }
Symbol* getSymbolAt(int i) { return symboltable[i]; }

Symbol* getSymbol(char* s) {
    for (int i=0; i<symbolcount; i++) {
        if (strcmp(symboltable[i]->name, s) == 0)
            return symboltable[i];
    }
    return NULL;
}

Symbol* checkSymbol(char* s) {
    Symbol* symbol = getSymbol(s);
    if (symbol == NULL) {
        symbol = (Symbol*) malloc(sizeof(Symbol));
        symbol->name = (char*)strdup(s);
        symbol->val = 0;
        symboltable[symbolcount++] = symbol;
    }
    return symbol;
}

void cleanupSymbols() {
    for (int i=0; i<symbolcount; i++) {
        free(symboltable[i]->name);
        free(symboltable[i]);
    }
}

void assignSymbol(char* s, char* u) { 
    printf("%s %s \n", s, u); // test output 
    Symbol* symbol = checkSymbol(s); 
    Command cmd;
    cmd.code = Assign;
    cmd.data = symbol->name;
    cmd.data2 = strdup(u); // pete suggestion, added data2 to Command class
    addCommand(cmd); 
  
}

#endif