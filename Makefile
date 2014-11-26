##
## Makefile for  in /home/eax/dev/kcatos
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Wed Nov 26 09:19:58 2014 eax
## Last update Wed Nov 26 09:41:51 2014 eax
##

CC	=	i686-elf-gcc
ASM	=	i686-elf-as

CFLAGS	=	-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS	=	-T linker.ld -nostdlib

SRCC	=	kernel.c
OBJC	= 	$(SRCC:.c=.o)

SRCA	=	boot.s
OBJA	=	$(SRCA:.s=.o)

OBJ	=	$(OBJC) $(OBJA)

NAME	=	KCat.Os

$(NAME): all

all: $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.s
	$(ASM) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
