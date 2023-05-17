#Mazen Talaat U3 L3 14-Nov-2021
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -g -O0
INCS=-I. -I/lesson4
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project=learn_embedded


all_bin: $(Project).bin
	@echo "------Yarab Saidni : You Can Do It Adem----------"

all_hex: $(Project).hex
	@echo "------Yarab Saidni : You Can Do It Adem----------"

%.s: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) -S $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

%.o: %.s
	$(CC)as.exe $< -o $@
	
$(Project).axf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	
$(Project).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map


$(Project).bin: $(Project).axf
	$(CC)objcopy.exe -O binary $< $@

$(Project).bin: $(Project).elf
	
	$(CC)objcopy.exe -O binary $< $@

$(Project).hex: $(Project).elf
	$(CC)objcopy.exe -O ihex $< $@

$(Project).hex: $(Project).axf
	$(CC)objcopy.exe -O ihex $< $@

assembly: $(Project).bin
	$(CC)objdump -D $(Project).elf > assembly_out.s
	
clean_all:
	rm -rf *.o *.elf *.bin *.map *.axf *.hex *.iex *.s
	@echo "-------------Clear Everything-----------------"
clean:
	rm -rf *.elf *.bin *.hex
