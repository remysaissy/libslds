/*
 * This file is part of ExAmour libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include	<list.h>

/* Double linked list implementation. */

void		_dlist_init(void *dlist, int m)
{
  if (dlist)
    {
      GET_FIELD(dlist, m, dlist_t)->prev = 0;
      GET_FIELD(dlist, m, dlist_t)->next = 0;
    }
}

void		_dlist_add_head(void **head, void *new, int m)
{
  if (!head)
    return;
  GET_FIELD(new, m, dlist_t)->prev = 0;
  GET_FIELD(new, m, dlist_t)->next = *head;
  if (*head)
    GET_FIELD(*head, m, dlist_t)->prev = new;
  *head = new;
}

void		_dlist_add_after(void **head, void *dlist, void *new, int m)
{
  if (!head)
    return;
  if (dlist)
    {
      GET_FIELD(new, m, dlist_t)->next = GET_FIELD(dlist, m, dlist_t)->next;
      GET_FIELD(new, m, dlist_t)->prev = dlist;
      if (GET_FIELD(dlist, m, dlist_t)->next)
	GET_FIELD(GET_FIELD(dlist, m, dlist_t)->next, m, dlist_t)->prev = new;
      GET_FIELD(dlist, m, dlist_t)->next = new;
    }
  else
    {
      if (*head)
	{
	  GET_FIELD(new, m, dlist_t)->next = GET_FIELD(*head, m, dlist_t)->next;
	  GET_FIELD(new, m, dlist_t)->prev = *head;
	  if (GET_FIELD(*head, m, dlist_t)->next)
	    GET_FIELD(GET_FIELD(*head, m, dlist_t)->next, m, dlist_t)->prev = new;
	  GET_FIELD(*head, m, dlist_t)->next = new;
	}
      else
	{
	  GET_FIELD(new, m, dlist_t)->next = 0;
	  GET_FIELD(new, m, dlist_t)->prev = 0;
	  *head = new;
	}
    }
}

void		_dlist_add_before(void **head, void *dlist, void *new, int m)
{
  if (!head)
    return;
  if (dlist)
    {
      GET_FIELD(new, m, dlist_t)->next = dlist;
      GET_FIELD(new, m, dlist_t)->prev = GET_FIELD(dlist, m, dlist_t)->prev;
      if (GET_FIELD(dlist, m, dlist_t)->prev)
	GET_FIELD(GET_FIELD(dlist, m, dlist_t)->prev, m, dlist_t)->next = new;
      GET_FIELD(dlist, m, dlist_t)->prev = new;
      if (dlist == *head)
	*head = new;
    }
  else
    {
      if (*head)
	{
	  GET_FIELD(new, m, dlist_t)->next = *head;
	  GET_FIELD(new, m, dlist_t)->prev = 0;
	  GET_FIELD(*head, m, dlist_t)->prev = new;
	  *head = new;
	}
      else
	{
	  GET_FIELD(new, m, dlist_t)->next = 0;
	  GET_FIELD(new, m, dlist_t)->prev = 0;
	  *head = new;
	}
    }
}

void		_dlist_remove(void **head, void *dlist, int m)
{
  if (!head)
    return;
  if (*head && dlist)
    {
      if (GET_FIELD(dlist, m, dlist_t)->prev == 0 &&
	  GET_FIELD(dlist, m, dlist_t)->next == 0 &&
	  *head == dlist)
	*head = 0;
      else
	{
	  if (GET_FIELD(dlist, m, dlist_t)->prev)
	    {
	      GET_FIELD(GET_FIELD(dlist, m, dlist_t)->prev, m, dlist_t)->next =
		GET_FIELD(dlist, m, dlist_t)->next;
	    }
	  if (GET_FIELD(dlist, m, dlist_t)->next)
	    {
	      if (dlist == *head)
		{
		  *head = GET_FIELD(dlist, m, dlist_t)->next;
		  if (*head)
		    GET_FIELD(*head, m, dlist_t)->prev = 0;
		}
	      else
		{
		  GET_FIELD(GET_FIELD(dlist, m, dlist_t)->next, m, dlist_t)->prev =
		    GET_FIELD(dlist, m, dlist_t)->prev;
		}
	    }
	}
    }
}
