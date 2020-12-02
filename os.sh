#!/bin/bash

run="-r"
comp="-c"
make="-m"
kernel="kernel"
all="all"
boot="bootloader"

if [[ "$1" == "$run" ]]; then
  qemu-system-x86_64 -cpu core2duo -fda $2.bin
elif [[ "$1" == "$comp" ]]; then
  nasm -fbin $2.s -o $2.bin
elif [[ "$1" == "$make" ]]; then
  cat boot.bin $2.bin > os.bin
elif [[ "$1" == "$kernel" ]]; then
  nasm -f elf64 kernel.s -o kasm.o
	g++ -mno-sse -mno-sse2 -fno-stack-protector -Wno-multichar -c kernel.cpp -o kc.o
  ld -o kernel.bin kasm.o kc.o -T link.ld
  rm kc.o
  rm kasm.o
elif [[ "$1" == "$all" ]]; then
  nasm -f elf64 kernel.s -o kasm.o
	g++ -mno-sse -mno-sse2 -fno-stack-protector -Wno-multichar -c kernel.cpp -o kc.o
  ld -o kernel.bin kasm.o kc.o -T link.ld
  rm kc.o
  rm kasm.o
  cat boot.bin kernel.bin > os.bin
  truncate os.bin -s 20k
  qemu-system-x86_64 -cpu core2duo -fda os.bin
elif [[ "$1" == "$boot" ]]; then
  cd bootloader
  nasm -fbin boot.s -o ../boot.bin
  cd -
fi
