/*
 * This file is part of ExAmour toolkit

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

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdbool.h>

#include	<list.h>

typedef struct	list_test_s
{
  slist_t	slist;
  stack_t	stack;
  dlist_t	dlist;
  clist_t	clist;
  queue_t	queue;

}		list_test_t;


bool	slist_test(void)
{
  list_test_t	*root = NULL;
  list_test_t	elem;
  list_test_t	elem2;

  slist_init(root, slist);
  slist_add_head(root, &elem, slist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in slist_add_head.\n");
      return (false);
    }
  slist_add_after(root, &elem, &elem2, slist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in slist_add_after.\n");
      return (false);
    }
  slist_remove(root, root, slist);
  if (root != (void *)&elem2)
    {
      fprintf(stderr, "Error in slist_remove.\n");
      return (false);
    }
  slist_remove(root, root, slist);
  if (root != NULL)
    {
      fprintf(stderr, "Error in slist_remove.\n");
      return (false);
    }
  slist_remove(root, root, slist);
  printf("Single linked list... [OK].\n");
  return (true);
}

bool	stack_test(void)
{
  list_test_t	*root = NULL;
  list_test_t	elem;
  list_test_t	elem2;

  stack_init(root, stack);
  stack_push(root, &elem, stack);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in stack_push.\n");
      return (false);
    }
  stack_push(root, &elem2, stack);
  if (root != (void *)&elem2)
    {
      fprintf(stderr, "Error in stack_push.\n");
      return (false);
    }
  if ((void *)stack_pop(root, stack) != (void *)&elem2)
    {
      fprintf(stderr, "Error in stack_pop().\n");
      return (false);
    }
  stack_pop(root, stack);
  if (root != NULL)
    {
      fprintf(stderr, "Error in stack_pop.\n");
      return (false);
    }
  stack_pop(root, stack);
  printf("Stack list... [OK].\n");
  return (true);
}

bool	dlist_test(void)
{
  list_test_t	*root = NULL;
  list_test_t	elem;
  list_test_t	elem2;
  list_test_t	elem3;

  dlist_init(root, dlist);
  dlist_add_head(root, &elem, dlist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in dlist_add_head.\n");
      return (false);
    }
  dlist_add_after(root, &elem, &elem2, dlist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in dlist_add_after.\n");
      return (false);
    }
  dlist_add_before(root, &elem, &elem3, dlist);
  if (root != (void *)&elem3)
    {
      fprintf(stderr, "Error in dlist_add_before.\n");
      return (false);
    }
  dlist_remove(root, root, dlist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in dlist_remove.\n");
      return (false);
    }
  dlist_remove(root, root, dlist);
  if (root != (void *)&elem2)
    {
      fprintf(stderr, "Error in dlist_remove.\n");
      return (false);
    }
  dlist_remove(root, root, dlist);
  if (root != NULL)
    {
      fprintf(stderr, "Error in dlist_remove.\n");
      return (false);
    }
  dlist_remove(root, root, dlist);
  printf("Double linked list... [OK].\n");
  return (true);
}

bool	clist_test(void)
{
  list_test_t	*root = NULL;
  list_test_t	elem;
  list_test_t	elem2;
  list_test_t	elem3;

  clist_init(root, clist);
  clist_add_after(root, &elem, clist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in clist_add_after.\n");
      return (false);
    }
  clist_add_after(root, &elem2, clist);
  if (root != (void *)&elem)
    {
      fprintf(stderr, "Error in clist_add_after.\n");
      return (false);
    }
  clist_add_before(root, &elem3, clist);
  if (root->clist.prev != (void *)&elem3)
    {
      fprintf(stderr, "Error in clist_add_before.\n");
      return (false);
    }
  clist_remove(root, root, clist);
  if (root != (void *)&elem2)
    {
      fprintf(stderr, "Error in clist_remove.\n");
      return (false);
    }
  clist_remove(root, root, clist);
  if (root != (void *)&elem3)
    {
      fprintf(stderr, "Error in clist_remove.\n");
      return (false);
    }
  clist_remove(root, root, clist);
  if (root != NULL)
    {
      fprintf(stderr, "Error in clist_remove.\n");
      return (false);
    }
  clist_remove(root, root, clist);
  printf("Circular list... [OK].\n");
  return (true);
}

static bool	queue_test(void)
{
  list_test_t	*root = NULL;
  list_test_t	elem;
  list_test_t	elem2;
  list_test_t	elem3;

  queue_init(root, queue);
  queue_add(root, &elem, queue);
  if (root != &elem)
    {
      fprintf(stderr, "Error in queue_add.\n");
      return (false);
    }
  queue_add(root, &elem2, queue);
  if (root != &elem2)
    {
      fprintf(stderr, "Error in queue_add.\n");
      return (false);
    }
  queue_add(root, &elem3, queue);
  if (root != &elem3)
    {
      fprintf(stderr, "Error in queue_add.\n");
      return (false);
    }
  if ((void *)queue_remove(root, queue) != (void *)&elem)
    {
      fprintf(stderr, "Error in queue_remove().\n");
      return (false);
    }
  if ((void *)queue_remove(root, queue) != (void *)&elem2)
    {
      fprintf(stderr, "Error in queue_remove().\n");
      return (false);
    }
  if ((void *)queue_remove(root, queue) != (void *)&elem3)
    {
      fprintf(stderr, "Error in queue_remove().\n");
      return (false);
    }
  queue_remove(root, queue);
  printf("Queue list... [OK].\n");
  return (true);
}

bool	do_lists(void)
{
  if (slist_test() == false)
    return (false);
  if (stack_test() == false)
    return (false);
  if (dlist_test() == false)
    return (false);
  if (clist_test() == false)
    return (false);
  if (queue_test() == false)
    return (false);
  return (true);
}

