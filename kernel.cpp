#include "lib/io.h"
#include "lib/logo.h"
#include "lib/GDT.h"

/*
    Moon OS
        - A simple OS for x86_64 hardware -
        - Made by Athanasius Sokol -
    Importent note: if binary goes past 0x28000 then you will need to update bootloader
    Importent note: type double and float will cause a crash, to fix look into enabling SSE
*/

extern "C" void kmain(){
    logo();
    loadingBar bar{1};
    //GlobalDiscriptorTable GDT{};
    bar.loadTask();
    const char* str = u8"привет";
    printString(10, 10, str, 0x7);
    letter(10, 20, '!', 0x7);
    //printHex(100, 20, 0xCAFE, 7);
    for(;;);
}
