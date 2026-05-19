CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

MODEL = f446re
LD_TARGET = $(MODEL).ld

# Флаги компиляции для Cortex-M4
CFLAGS = -mthumb -mcpu=cortex-m4 -g -ggdb -Wall -Wextra -Wno-main -DOWN_MALLOC

# Флаги линковки
LDFLAGS = -T $(LD_TARGET) -gc-sections -nostdlib -Map=image.map

# Объектные файлы
OBJS = startup_$(MODEL).o main.o malloc.o

all: image.bin

image.bin: image.elf
	$(OBJCOPY) -O binary $^ $@

image.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

rebuild: clean all

clean:
	rm -rf image.bin image.elf image.map *.o

.PHONY: all rebuild clean