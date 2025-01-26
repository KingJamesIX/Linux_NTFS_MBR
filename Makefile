all: mbr.bin

mbr.bin: mbr.asm
        nasm -f bin -o mbr.bin mbr.asm

clean:
        rm -f mbr.bin
