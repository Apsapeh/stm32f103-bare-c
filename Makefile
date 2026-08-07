.PHONY: compile clean flash

# CC := arm-none-eabi-gcc
CC      := clang
LD      := ld.lld
OBJCOPY := llvm-objcopy

# CFLAGS := -O2  -mcpu=cortex-m3 -mthumb -nostdlib -fno-builtin -std=c99
CFLAGS  := -O0 -g --target=arm-none-eabi -mcpu=cortex-m3 -mthumb -nostdlib -fno-builtin -std=c99 -Wpedantic -fno-exceptions -fno-unwind-tables
LDFLAGS := -T linker_script.ld

SRC_DIR   := src
BUILD_DIR := build

OBJ_DIR := $(BUILD_DIR)/.obj

# Ok, is bad solution, but I'm too lazy, to set every sub dir
SOURCES := $(shell find $(SRC_DIR) -name "*.c")
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
DEPS    := $(OBJECTS:.o=.d)

$(BUILD_DIR): Makefile
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR): $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

-include $(DEPS)

$(BUILD_DIR)/firmware.elf: $(OBJECTS) linker_script.ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/firmware.bin: $(BUILD_DIR)/firmware.elf
	$(OBJCOPY) -O binary $^ $@

compile: $(BUILD_DIR)/firmware.bin

flash: compile
	st-flash write $(BUILD_DIR)/firmware.bin 0x08000000

probe-rs: compile
	probe-rs run --chip STM32F103C8Tx $(BUILD_DIR)/firmware.elf

clean:
	@rm -rf $(BUILD_DIR)
