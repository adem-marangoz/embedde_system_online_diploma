#copyright	Created By Adem Maragoz 
CC=arm-none-eabi-
CFLAG=-mcpu=arm926ej-s -g
INCS=-I .
SRC=$(wildcard *.c)
OBJC=$(SRC:.c=.o)
AS=$(wildcard *.s)
AsOBJ=$(AS:.s=.o)
LIBS=


all: learn_embedded.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel $<
	@echo "------------Yarab Help Me I Need You----------"

startup.o: startup.s
	$(CC)as.exe $(CFLAG) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c  $(INCS) $(CFLAG) $< -o $@

learn-embedded.elf: $(OBJC) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJC) $(AsBJC) -o $@ 

learn_embedded.bin:learn-embedded.elf
	$(CC)objcopy.exe -O binary $< $@

clear_all:
	rm *.o *.elf *.bin *.map

clear:
	em *.elf *.bin *.map
