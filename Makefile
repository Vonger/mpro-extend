NAME = x
CROSS_COMPILE = arm-none-eabi-

INCLUDE = . ./include
SOURCE  = . ./lib

LVGL_PATH ?= ${shell pwd}/lvgl
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}

INC := $(patsubst %, -I %, $(INCLUDE))
INC += "-I$(LVGL_PATH)"
LIB := $(patsubst %, -L %, $(LIBRARY))
LIB += -lgcc

AS = $(CROSS_COMPILE)gcc -x assembler-with-cpp
CC = $(CROSS_COMPILE)gcc
OC = $(CROSS_COMPILE)objcopy
OD = $(CROSS_COMPILE)objdump

MFLAGS = -march=armv5te -mtune=arm926ej-s -mfloat-abi=soft -marm -mno-thumb-interwork \
        -g -Wall -O2 -fdata-sections -ffunction-sections -ffreestanding \
        -D__ARM32_ARCH__=5 -D__ARM926EJS__ -DENABLE_LVGL_ROTATE
AFLAGS = $(MFLAGS) 
CFLAGS = $(MFLAGS) -fomit-frame-pointer -Wall -fverbose-asm
LFLAGS = -T link.ld -nostdlib -Wl,-gc-sections -pie

all: $(NAME)

SFILES := $(foreach dir, $(SOURCE), $(wildcard $(dir)/*.S))
SOBJS  := $(patsubst %, %, $(SFILES:.S=.o))
$(SOBJS) : %.o : %.S
	@echo [AS] $<
	@$(AS) $(AFLAGS) $(INC) -c $< -o $@

CFILES := $(foreach dir, $(SOURCE), $(wildcard $(dir)/*.c))
CFILES += $(shell find $(LVGL_PATH)/src -type f -name '*.c')
CFILES += $(shell find $(LVGL_PATH)/demos -type f -name '*.c')
COBJS  := $(patsubst %, %, $(CFILES:.c=.o))
$(COBJS) : %.o : %.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	
$(NAME): $(COBJS) $(SOBJS)
	@echo [LD] Link $@
	@$(CC) $(LFLAGS) -Wl,--cref,-Map=$@.map $^ -o $@.elf $(LIB)
	@echo [OC] Object copy $@.bin
	@$(OC) -v -O binary $@.elf $@.bin > /dev/null

.PHONY: bin
bin:
	@echo [MAKE] extend_combine
	@gcc ./misc/extend_combine.c -o extend_combine
	@if [ -z "$(wildcard x.bin)" ]; then \
		echo "ERROR: x.bin not exists, please call make."; \
		exit 1; \
	fi

	@rm -rf x.bin.lzma
	@cp x.bin x.bin.bak
	@if [ -z "$(wildcard MPRO.bin)" ]; then \
		echo "ERROR: MPRO.bin not exists, please rename firmware as MPRO.bin and put to this folder."; \
		exit 1; \
	else \
		$(PWD)/extend_combine MPRO.bin x.bin; \
		echo "NOTE: Please use 'mprotool upgrade MPRO.output.bin' or v2scrctl upgrade your screen."; \
	fi
	@mv x.bin.bak x.bin

.PHONY: clean
clean:
	rm -rf *.o ./lib/*.o* *.lst *.map *.elf
	find lvgl -name *.o | xargs rm -f
