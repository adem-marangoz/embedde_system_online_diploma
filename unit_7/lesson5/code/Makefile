#Mazen Talaat U3 L3 14-Nov-2021
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I. -I/lesson4
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project=learn_embedded

all: $(Project).bin
	@echo "------Yarab Saidni : You Can Do It Adem----------"
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
$(Project).axf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	
$(Project).bin: $(Project).axf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm -rf *.o *.elf *.bin *.map *.axf
	@echo "-------------Clear Everything-----------------"
clean:
	rm -rf *.elf *.bin
