# Moon OS
A simple x86_64 operating system

Currently should boot a grey screen with a single black point at location (10, 10) in the 320/200 vga grid

Known issue: floating point decloration causes crash (SOLVED: this is due to not enabling SSE, for know find alternatives)

[Order of events]

  Bootloader:
  
    Sets up stack
    
    Reads first 5 segments (+ bootsegment) from usb or floppy (CD or DVD may work, but is untested)
    
    Checks and loads possible remaining segments
    
    Checks and if needed enables A20 line
    
    Checks for long mode capability
    
    Sets VGA mode to 0x13
    
    Switchs to long mode
    
    Jumps to 0x8000 where kernel (hopefully) is located
    
  Kernel:
  
    Tests current io.h functions
