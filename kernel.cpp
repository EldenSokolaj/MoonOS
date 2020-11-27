#include "lib/io.h"
#include "lib/logo.h"

/*
    Moon OS
        - A simple OS for x86_64 hardware -
        - Made by Athanasius Sokol -
    Importent note: if binary goes past 0x20000 then you will need to update bootloader
*/

extern "C" void kmain(){
    clrscr(7);
    set(10, 10, 0);
    for(;;);
}
