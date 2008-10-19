/*
 * This file is part of libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * libslds is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * libslds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include	<stdio.h>
#include	<stdlib.h>

#include	<CuTest.h>

#include	<tree.h>

typedef struct test_tree_s
  {
    int key;
    btree_t btree;

  } test_tree_t;

btree_compare_e BTREE_COMPARE(void *n1, void *n2)
  {
    test_tree_t *bt1 = (test_tree_t *)n1;
    test_tree_t *bt2 = (test_tree_t *)n2;

    if (bt2->key < bt1->key)
      return (BTREE_LEFT);
    if (bt2->key > bt1->key)
      return (BTREE_RIGHT);
    return (BTREE_MATCH);
  }

btree_compare_e BTREE_COMPARE_KEY(void *n1, void *key)
  {
    int *k = (int *)&key;
    test_tree_t *bt1 = (test_tree_t *)n1;

    if (*k < bt1->key)
      return (BTREE_LEFT);
    if (*k > bt1->key)
      return (BTREE_RIGHT);
    return (BTREE_MATCH);
  }

void Testbinary_tree_init(CuTest *tc)
  {
    test_tree_t test;
    bool ret;

    ret = _btree_init(NULL, 0);
    CuAssertTrue(tc, !ret);
    ret = btree_init(&test, btree);
    CuAssertTrue(tc, ret);
  }

void Testbinary_tree_insert(CuTest *tc)
  {
    test_tree_t *root;
    test_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    ret = _btree_insert(NULL, elem, 0, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = btree_insert(&root, NULL, btree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = btree_insert(&root, elem, btree, NULL);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = root;
    CuAssertIntEquals(tc, 2, elem->key);
    CuAssertIntEquals(tc, 1, ((test_tree_t *)elem->btree._btree_base.left)->key);
    CuAssertIntEquals(tc, 3, ((test_tree_t *)elem->btree._btree_base.right)->key);
  }

void Testbinary_tree_lookup(CuTest *tc)
  {
    test_tree_t *root;
    test_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 30; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    CuAssertPtrNotNull(tc, root);
    for (i = 0, j = 30; i < j; i++, j--)
      {
        pret = btree_lookup(&root, i, btree, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = btree_lookup(&root, j, btree, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testbinary_tree_remove(CuTest *tc)
  {
    test_tree_t *root;
    test_tree_t *elem;
    int i;
    int j;
    bool ret;
    void        *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = btree_remove(&root, i, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = btree_remove(&root, j, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }

static bool	walk_state;
static int prev_value;

static void	btree_walk_preorder_cb(void *node, void *data)
{
	test_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_tree_t *)node;
	prev_value = elem->key;
	switch (prev)
	{
	case -1:
		if (elem->key != 8)
			walk_state = false;
		break;
	case 8:
		if (elem->key != 6)
			walk_state = false;
		break;
	case 6:
		if (elem->key != 5)
			walk_state = false;
		break;
	case 5:
		if (elem->key != 7)
			walk_state = false;
		break;
	case 7:
		if (elem->key != 10)
			walk_state = false;
		break;
	case 10:
		if (elem->key != 9)
			walk_state = false;
		break;
	case 9:
		if (elem->key != 11)
			walk_state = false;
		break;
	case 11:
		walk_state = false;
		break;
	}
}

void Testbinary_tree_walk_preorder(CuTest *tc)
  {
 	test_tree_t *root;
    test_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	btree_walk_preorder(&root, btree, btree_walk_preorder_cb, NULL);
	CuAssertIntEquals(tc, true, walk_state);

    pret = btree_remove(&root, 8, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 6, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 5, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 7, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 10, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 9, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 11, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void	btree_walk_inorder_cb(void *node, void *data)
{
	test_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_tree_t *)node;
	prev_value = elem->key;
	switch (prev)
	{
	case -1:
		if (elem->key != 5)
			walk_state = false;
		break;
	case 5:
		if (elem->key != 6)
			walk_state = false;
		break;
	case 6:
		if (elem->key != 7)
			walk_state = false;
		break;
	case 7:
		if (elem->key != 8)
			walk_state = false;
		break;
	case 8:
		if (elem->key != 9)
			walk_state = false;
		break;
	case 9:
		if (elem->key != 10)
			walk_state = false;
		break;
	case 10:
		if (elem->key != 11)
			walk_state = false;
		break;
	case 11:
		walk_state = false;
		break;
	}
}

void Testbinary_tree_walk_inorder(CuTest *tc)
  {
 	test_tree_t *root;
    test_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	btree_walk_inorder(&root, btree, btree_walk_inorder_cb, NULL);
	CuAssertIntEquals(tc, true, walk_state);

    pret = btree_remove(&root, 8, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 6, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 5, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 7, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 10, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 9, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 11, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void	btree_walk_postorder_cb(void *node, void *data)
{
	test_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_tree_t *)node;
	prev_value = elem->key;
	switch (prev)
	{
	case -1:
		if (elem->key != 5)
			walk_state = false;
		break;
	case 5:
		if (elem->key != 7)
			walk_state = false;
		break;
	case 7:
		if (elem->key != 6)
			walk_state = false;
		break;
	case 6:
		if (elem->key != 9)
			walk_state = false;
		break;
	case 9:
		if (elem->key != 11)
			walk_state = false;
		break;
	case 11:
		if (elem->key != 10)
			walk_state = false;
		break;
	case 10:
		if (elem->key != 8)
			walk_state = false;
		break;
	case 8:
		walk_state = false;
		break;
	}
}

void Testbinary_tree_walk_postorder(CuTest *tc)
  {
 	test_tree_t *root;
    test_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	btree_walk_postorder(&root, btree, btree_walk_postorder_cb, NULL);
	CuAssertIntEquals(tc,true, walk_state);

    pret = btree_remove(&root, 8, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 6, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 5, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 7, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 10, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 9, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = btree_remove(&root, 11, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }


void Testbinary_tree_graft(CuTest *tc)
  {
    test_tree_t *root1;
    test_tree_t *root2;
    test_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root1 = NULL;
    root2 = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = btree_insert(&root1, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = btree_insert(&root2, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    pret = btree_lookup(&root1, i + 1, btree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    ret = btree_graft(&root1, NULL, btree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = btree_graft(&root1, root2, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    pret = btree_lookup(&root1, j + 1, btree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = btree_remove(&root1, i, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = btree_remove(&root2, j, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testbinary_tree_prune(CuTest *tc)
  {
    test_tree_t *root;
    test_tree_t *grafted;
    test_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = btree_insert(&root, elem, btree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    grafted = btree_prune(&root, j, btree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, grafted);
    grafted = btree_prune(&root, 5, btree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, grafted);
    pret = btree_lookup(&grafted, 1, btree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    pret = btree_lookup(&grafted, 5, btree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    ret = btree_graft(&root, grafted, btree, BTREE_COMPARE_KEY);
    CuAssertTrue(tc, ret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = btree_remove(&root, i, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        ret = btree_remove(&root, j, btree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }
