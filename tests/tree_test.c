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

#include	<stdio.h>
#include	<stdlib.h>

#include	<tree.h>

typedef struct	test_tree_s
{
  btree_t	btree;
  splay_tree_t	splay_tree;
  int		key;
  
}		test_tree_t;


/* Binary trees. */

int BTREE_COMPARE(void *n1, void *n2)
{
  test_tree_t	*bt1 = (test_tree_t *)n1;
  test_tree_t	*bt2 = (test_tree_t *)n2;
  
  return (bt1->key - bt2->key);
}

int BTREE_COMPARE_KEY(void *key, void *n2)
{
  int		*k = (int *)&key;
  test_tree_t	*bt2 = (test_tree_t *)n2;

  return (*k - bt2->key);
}

static bool	do_btree_init_tests(void)
{
  test_tree_t	test;

  if (_btree_init(NULL, 0) == true)
    {
      fprintf(stderr, ")btree_init(NULL, 0).\n)");
      return (false);
    }
  if (btree_init(&test, btree) == false)
    {
      fprintf(stderr, "btree_init(test, btree).\n)");
      return (false);
    }
  return (true);
}

static bool	do_btree_insert_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;

  root = NULL;
  if (_btree_insert(NULL, (void *)elem, 0, BTREE_COMPARE) == true)
    {
      fprintf(stderr, "_btree_insert(NULL, elem, 0, BTREE_COMPARE).\n)");
      return (false);
    }
  if (btree_insert(&root, NULL, btree, BTREE_COMPARE) == true)
    {
      fprintf(stderr, "btree_insert(&root, NULL, btree, BTREE_COMPARE).\n)");
      return (false);
    }
  if (btree_insert(&root, (void *)elem, btree, NULL) == true)
    {
      fprintf(stderr, "btree_insert(&root, elem, btree, NULL).\n)");
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == false)
    {
      fprintf(stderr, "btree_insert(&root, elem{1}, btree, BTREE_COMPARE).\n)");
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == false)
    {
      fprintf(stderr, "btree_insert(&root, elem{2}, btree, BTREE_COMPARE).\n)");
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == true)
    {
      fprintf(stderr, "btree_insert(&root, elem{1*}, btree, BTREE_COMPARE).\n)");
      return (false);
    }
  return (true);
}

static bool	do_btree_lookup_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;
  int		i;
  int		j;

  root = NULL;
  for (i = 0, j = 30; i < j; i++, j--)
    {
      elem = malloc(sizeof(*elem));
      elem->key = i;
      if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == false)
	{
	  fprintf(stderr, "btree_insert(&root, elem{%d}, btree, BTREE_COMPARE).\n)", i);
	  return (false);
	}
      elem = malloc(sizeof(*elem));
      elem->key = j;
      if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == false)
	{
	  fprintf(stderr, "btree_insert(&root, elem{%d}, btree, BTREE_COMPARE).\n)", j);
	  return (false);
	}
    }
  if (root == NULL)
    {
      fprintf(stderr, "root == NULL.\n");
      return (false);
    }
  for (i = 0, j = 30; i < j; i++, j--)
    {
      if (btree_lookup(&root, (void *)i, btree, BTREE_COMPARE_KEY) == NULL)
	{
	  fprintf(stderr, "btree_lookup(root, %d, btree, BTREE_COMPARE_KEY).\n", i);
	  return (false);
	}
      if (btree_lookup(&root, (void *)j, btree, BTREE_COMPARE_KEY) == NULL)
	{
	  fprintf(stderr, "btree_lookup(root, %d, btree, BTREE_COMPARE_KEY).\n", j);
	  return (false);
	}
    }
  return (true);
}

static bool	do_btree_remove_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;
  int		i;
  int		j;

  root = NULL;
  for (i = 0, j = 30; i < j; i++, j--)
    {
      elem = malloc(sizeof(*elem));
      elem->key = i;
      if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == false)
	{
	  fprintf(stderr, "btree_insert(&root, elem{%d}, btree, BTREE_COMPARE).\n)", i);
	  return (false);
	}
      elem = malloc(sizeof(*elem));
      elem->key = j;
      if (btree_insert(&root, (void *)elem, btree, BTREE_COMPARE) == false)
	{
	  fprintf(stderr, "btree_insert(&root, elem{%d}, btree, BTREE_COMPARE).\n)", j);
	  return (false);
	}
    }
  for (i = 0, j = 30; i < j; i++, j--)
    {
      if (btree_remove(&root, (void *)i, btree, BTREE_COMPARE, BTREE_COMPARE_KEY) == false)
	{
	  fprintf(stderr, "btree_remove(root, %d, btree, BTREE_COMPARE, BTREE_COMPARE_KEY).\n", i);
	  return (false);
	}
      if (btree_remove(&root, (void *)j, btree, BTREE_COMPARE, BTREE_COMPARE_KEY) == false)
	{
	  fprintf(stderr, "btree_remove(root, %d, btree, BTREE_COMPARE, BTREE_COMPARE_KEY).\n", j);
	  return (false);
	}
    }
  if (root != NULL)
    {
      fprintf(stderr, "root != NULL.\n");
      return (false);
    }
  return (true);
}

static bool	do_btree_tests(void)
{
  if (do_btree_init_tests() == false)
    {
      fprintf(stderr, "Btree init test.....Failed.\n");
      return (false);
    }
  else
    fprintf(stderr, "Btree init test.....[Ok].\n");
  if (do_btree_insert_tests() == false)
    {
      fprintf(stderr, "Btree insert test.....Failed.\n");
      return (false);
    }
  else
    fprintf(stderr, "Btree insert test.....[Ok].\n");
  if (do_btree_lookup_tests() == false)
    {
      fprintf(stderr, "Btree lookup test.....Failed.\n");
      return (false);
    }
  else
    fprintf(stderr, "Btree lookup test.....[Ok].\n");
  if (do_btree_remove_tests() == false)
    {
      fprintf(stderr, "Btree remove test.....Failed.\n");
      return (false);
    }
  else
    fprintf(stderr, "Btree remove test.....[Ok].\n");
  return (true);
}


/* Splay trees. */

int SPLAY_TREE_COMPARE(void *n1, void *n2)
{
  test_tree_t	*bt1 = (test_tree_t *)n1;
  test_tree_t	*bt2 = (test_tree_t *)n2;
  
  return (bt1->key - bt2->key);
}

int SPLAY_TREE_COMPARE_KEY(void *key, void *n2)
{
  int		*k = (int *)&key;
  test_tree_t	*bt2 = (test_tree_t *)n2;

  return (*k - bt2->key);
}

static bool	do_splay_tree_init_tests(void)
{
  test_tree_t	test;

  if (_splay_tree_init(NULL, 0) == true)
    {
      fprintf(stderr, ")splay_tree_init(NULL, 0).\n)");
      return (false);
    }
  if (splay_tree_init(&test, splay_tree) == false)
    {
      fprintf(stderr, "splay_tree_init(test, splay_tree).\n)");
      return (false);
    }
  return (true);
}

static bool	do_splay_tree_insert_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;

  root = NULL;
  if (_splay_tree_insert(NULL, (void *)elem, 0, SPLAY_TREE_COMPARE) == true)
    {
      fprintf(stderr, "_splay_tree_insert(NULL, elem, 0, SPLAY_TREE_COMPARE).\n)");
      return (false);
    }
  if (splay_tree_insert(&root, NULL, splay_tree, SPLAY_TREE_COMPARE) == true)
    {
      fprintf(stderr, "splay_tree_insert(&root, NULL, splay_tree, SPLAY_TREE_COMPARE).\n)");
      return (false);
    }
  if (splay_tree_insert(&root, (void *)elem, splay_tree, NULL) == true)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem, splay_tree, NULL).\n)");
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem{1}, splay_tree, SPLAY_TREE_COMPARE).\n)");
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem{2}, splay_tree, SPLAY_TREE_COMPARE).\n)");
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == true)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem{1*}, splay_tree, SPLAY_TREE_COMPARE).\n)");
      return (false);
    }
  return (true);
}

static bool	do_splay_tree_lookup_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;
  int		i;
  int		j;

  root = NULL;
  for (i = 0, j = 30; i < j; i++, j--)
    {
      elem = malloc(sizeof(*elem));
      elem->key = i;
      if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
	{
	  fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", i);
	  return (false);
	}
      elem = malloc(sizeof(*elem));
      elem->key = j;
      if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
	{
	  fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", j);
	  return (false);
	}
    }
  if (root == NULL)
    {
      fprintf(stderr, "root == NULL.\n");
      return (false);
    }
  for (i = 0, j = 30; i < j; i++, j--)
    {
      if (splay_tree_lookup(&root, (void *)i, splay_tree, SPLAY_TREE_COMPARE_KEY) == NULL)
	{
	  fprintf(stderr, "splay_tree_lookup(root, %d, splay_tree, SPLAY_TREE_COMPARE_KEY).\n", i);
	  return (false);
	}
      if (splay_tree_lookup(&root, (void *)j, splay_tree, SPLAY_TREE_COMPARE_KEY) == NULL)
	{
	  fprintf(stderr, "splay_tree_lookup(root, %d, splay_tree, SPLAY_TREE_COMPARE_KEY).\n", j);
	  return (false);
	}
    }
  return (true);
}

static bool	do_splay_tree_remove_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;
  int		i;
  int		j;

  root = NULL;
  for (i = 0, j = 30; i < j; i++, j--)
    {
      elem = malloc(sizeof(*elem));
      elem->key = i;
      if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
	{
	  fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", i);
	  return (false);
	}
      elem = malloc(sizeof(*elem));
      elem->key = j;
      if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
	{
	  fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", j);
	  return (false);
	}
    }
  for (i = 0, j = 30; i < j; i++, j--)
    {
      if (splay_tree_remove(&root, (void *)i, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY) == false)
	{
	  fprintf(stderr, "splay_tree_remove(root, %d, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY).\n", i);
	  return (false);
	}
      if (splay_tree_remove(&root, (void *)j, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY) == false)
	{
	  fprintf(stderr, "splay_tree_remove(root, %d, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY).\n", j);
	  return (false);
	}
    }
  if (root != NULL)
    {
      fprintf(stderr, "root != NULL.\n");
      return (false);
    }
  return (true);
}

static void	_print_spaces(int n)
{
  while (n-- > 0)
    printf(" ");
}

static void	do_splay_dump(test_tree_t *tree, int depth)
{
  if (tree == NULL)
    return;
  if (tree->splay_tree.parent == NULL)
    {
       _print_spaces(depth);
      printf("[%i]\n", tree->key);
      depth--;
    }
  if (tree->splay_tree.left
      || tree->splay_tree.right)
    _print_spaces(depth);
  if (tree->splay_tree.left)
    printf("[%i]", ((test_tree_t *)tree->splay_tree.left)->key);
  else
    printf("[ ]");
  printf("  ");
  if (tree->splay_tree.right)
    printf("[%i]", ((test_tree_t *)tree->splay_tree.right)->key);
  else
    printf("[ ]");
  printf("\n");
  do_splay_dump(tree->splay_tree.left, depth - 1);
  do_splay_dump(tree->splay_tree.right, depth - 1);
}

static int	do_get_max_depth(test_tree_t *tree)
{
  int ldepth;
  int	rdepth;
  test_tree_t	*p;

  ldepth = 0;
  p = tree;
  while (p)
    {
      if (p->splay_tree.left)
	ldepth++;
      p = (test_tree_t *)p->splay_tree.left;
    }
  rdepth = 0;
  p = tree;
  while (p)
    {
      if (p->splay_tree.right)
	rdepth++;
      p = (test_tree_t *)p->splay_tree.right;
    }
  return ((ldepth > rdepth ? ldepth : rdepth));
}

static bool	do_splay_tree_case1_tests(void)
{
  test_tree_t	*root;
  test_tree_t	*elem;

  elem = malloc(sizeof(*elem));
  elem->key = 1;
  if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", 1);
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", 1);
      return (false);
    }
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  if (splay_tree_insert(&root, (void *)elem, splay_tree, SPLAY_TREE_COMPARE) == false)
    {
      fprintf(stderr, "splay_tree_insert(&root, elem{%d}, splay_tree, SPLAY_TREE_COMPARE).\n)", 1);
      return (false);
    }

  do_splay_dump(root, do_get_max_depth(root));
  return (true);
}

static bool	do_splay_tree_tests(void)
{
/*   if (do_splay_tree_init_tests() == false) */
/*     { */
/*       fprintf(stderr, "Splay_Tree init test.....Failed.\n"); */
/*       return (false); */
/*     } */
/*   else */
/*     fprintf(stderr, "Splay_Tree init test.....[Ok].\n"); */
/*   if (do_splay_tree_insert_tests() == false) */
/*     { */
/*       fprintf(stderr, "Splay_Tree insert test.....Failed.\n"); */
/*       return (false); */
/*     } */
/*   else */
/*     fprintf(stderr, "Splay_Tree insert test.....[Ok].\n"); */
/*   if (do_splay_tree_lookup_tests() == false) */
/*     { */
/*       fprintf(stderr, "Splay_Tree lookup test.....Failed.\n"); */
/*       return (false); */
/*     } */
/*   else */
/*     fprintf(stderr, "Splay_Tree lookup test.....[Ok].\n"); */
/*   if (do_splay_tree_remove_tests() == false) */
/*     { */
/*       fprintf(stderr, "Splay_Tree remove test.....Failed.\n"); */
/*       return (false); */
/*     } */
/*   else */
/*     fprintf(stderr, "Splay_Tree remove test.....[Ok].\n"); */
  if (do_splay_tree_case1_tests() == false)
    {
      fprintf(stderr, "Splay_Tree case 1 test.....Failed.\n");
      return (false);
    }
  else
    fprintf(stderr, "Splay_Tree case 1 test.....[Ok].\n");
  return (true);
}

/* Main function. */

bool	do_trees(void)
{
  if (do_btree_tests() == false)
    return (false);
  if (do_splay_tree_tests() == false)
    return (false);
  return (true);
}
