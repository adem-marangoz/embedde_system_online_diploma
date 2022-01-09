#Author Adem Alnajjar
#Data   09/01/2022



CC := gcc
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

all:create copy lesson4_lab2_with_make.exe
	rm *.h *.c
	@echo "Removing all header, source files in main directory" 
	@echo "------------Yarab Help Me I Need You----------"

$(PRE_PATH)%.i: $(SRC_PATH)%.c
	@$(CC) -o $@ -E $< $(INC_PATH) 
	@echo "Just Preprocessing source files to I files"

$(ASM_PATH)%.s: $(SRC_PATH)%.c
	@$(CC) -o $@ -S $< $(INC_PATH) 
	@echo "Just assembling source files to assembly files" 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) -o $@ -c $< $(INC_PATH) 
	@echo "Just compiling source files to objects files"


lesson4_lab2_with_make.exe:$(OBJ) $(ASM) $(PRE)
	@$(CC) -o ./Tgt/$@ $(OBJ)


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