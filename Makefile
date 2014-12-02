##
## Makefile for  in /home/eax/dev/kcatos
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Wed Nov 26 09:19:58 2014 eax
## Last update Tue Dec  2 14:49:10 2014 eax
##

CC      =	gcc
ASM	=	nasm
LD	=	ld

CFLAGS	=	-m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS	=	-melf_i386 -T linker.ld -nostdlib
ASMFLAGS=	-f elf32

SRCC	=	kernel.c
OBJC	= 	$(SRCC:.c=.o)

SRCA	=	boot.s
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
