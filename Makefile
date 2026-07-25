.PHONY: build all upload

OBJCOPY = arm-none-eabi-objcopy

CC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=cortex-m3 -mthumb -nostdlib -std=c99
SOURCES = src/main.c src/startup.c
OUT_DIR = out

out:
	mkdir $(OUT_DIR)

$(OUT_DIR)/firmware.elf: out $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -T linker_script.ld -o $(OUT_DIR)/firmware.elf  

$(OUT_DIR)/firmware.bin: $(OUT_DIR)/firmware.elf
	$(OBJCOPY) -O binary $(OUT_DIR)/firmware.elf $(OUT_DIR)/firmware.bin

build: $(OUT_DIR)/firmware.bin

upload: build
	st-flash write $(OUT_DIR)/firmware.bin 0x08000000

all: upload
