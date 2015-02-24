##
## Makefile for  in /home/eax/dev/kcatos
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Wed Nov 26 09:19:58 2014 eax
## Last update Tue Feb 24 18:52:41 2015 
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
		utils/print.c \
		utils/panic_print.c \
		utils/string.c \
		memory/page.c \
		memory/kmalloc.c \
		memory/frame.c \
		process/process.c \
		syscall/syscall_handler.c \
		syscall/syscall.c \
		test/test_kmalloc.c \
		utils/ascii_art.c \
		fs/tar/tar.c \
		initrd/initrd.c

OBJC	= 	$(SRCC:.c=.o)

SRCA	=	boot.s \
		descriptor_tables/gdt_flush.s \
		descriptor_tables/idt_load.s \
		descriptor_tables/idt_gen.s \
		descriptor_tables/pic/init.s \
		descriptor_tables/pic/irq_gen.s \
		utils/usefull_routine.s \
		utils/io.s \
		usermode.s \
		descriptor_tables/tss_flush.s \
		memory/enable_paging.s \
		syscall/syscall_do_call.s

OBJA	=	$(SRCA:.s=.o)

OBJ	=	$(OBJC) $(OBJA)

NAME	=	KCat.Os

ISONAME	=	$(NAME).iso
BOOT_PATH =	iso/boot/
INITRD_NAME =	initrd.tar
INITRD_DATA =	initrd_content/

all: $(NAME) $(BOOT_PATH)/$(INITRD_NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

iso: $(NAME)
	cp $(NAME) $(BOOT_PATH)
	grub-mkrescue  -d /usr/lib/grub/i386-pc  -o $(ISONAME) iso/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BOOT_PATH)/$(NAME)
	$(RM) $(ISONAME)

re: fclean all

$(BOOT_PATH)/$(INITRD_NAME): $(wildcard $(INITRD_DATA)/*)
	tar -cf $(BOOT_PATH)/$(INITRD_NAME) $(INITRD_DATA)/*

run:
	qemu-system-i386 -kernel $(NAME) -initrd $(BOOT_PATH)/$(INITRD_NAME)

run-debug:
	qemu-system-i386 -S -s -kernel $(NAME) -initrd $(BOOT_PATH)/$(INITRD_NAME)

run-iso:
	qemu-system-i386 $(ISONAME)


.PHONY: all clean fclean re iso run run-debug run-iso
