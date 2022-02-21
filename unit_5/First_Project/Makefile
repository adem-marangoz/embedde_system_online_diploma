#Author Adem Alnajjar
#Data   09/01/2022



CC := arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
RM := rm

.PHONY: $(TARGET)
.PHONY: clean

#folders Names
SRCDIR = Src
INCDIR = Inc
OBJDIR = Obj
EXEDIR = Tgt
ASMDIR = Asm
PREDIR = Pre
TARGET := exe


VPATH:= ./Src/ ./Obj/ ./Inc/



#Paths
Project	 :=learn_embedded
SRC_PATH :=./Src/
INC_PATH :=-I ./$(INCDIR)/
OBJ_PATH :=./$(OBJDIR)/
EXE_PATH :=./$(EXEDIR)/
ASM_PATH :=./$(ASMDIR)/
PRE_PATH :=./$(PREDIR)/


#detect all soruce and header files
SRC := $(wildcard *.c)
INC := $(wildcard *.h)
ASMC := $(SRC:.c=.s)
OBJC := $(SRC:.c=.o)
PREC := $(SRC:.c=.i)


OBJ := $(patsubst %,$(OBJ_PATH)%,$(OBJC))
ASM := $(patsubst %,$(ASM_PATH)%,$(ASMC))
PRE := $(patsubst %,$(PRE_PATH)%,$(PREC))
EXE := $(patsubst %,$(EXE_PATH)%,"lesson4_lab2_with_make.exe")

all:create copy $(Project).bin
	rm *.h *.c
	@echo "Removing all header, source files in main directory" 
	@echo "------------Yarab Help Me I Need You----------"

$(PRE_PATH)%.i: $(SRC_PATH)%.c
	@echo "-------- start -------- Just Preprocessing source files to I files"
	$(CC)gcc.exe -o $@ -E $< $(INC_PATH) 
	@echo "Just Preprocessing source files to I files"

$(ASM_PATH)%.s: $(SRC_PATH)%.c
	@echo "-------- start -------- Just assembling source files to assembly files" 
	$(CC)gcc.exe -o $@ -S $< $(INC_PATH) 
	@echo "Just assembling source files to assembly files" 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "-------- start -------- Just compiling source files to objects files"
	$(CC)gcc.exe -c $(CFLAGS) $(INC_PATH) $< -o $@ 
	@echo "Just compiling source files to objects files"

$(Project).elf: $(OBJ) $(ASM) $(PRE)
	@echo "-------- start -------- Elf file it created"
	$(CC)ld.exe -T linker_script.ld $(OBJ) -o $(EXE_PATH)$@ -Map=map_file.map
	@echo "Elf file it created"

$(Project).bin:$(Project).elf 
	$(CC)objcopy.exe -O binary $(EXE_PATH)$< $(EXE_PATH)$@


#Copy files from current directory to distention
copy:
	cp -r $(SRC) $(SRCDIR)
	cp -r $(INC) $(INCDIR)
	@echo "copy header and source files is done"
	

#Create folders
create:
	mkdir -p $(SRCDIR)
	mkdir -p $(INCDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(EXEDIR)
	mkdir -p $(ASMDIR)
	mkdir -p $(PREDIR)
	@echo "Create folders is done"

clean:
	rm -rf *.elf *.bin *.o *.map