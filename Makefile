##
## Makefile for  in /home/eax/dev/kcatos
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Wed Nov 26 09:19:58 2014 eax
## Last update Tue Dec 16 12:29:41 2014 
##

CC      =	gcc
ASM	=	nasm
LD	=	ld

CFLAGS	=	-m32 -std=gnu99 -ffreestanding -Wall -Wextra
LDFLAGS	=	-melf_i386 -T linker.ld -nostdlib
ASMFLAGS=	-f elf32

SRCC	=	kernel.c \
		descriptor_tables/gdt.c \
		descriptor_tables/descriptor_tables.c \
		descriptor_tables/idt_setup.c \
		descriptor_tables/idt_handler.c \
		utils/Print.c \
		utils/panic_print.c

OBJC	= 	$(SRCC:.c=.o)

SRCA	=	boot.s \
		descriptor_tables/gdt_flush.s \
		descriptor_tables/idt_load.s \
		descriptor_tables/idt_gen.s

OBJA	=	$(SRCA:.s=.o)

OBJ	=	$(OBJC) $(OBJA)

NAME	=	KCat.Os

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
