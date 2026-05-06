CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
MODEL = f446re
LD_TARGET = $(MODEL).ld
OBJCOPY = $(CROSS_COMPILE)objcopy
CFLAGS = -mthumb -mcpu=cortex-m4 -g -ggdb -Wall -Wno-main
LDFLAGS = -gc-sections -nostdlib

all: image.bin

image.bin: bootloader.bin app.bin
	cat bootloader.bin app.bin > $@

app.bin: app.elf
	$(OBJCOPY) -O binary $< $@

bootloader.bin: bootloader.elf
	$(OBJCOPY) -O binary --pad-to=0x4000 $< $@

app.elf: startup_$(MODEL).o app.ld
	$(LD) $(LDFLAGS) -T app.ld startup_$(MODEL).o -o $@ -Map=app.map

bootloader.elf: startup_$(MODEL)_bl.o utils.o bootloader.ld
	$(LD) $(LDFLAGS) -T bootloader.ld startup_$(MODEL)_bl.o utils.o -o $@ -Map=bootloader.map

startup_$(MODEL)_bl.o: CFLAGS += -DBOOTLOADER

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild:
	make clean
	make

clean:
	rm -rf *.bin *.elf *.map *.o
