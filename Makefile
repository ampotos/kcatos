##
## Makefile for  in /home/eax/dev/kcatos
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Wed Nov 26 09:19:58 2014 eax
## Last update Tue Feb 10 14:04:29 2015 eax
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
		utils/print.c \
		utils/panic_print.c \
		utils/string.c \
		memory/page.c \
		memory/kmalloc.c \
		memory/frame.c \
		process/process.c \
		syscall/syscall_handler.c \
		syscall/syscall.c

OBJC	= 	$(SRCC:.c=.o)

SRCA	=	boot.s \
		descriptor_tables/gdt_flush.s \
		descriptor_tables/idt_load.s \
		descriptor_tables/idt_gen.s \
		utils/usefull_routine.s \
		usermode.s \
		descriptor_tables/tss_flush.s

OBJA	=	$(SRCA:.s=.o)

OBJ	=	$(OBJC) $(OBJA)

NAME	=	KCat.Os
ISONAME	=	$(NAME).iso

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

iso: $(NAME)
	cp $(NAME) iso/boot/
	grub-mkrescue  -d /usr/lib/grub/i386-pc  -o $(ISONAME) iso/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) iso/boot/$(NAME)
	$(RM) $(ISONAME)

re: fclean all

.PHONY: all clean fclean re iso
