CROSS_COMPILE = aarch64-elf-
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

SRC = boot.S exceptions.S switch_context.S kernel.c uart.c memory.c string.c process.c scheduler.c 
OBJ = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRC)))

all: kernel8.img

clean:
	rm -f $(OBJ) kernel.elf kernel8.img

kernel8.img: $(OBJ)
	$(CROSS_COMPILE)ld $(LDFLAGS) $(OBJ) -o kernel.elf
	$(CROSS_COMPILE)objcopy -O binary kernel.elf kernel8.img

%.o: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

run: kernel8.img
	qemu-system-aarch64 -M virt -cpu cortex-a72 -kernel kernel8.img -nographic -d in_asm,exec,int,cpu

