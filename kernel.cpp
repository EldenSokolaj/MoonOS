#include "lib/io.h"
#include "lib/logo.h"

/*
    Moon OS
        - A simple OS for x86_64 hardware -
        - Made by Athanasius Sokol -
    Importent note: if binary goes past 0x20000 then you will need to update bootloader
    Importent note: type double and float will cause a crash, to fix look into enabling SSE
*/

extern "C" void kmain(){
    clrscr(7);
    rect(50, 10, 100, 100, 0);
    rect(55, 15, 90, 90, 0x6E);
    rect(60, 20, 20, 20, 0);
    rect(120, 80, 20, 20, 0);
    rect(90, 50, 20, 20, 0);
    for(;;);
}
