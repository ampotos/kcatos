##
## Makefile for  in /home/eax/dev/kcatos/modules
## 
## Made by eax
## Login   <soules_k@epitech.net>
## 
## Started on  Mon Feb 23 06:13:36 2015 eax
## Last update Mon Feb 23 06:27:37 2015 eax
##

MODULES	=	$(shell find . -maxdepth 1 -type d -not -name ".")

all:
	@for l in $(MODULES); do make -C $$l; done

clean:
	@for l in $(MODULES); do make -C $$l clean; done

fclean:
	@for l in $(MODULES); do make -C $$l fclean; done

re:
	@for l in $(MODULES); do make -C $$l re; done

load:
	@for l in $(MODULES); do make -C $$l load; done
