##
## Makefile for  in /home/eax/dev/kcatos/modules/t1
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Mon Feb 23 06:09:39 2015 eax
## Last update Mon Feb 23 06:37:10 2015 eax
##

CC	=	gcc
LD	=	ld

CFLAGS	=	-g -m32 -nostdlib -fPIC -shared -W -Wall -Wextra
LDFLAGS	=	-melf_i386 -fPIC -shared

SRC	=	t1.c
OBJ	=	$(SRC:.c=.o)

NAME	=	t1.kso

DESTDIR	=       ../../initrd_content/
DESTFILE=	$(DESTDIR)$(NAME)

all:	$(NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $(NAME) $(OBJ) 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

load: $(DESTFILE)

$(DESTFILE): $(NAME)
	cp $(NAME) $(DESTFILE)

.PHONY: all clean fclean re load
