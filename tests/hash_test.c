/*
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include	<hash.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>
#include	<stdbool.h>

typedef struct elem_s
{
  hashtable_t	entry;
  int		key;

}		elem_t;

typedef struct	test_s
{
  elem_t	*table[256];

}		test_t;

/* Callback functions. */

static unsigned int	HASHING_FUNCTION(void *key)
{
  unsigned int	*p = (unsigned int *)&key;

/*   printf("Hasing function callback...\n"); */
  return (*p % 256);
}

static unsigned int	HASHING_COMPARE(void *key, void *it)
{
  unsigned int	*p = (unsigned int *)&key;
  elem_t	*elem = (elem_t *)it;

/*   printf("Hashing comparison callback...\n"); */
  return (*p - elem->key);
}


static bool	hashtable_init_test(void)
{
  test_t	test;

  if (hashtable_init(NULL, 1) == true)
    {
      fprintf(stderr, "hashtable_init(NULL, 1).\n");
      return (false);
    }
  if (hashtable_init(test.table, 0) == true)
    {
      fprintf(stderr, "hashtable_init(test.table, 0).\n");
      return (false);
    }
  if (hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])) == false)
    {
      fprintf(stderr, "hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])).\n");
      return (false);
    }
  return (true);
}

static bool	hashtable_insert_test(void)
{
  test_t	test;
  elem_t	elem;
  elem_t	elem2;

  if (hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])) == false)
    {
      fprintf(stderr, "hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])).\n");
      return (false);
    }
  if (hashtable_insert(test.table, elem2.key, &elem2, entry, NULL) == true)
    {
      fprintf(stderr, "hashtable_insert(test.table, elem2.key, &elem2, entry, NULL).\n");
      return (false);
    }
  if (hashtable_insert(test.table, elem2.key, NULL, entry, HASHING_FUNCTION) == true)
    {
      fprintf(stderr, "hashtable_insert(test.table, elem2.key, NULL, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  if (_hashtable_insert(NULL, elem2.key, &elem2, 0, HASHING_FUNCTION) == true)
    {
      fprintf(stderr, "hashtable_insert(NULL, elem2.key, &elem2, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  return (true);
}

static bool	hashtable_lookup_test(void)
{
  test_t	test;
  elem_t	elem;
  elem_t	elem2;
  elem_t	*p;

  if (hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])) == false)
    {
      fprintf(stderr, "hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])).\n");
      return (false);
    }
  elem.key = 42;
  if (hashtable_insert(test.table, elem.key, &elem, entry, HASHING_FUNCTION) == false)
    {
      fprintf(stderr, "hashtable_insert(test.table, elem.key, &elem, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  elem2.key = 43;
  if (hashtable_insert(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION) == false)
    {
      fprintf(stderr, "hashtable_insert(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  if (hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, NULL))
    {
      fprintf(stderr, "hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, NULL).\n");
      return (false);
    }
  if (hashtable_lookup(test.table, elem2.key, entry, NULL, HASHING_COMPARE))
    {
      fprintf(stderr, "hashtable_lookup(test.table, elem2.key, entry, NULL, HASHING_COMPARE).\n");
      return (false);
    }
  if (_hashtable_lookup(NULL, elem2.key, 0, HASHING_FUNCTION, HASHING_COMPARE))
    {
      fprintf(stderr, "hashtable_lookup(NULL, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE).\n");
      return (false);
    }
  p = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  if (!p || p->key != elem2.key)
    {
      printf("hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE): no key %d!\n.", elem2.key);
      return (false);
    }
  p = hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  if (!p || p->key != elem.key)
    {
      printf("hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE): no key %d!\n.", elem.key);
      return (false);
    }
  return (true);
}

static bool	hashtable_remove_test(void)
{
  test_t	test;
  elem_t	elem;
  elem_t	elem2;
  elem_t	*p;

  if (hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])) == false)
    {
      fprintf(stderr, "hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])).\n");
      return (false);
    }
  elem.key = 42;
  if (hashtable_insert(test.table, elem.key, &elem, entry, HASHING_FUNCTION) == false)
    {
      fprintf(stderr, "hashtable_insert(test.table, elem.key, &elem, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  elem2.key = 43;
  if (hashtable_insert(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION) == false)
    {
      fprintf(stderr, "hashtable_insert(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  p = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  if (!p || p->key != elem2.key)
    {
      printf("hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE): no key %d!\n.", elem2.key);
      return (false);
    }
  p = hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  if (!p || p->key != elem.key)
    {
      printf("hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE): no key %d!\n.", elem.key);
      return (false);
    }
  if (hashtable_remove(test.table, elem2.key, &elem2, entry, NULL) == true)
    {
      fprintf(stderr, "hashtable_remove(test.table, elem2.key, &elem2, entry, NULL).\n");
      return (false);
    }
  if (hashtable_remove(test.table, elem2.key, NULL, entry, HASHING_FUNCTION) == true)
    {
      fprintf(stderr, "hashtable_remove(test.table, elem2.key, NULL, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  if (hashtable_remove(test.table, 12, &elem2, entry, HASHING_FUNCTION) == true)
    {
      fprintf(stderr, "hashtable_remove(test.table, 12, &elem2, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  if (_hashtable_remove(NULL, elem2.key, &elem2, 0, HASHING_FUNCTION) == true)
    {
      fprintf(stderr, "hashtable_remove(NULL, elem2.key, &elem2, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  if (hashtable_remove(test.table, elem.key, &elem, entry, HASHING_FUNCTION) == false)
    {
      fprintf(stderr, "hashtable_remove(test.table, elem.key, &elem, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  if (hashtable_remove(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION) == false)
    {
      fprintf(stderr, "hashtable_remove(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION).\n");
      return (false);
    }
  p = hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  if (p)
    {
      printf("hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE): key found after a remove %d!\n.", elem.key);
      return (false);
    }
  p = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  if (p)
    {
      printf("hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE): key found after a remove %d!\n.", elem2.key);
      return (false);
    }
  return (true);
}


static	void	interactive_tests(void)
{
  test_t	test;
  int		val;
  elem_t	*elem;

  if (hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0])) == false)
    return;
  while (1)
    {
      putchar('>');
      scanf("%d", &val);
      if (val == 0)
	{
	  int	i;
	  elem_t	*p;

	  printf("Dumping the table.\n");
	  for (i = 0; i < 256; i++)
	    {
	      p = test.table[i];
	      if (p)
		{
		  printf("[%d]:\n", i);
		  while (p)
		    {
		      printf("\tentry: %p key: %d\n", p, p->key);
		      p = p->entry.next;
		    }
		}
	    }
	  printf("End of dump.\n");
	}
      else
	{
	  if (val > 0)
	    {
	      elem = malloc(sizeof(*elem));
	      elem->key = val;
	      hashtable_insert(test.table, elem->key, elem, entry, HASHING_FUNCTION);
	      val = 0;
	      printf("Added.\n");
	    }
	  else
	    {
	      elem = hashtable_lookup(test.table, -val, entry, HASHING_FUNCTION, HASHING_COMPARE);
	      if (elem)
		{
		  printf("About to kick %d out.\n", elem->key);
		  hashtable_remove(test.table, -val, elem, entry, HASHING_FUNCTION);
		  free(elem);
		}
	    }
	}
    }
}

bool	do_hashs(void)
{
  if (hashtable_init_test() == true)
    printf("Hashtable init.....[OK].\n");
  else
    {
      printf("Hashtable.....[FAILED].\n");
      return (false);
    }
  if (hashtable_insert_test() == true)
    printf("Hashtable insert.....[OK].\n");
  else
    {
      printf("Hashtable insert.....[FAILED].\n");
      return (false);
    }
  if (hashtable_lookup_test() == true)
    printf("Hashtable lookup.....[OK].\n");
  else
    {
      printf("Hashtable lookup.....[FAILED].\n");
      return (false);
    }
  if (hashtable_remove_test() == true)
    printf("Hashtable remove.....[OK].\n");
  else
    {
      printf("Hashtable remove.....[FAILED].\n");
      return (false);
    }
  return (true);
}

