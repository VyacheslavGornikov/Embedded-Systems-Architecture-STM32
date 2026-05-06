CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
MODEL = f446re
LD_TARGET = $(MODEL).ld
OBJCOPY = $(CROSS_COMPILE)objcopy
CFLAGS = -mthumb -mcpu=cortex-m3 -g -ggdb -Wall -Wno-main
LDFLAGS = -T $(LD_TARGET) -gc-sections -nostdlib -Map=image.map

all: image.bin

image.bin: image.elf
	$(OBJCOPY) -O binary $^ $@

image.elf: startup_$(MODEL).o $(LD_TARGET)
	$(LD) $(LDFLAGS) startup_$(MODEL).o -o $@

startup_$(MODEL).o: startup_$(MODEL).c

clean:
	rm -rf image.bin image.elf image.map *.o