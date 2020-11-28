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
  
  To install:
  
    preinstall qemu, nasm, and g++
    chmod +x os.sh
    ./os.sh bootloader
    ./os.sh all
    This will run the program in a qemu virtual machine, 
    to run on hardware preform all of the above steps then write os.bin to a usb,
    then configure the BIOS on the host computer to boot of usb before internal disk,
    and enjoy what little there is to enjoy
