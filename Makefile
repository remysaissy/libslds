##
## This file is part of ExAmour libslds

## Copyright (C) Remy Saissy <remy.saissy@gmail.com>
## ExAmour toolkit is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## ExAmour toolkit is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

OUTPUT		=	libslds.a

find_csources   = 	$(wildcard $(subdir)/*.c)

LIST_SRC	:= 	$(foreach subdir,list,$(find_csources))
LIST_OBJS	:= 	$(LIST_SRC:.c=.o)

HASH_SRC	:= 	$(foreach subdir,hash,$(find_csources))
HASH_OBJS	:= 	$(HASH_SRC:.c=.o)

TREE_SRC	:= 	$(foreach subdir,tree,$(find_csources))
TREE_OBJS	:= 	$(TREE_SRC:.c=.o)

CFLAGS		=	-Iinclude -O2

CFLAGS		+=	$(EXTRA_CFLAGS)

CC		=	gcc

AR		=	ar

AR_FLAGS	=	rcs

RANLIB		=	ranlib

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

build: $(LIST_OBJS) $(HASH_OBJS) $(TREE_OBJS)
	@$(AR) $(AR_FLAGS) $(OUTPUT) $(LIST_OBJS) $(HASH_OBJS) $(TREE_OBJS)
	@$(RANLIB) $(OUTPUT)
	@echo	"[Build] $(OUTPUT)."

fclean:
	@find -type f -name '*~' -o -name '#*' -o -name '*.o'  | xargs rm -f
	@rm -rf $(LIST_OBJS) $(HASH_OBJS) $(TREE_OBJS)
	@echo	"[Clean] All completed."

re:	fclean build

test:
	make -C tests
	./tests/tester
