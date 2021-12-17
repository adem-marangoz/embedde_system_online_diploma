#Created By Adem AlNajjar 
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m4 -mthumb -gdwarf-2 -g
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project=unit3_lab4_cortexM4

all: $(Project).bin
	@echo "------Yarab Saidni : You Can Do It Adem----------"
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
$(Project).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	cp $(Project).elf $(Project).axf
	
$(Project).bin: $(Project).elf
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
	rm -rf *.o *.elf *.bin *.map *.axf
	@echo "-------------Clear Everything-----------------"
clean:
	rm -rf *.elf *.bin
