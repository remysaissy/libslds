##
## This file is part of ExAmour toolkit

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

OUTPUT		=	tester

find_csources   = 	$(wildcard $(subdir)/*.c)

SRC		:= 	$(foreach subdir,.,$(find_csources))
OBJS		:= 	$(SRC:.c=.o)

LIBS		=	../libslds.a

CFLAGS		=	-I../include

CC		=	gcc

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT):
	make EXTRA_CFLAGS='-D__LIBSLDS_UNIT_TESTING__' -C ../ re
	make build


build:	$(OBJS)
	@$(CC) -o $(OUTPUT) $(LDFLAGS) $(OBJS) $(LIBS)
	@echo	"[MK] $(OUTPUT)."

clean:
	@rm -f $(OBJS)
	@echo	"[RM] $(OBJS)."

fclean:	clean
	@rm -f $(OUTPUT) *~ \#*
	@echo	"[RM] $(OUTPUT)."

re:	fclean $(OUTPUT)



