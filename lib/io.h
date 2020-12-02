#ifndef IO_H
#define IO_H

/*
    Graphics are arranged in points in 320*200 grid
    Use values in which (-1 < x < 320) and (-1 < y < 200)
    Importent Note: Line functions do not currently work
*/

#include "math.h"
#include "font.h"
#include "types.h"

int io_x = 0, io_y = 0;
byte *vga = (byte *)0xA0000;

void set(int x, int y, char color){
    if(x > -1 && x < 320 && y > -1 && y < 200){
        vga[(y << 8) + (y << 6) + x] = color;
    }
}

void clrscr(char color){
    for(int i = 0; i < 64000; i++){
        vga[i] = color;
    }
}
/*
    plotLineHigh(x0, y0, x1, y1)
    dx = x1 - x0
    dy = y1 - y0
    xi = 1
    if dx < 0
        xi = -1
        dx = -dx
    end if
    D = (2 * dx) - dy
    x = x0

    for y from y0 to y1
        plot(x, y)
        if D > 0
            x = x + xi
            D = D + (2 * (dx - dy))
        end if
        else
            D = D + 2*dx

    plotLineLow(x0, y0, x1, y1)
    dx = x1 - x0
    dy = y1 - y0
    yi = 1
    if dy < 0
        yi = -1
        dy = -dy
    end if
    D = (2 * dy) - dx
    y = y0

    for x from x0 to x1
        plot(x, y)
        if D > 0
            y = y + yi
            D = D + (2 * (dy - dx))
        end if
        else
            D = D + 2*dy

    plotLine(x0, y0, x1, y1)
    if abs(y1 - y0) < abs(x1 - x0)
        if x0 > x1
            plotLineLow(x1, y1, x0, y0)
        else
            plotLineLow(x0, y0, x1, y1)
        end if
    else
        if y0 > y1
            plotLineHigh(x1, y1, x0, y0)
        else
            plotLineHigh(x0, y0, x1, y1)
        end if
    end if
*/

void plotLineLow(int x1, int y1, int x2, int y2, char color){
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;
    if(dy < 0){
        yi = -1;
        dy = -dy;
    }
    int d = (2 * dy) - dx;
    int y = y1;
    for(int x = x1; x < x2; x++){
        set(x, y, color);
        if(d > 0){
            y += y1;
            d += 2 * (dy - dx);
        }
            d += 2 * dy;
    }
}

void plotLineHigh(int x1, int y1, int x2, int y2, char color){
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;
    if(dx < 0){
        xi = -1;
        dx = -dx;
    }
    int d = (2 * dx) - dy;
    int x = x1;
    for(int y = y1; y < y2; y++){
        set(x, y, color);
        if(d > 0){
            x = x + xi;
            d += 2 * (dx - dy);
        }
        d += 2 * dx;
    }
}

void line(int x1, int y1, int x2, int y2, char color){
    if(abs(y2 - y1) > abs(x2 - x1)){
        if(x1 > x2){
            plotLineLow(x2, y2, x1, y1, color);
        } else {
            plotLineLow(x1, y1, x2, y2, color);
        }
    } else {
        if(y1 > y2){
            plotLineHigh(x2, y2, x1, y1, color);
        } else {
            plotLineHigh(x1, y1, x2, y2, color);
        }
    }
}

void rect(int x, int y, int width, int height, char color){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            set(x+j, y+i, color);
        }
    }
}

void circ(int loc_x, int loc_y, int r, char color){
    int n = 2 * r + 1;
    int x, y;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            x = i - r;
            y = j - r;
            if (x * x + y * y <= r * r + 1){
                set(x + loc_x, y + loc_y, color);
            }
        }
    }
}

void printHex(int loc_x, int loc_y, long data, char color);

void letter(int loc_x, int loc_y, char input, char color) {
    unsigned char* bitmap = basicfont[input];
    int x,y;
    int s;
    for (x=0; x < 8; x++) {
        for (y=0; y < 8; y++) {
            s = bitmap[x] & 1 << y;
            if(s){
                set(loc_x + y, loc_y + x, color);
            }
        }
    }
}

void unicodeLetter(int loc_x, int loc_y, const char* letter, char color){
    unsigned char* bitmap;
    short input = (((short)*letter) << 8) | (short)*(letter + 1);
    if(input >= 1040 && input <= 1071){
        bitmap = crylicfont[input - 1040];
    } else if(input > 1072 && input < 1072){
        bitmap = crylicfont[input - 1072];
    } else {
        bitmap = unknown;
    }
    int x,y;
    int s;
    for (x=0; x < 8; x++) {
        for (y=0; y < 8; y++) {
            s = bitmap[x] & 1 << y;
            if(s){
                set(loc_x + y, loc_y + x, color);
            }
        }
    }
}

void printString(int x, int y, const char* input, char color){
    //check if first byte is directional
    while(*input != '\0'){
        if(*input >= 0 && *input <= 0x7F){
            letter(x, y, *input, color);
        } else {
            unicodeLetter(x, y, input, color);
            input++;
        }
        input++;
        x += 8;
    }
}

void printHex(int x, int y, long data, char color){
    char str[] = "0x********\0";
    long temp;
    for(int i = 7; i > -1; i--){
        temp = data % 16;
        if(data < 10){
            str[i+2] = temp + 48;
        } else {
            str[i+2] = temp + 55;
        }
        data = data / 16;
    }
    printString(x, y, (const char*)str, color);
}

extern "C" void dispFail(){
    clrscr(1);
    printString(5, 5, "Fatal Error", 0xF);
    printString(80, 60, "unknown reason", 0xF);
    for(;;);
}

#endif
