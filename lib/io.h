#ifndef IO_H
#define IO_H

#include "math.h"

/*
    Graphics are arranged in points in 320*200 grid
    Use values in which (-1 < x < 320) and (-1 < y < 200)
*/

typedef unsigned char byte;

int io_x = 0, io_y = 0;
byte *vga = (byte *)0xA0000;

void set(int x, int y, char color){
    if(x > -1 && x < 320 && y > -1 && y < 200){
        unsigned short offset = 320 * y + x;
        vga[offset] = color;
    }
}

void clrscr(char color){
    for(int i = 0; i < 64000; i++){
        vga[i] = color;
    }
}
/*
void line(int x1, int y1, int x2, int y2, char color){
    if(x1 > x2){
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    int deltax = x2 - x1;
    int deltay = y2 - y1;
    double err = 0.0;
    double deltaError = abs((double)deltay / deltax);
    int y = y1;
    for(int x = x1; x < x2; x++){
        set(x, y, color);
        err += deltaError;
        if(err > 0.5){
            y += deltay;
            err -= 1;
        }
    }
}
*/
#endif
