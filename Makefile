##
## Makefile for  in /home/eax/dev/kcatos
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Wed Nov 26 09:19:58 2014 eax
## Last update Mon Mar 23 14:59:31 2015 eax
##

CC      =	gcc
ASM	=	nasm
LD	=	ld

CFLAGS	+=	-m32 -std=gnu99 -g -ffreestanding -Wall -Wextra -I.
LDFLAGS	=	-melf_i386 -T linker.ld -nostdlib
ASMFLAGS=	-f elf32

SRCC	=	kernel.c \
		descriptor_tables/gdt.c \
		descriptor_tables/descriptor_tables.c \
		descriptor_tables/idt_setup.c \
		descriptor_tables/idt_handler.c \
		descriptor_tables/pic/irq_handler.c \
		descriptor_tables/pic/pit.c \
		descriptor_tables/pic/keyboard.c \
		descriptor_tables/pic/keyboard_conv.c \
		utils/print.c \
		utils/panic_print.c \
		utils/string.c \
		memory/page.c \
		memory/kmalloc.c \
		memory/frame.c \
		process/process.c \
		syscall/syscall_handler.c \
		syscall/syscall.c \
		syscall/read.c \
		test/test_kmalloc.c \
		utils/ascii_art.c \
		fs/tar/tar.c \
		initrd/initrd.c \
		elf/elf.c \
		utils/error.c \
		kmodule/kmodule.c \
		elf/kern_parse.c \
		fpu/init_fpu.c

OBJC	= 	$(SRCC:.c=.o)

SRCA	=	boot.s \
		descriptor_tables/gdt_flush.s \
		descriptor_tables/idt_load.s \
		descriptor_tables/idt_gen.s \
		descriptor_tables/pic/init.s \
		descriptor_tables/pic/irq_gen.s \
		descriptor_tables/pic/pit_inc.s \
		utils/routines.s \
		utils/usefull_routine.s \
		utils/io.s \
		usermode.s \
		descriptor_tables/tss_flush.s \
		memory/enable_paging.s \
		syscall/syscall_do_call.s \
		fpu/init_sse.s

OBJA	=	$(SRCA:.s=.o)

OBJ	=	$(OBJA) $(OBJC)

NAME	=	KCat.Os

ISONAME	=	$(NAME).iso
BOOT_PATH =	iso/boot/
INITRD_NAME =	initrd.tar
INITRD_FILE =	$(BOOT_PATH)$(INITRD_NAME)
INITRD_DATA =	initrd_content/

all: $(NAME)

$(NAME): $(OBJ) modules $(INITRD_FILE)
	$(LD) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

iso: $(ISONAME)

$(ISONAME): $(NAME)
	cp $(NAME) $(BOOT_PATH)
	grub-mkrescue  -d /usr/lib/grub/i386-pc  -o $(ISONAME) iso/

$(INITRD_FILE): $(wildcard $(INITRD_DATA)/*)
	tar --transform="s#$(INITRD_DATA)/##g" -cf $(INITRD_FILE) --add-file $(INITRD_DATA)/*

modules: $(INITRD_DATA)
	make -C modules/ load

$(INITRD_DATA):
	mkdir -p $(INITRD_DATA)

clean:
	$(RM) $(OBJ)
	make -C modules/ clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BOOT_PATH)/$(NAME)
	$(RM) $(ISONAME)
	$(RM) $(BOOT_PATH)/$(INITRD_NAME)
	make -C modules/ fclean

re: fclean all

run: $(ISONAME)
	qemu-system-i386 $(ISONAME)

run-debug: $(ISONAME)
	qemu-system-i386 -S -s $(ISONAME)


.PHONY: all clean fclean re iso run modules
