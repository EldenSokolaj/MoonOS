#ifndef LOGO_H
#define LOGO_H

#include "io.h"

void logo(){
    clrscr(0);
    circ(140, 90, 70, 7);
    circ(170, 80, 70, 0);
    printString(140, 50, "Moon OS\0", 7);
}

class loadingBar{
    private:
        int done;
        int segsize;

    public:
        loadingBar(int tasks){
            done = 0;
            rect(140, 100, 150, 10, 0x7);
            rect(142, 102, 146, 6, 0);
            segsize = 146 / tasks;
        }

        void loadTask(){
            rect(segsize*done+142, 102, segsize, 6, 0x32);
            done++;
        }
};

#endif