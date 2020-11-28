#ifndef IO_H
#define IO_H

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

void rect(int x, int y, int width, int height, char color){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            set(x+j, y+i, color);
        }
    }
}

#endif
