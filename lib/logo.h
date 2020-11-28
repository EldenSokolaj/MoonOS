#ifndef LOGO_H
#define LOGO_H

#include "io.h"

void logo(){
    clrscr(0);
    circ(140, 90, 70, 7);
    circ(170, 80, 70, 0);
    printString(140, 50, "Moon OS\0", 7);
}

#endif