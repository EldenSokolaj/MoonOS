# Moon OS
A simple x86_64 operating system

Currently should boot a grey screen with a single black point at location (10, 10) in the 320/200 vga grid

Current issue: floating point decloration causes crash

Order of events:

  Bootloader:
  
    Sets up stack
    
    Reads first 5 segments (+ bootsegment) from usb or floppy (CD or DVD may work, but is untested)
    
    Checks and loads possible remaining segments
    
    Checks and if needed enables A20 line
    
    Checks for long mode capability
    
    Switchs to long mode
    
    Sets VGA mode to 0x13
    
    Jumps to 0x8000 where kernel (hopefully) is located
    
  Kernel:
  
    Sets screen to grey
    
    Sets point at location (10, 10) to black
    
    [Currently io.h is the main file under development. However for now declairing a float causes a crash which has put a hold on everything else]
