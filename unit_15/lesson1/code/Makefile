# Makefile created by Adem Marangoz

CC := arm-none-eabi-gcc
LD := arm-none-eabi-ld
CPY := arm-none-eabi-objcopy
CFLAGS := -mcpu=cortex-m3 -mthumb -gdwarf-2 


# SRC_DIR := ./source
ASM_DIR := asm
OBJ_DIR := obj
SRC_DIR := src
OUT_DIR := out
INC_DIR := inc

SRC := $(wildcard $(SRC_DIR)/*.c)
ASM := $(wildcard $(ASM_DIR)/*.s)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


Project := learn_embedded

bin: $(Project).bin
	@echo "===================================================================="
	@echo "---------------- YARAB Saibni : You Can do it Adem -----------------"
hex: $(Project).hex
	@echo "===================================================================="
	@echo "---------------- YARAB Saibni : You Can do it Adem -----------------"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(Project).axf: $(OBJS)
	@echo "------------------------- Object Files -----------------------------"
	$(LD) -T linker_script.ld $^ -o $(OUT_DIR)/$@

$(Project).elf: $(OBJS)
	@echo "------------------------- Linking Files ----------------------------"
	$(LD) -T linker_script.ld $^ -o $(OUT_DIR)/$@

$(Project).bin: $(Project).elf
	@echo "--------------------------- ELF ------------------------------------"
	$(CPY) -O binary $(OUT_DIR)/$< $(OUT_DIR)/$@

$(Project).bin: $(Project).axf
	@echo "--------------------------- AXF ------------------------------------"
	$(CPY) -O binary $(OUT_DIR)/$< $(OUT_DIR)/$@

$(Project).hex: $(Project).elf
	$(CPY) -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$@

$(Project).hex: $(Project).axf
	$(CPY) -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$@


	
clean_all:
	# rm -rf *.o *.elf *.bin *.map *.axf *.hex *.iex
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/*.elf $(OUT_DIR)/*.bin $(OUT_DIR)/*.hex $(OUT_DIR)/*.axf
	@echo "-------------Clear Everything-----------------"


.PHONY: all clean
