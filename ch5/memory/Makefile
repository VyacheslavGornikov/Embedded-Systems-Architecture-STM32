CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy

MODEL = f446re
LD_TARGET = $(MODEL).ld

# Флаги компиляции
CFLAGS = -mthumb -mcpu=cortex-m4 -g -ggdb -Wall -Wextra -Wno-main -Wno-unused -ffreestanding #-nostdlib -DOWN_MALLOC

# Флаги линковки
LDFLAGS = -T $(LD_TARGET) -Wl,-gc-sections -Wl,-Map=image.map -nostartfiles -mthumb -mcpu=cortex-m4

# Объектные файлы (линкер-скрипт НЕ включаем в OBJS)
OBJS = startup_$(MODEL).o main.o malloc.o

all: image.bin

image.bin: image.elf
	$(OBJCOPY) -O binary $^ $@

# Линкер-скрипт указываем только через -T, но НЕ в $^
image.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

rebuild: clean all

clean:
	rm -rf *.bin *.elf *.map *.o

.PHONY: all rebuild clean