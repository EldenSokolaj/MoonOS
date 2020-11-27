#include "lib/io.h"
#include "lib/logo.h"

/*
    Rune OS
    Made by Athanasius Sokol
    Importent note: if binary goes past 0x20000 then you will need to update bootloader
*/

extern "C" void kmain(){
    float b = 0;
    float a = b + 2;
    b = a * 3;
    clrscr(7);
    //line(10, 10, 20, 20, 0);
    set(10, 10, 0);
    for(;;);
}
