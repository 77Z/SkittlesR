# SkittlesR-i386-x86 Makefile

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Change version, compiler, assembler, and linker info in config.mk
include config.mk

# ifeq ($(SKITTLESENV), "yes")
# 	@echo "Skittles Development Environment Detected!"
# else
# 	@echo "WARNING SKITTLES DEV ENVIRONMENT WASN'T DETECTED,"
# 	@echo "THE BUILD MAY FAIL. DID YOU SET IT UP CORRECTLY?"
# endif

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c modules/*.c filesystem/*.c)
HEADERS   = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h modules/*.h filesystem/*.h)
# File extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CFLAGS = -ffreestanding -Wall -Wextra -fno-exceptions -m32 -DVERSION=\"$(SKITVER)\"

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral.
kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

run: os-image.bin
	qemu-system-i386 -fda $< -serial stdio

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o programs/*.o filesystem/*.o