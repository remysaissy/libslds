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

typedef struct	test_tree_s
{
  splay_tree_t	splay_tree;
  int		key;
  
}		test_tree_t;
//
//btree_compare_e SPLAY_TREE_COMPARE(void *n1, void *n2)
//{
//  test_tree_t	*bt1 = (test_tree_t *)n1;
//  test_tree_t	*bt2 = (test_tree_t *)n2;
//  
//  if ((bt1->key - bt2->key) < 0)
//	  return (BTREE_LEFT);
//  if ((bt1->key - bt2->key) > 0)
//	  return (BTREE_RIGHT);
//  return (BTREE_MATCH);
//}
//
//btree_compare_e SPLAY_TREE_COMPARE_KEY(void *n1, void *key)
//{
//  int		*k = (int *)&key;
//  test_tree_t	*bt2 = (test_tree_t *)n1;
//
//  if ((*k - bt2->key) < 0)
//	  return (BTREE_LEFT);
//  if ((*k - bt2->key) > 0)
//	  return (BTREE_RIGHT);
//  return (BTREE_MATCH);
//}
////
////void Testsplay_tree_init(CuTest *tc)
////{
////  test_tree_t	test;
////  bool			ret;
////  
////  ret = _splay_tree_init(NULL, 0);
////  CuAssertTrue(tc, !ret);
////  ret = splay_tree_init(&test, splay_tree);
////  CuAssertTrue(tc, ret);
////}
////
////void Testsplay_tree_insert(CuTest *tc)
////{
////  test_tree_t	*root;
////  test_tree_t	*elem;
////  bool			ret;
////  
////  root = NULL;
////  ret = _splay_tree_insert(NULL, elem, 0, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, !ret);
////  ret = splay_tree_insert(&root, NULL, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, !ret);
////  elem = malloc(sizeof(*elem));
////  elem->key = 1;
////  ret = splay_tree_insert(&root, elem, splay_tree, NULL);
////  CuAssertTrue(tc, !ret);
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
////  elem = malloc(sizeof(*elem));
////  elem->key = 2;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
////  elem = malloc(sizeof(*elem));
////  elem->key = 1;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, !ret);
////}
////
////void Testsplay_tree_lookup(CuTest *tc)
////{
////  test_tree_t	*root;
////  test_tree_t	*elem;
////  int			i;
////  int			j;
////  bool			ret;
////  void			*pret;
////  
////  root = NULL;
////  for (i = 0, j = 30; i < j; i++, j--)
////    {
////      elem = malloc(sizeof(*elem));
////      elem->key = i;
////      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////      CuAssertTrue(tc, ret);
////      elem = malloc(sizeof(*elem));
////      elem->key = j;
////      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////      CuAssertTrue(tc, ret);
////    }
////  CuAssertPtrNotNull(tc, root);
////  for (i = 0, j = 30; i < j; i++, j--)
////    {
////	  pret = splay_tree_lookup(&root, i, splay_tree, SPLAY_TREE_COMPARE_KEY);
////	  CuAssertPtrNotNull(tc, pret);
////	  pret = splay_tree_lookup(&root, j, splay_tree, SPLAY_TREE_COMPARE_KEY);
////	  CuAssertPtrNotNull(tc, pret);
////    }
////}
////
////void Testsplay_tree_remove(CuTest *tc)
////{
////  test_tree_t	*root;
////  test_tree_t	*elem;
////  int			i;
////  int			j;
////  bool			ret;
////  
////  root = NULL;
////  for (i = 0, j = 30; i < j; i++, j--)
////    {
////      elem = malloc(sizeof(*elem));
////      elem->key = i;
////      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////      CuAssertTrue(tc, ret);
////      elem = malloc(sizeof(*elem));
////      elem->key = j;
////      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////      CuAssertTrue(tc, ret);
////    }
////  for (i = 0, j = 30; i < j; i++, j--)
////    {
////	  ret = splay_tree_remove(&root, i, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY);
////	  CuAssertTrue(tc, ret);
////	  ret = splay_tree_remove(&root, j, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY);
////	  CuAssertTrue(tc, ret);
////    }
////  CuAssertPtrNotNull(tc, root);
////}
//
//void Testsplay_tree_case1(CuTest *tc)
//{
//  test_tree_t	*root;
//  test_tree_t	*elem;
//  int			i;
//  bool			ret;
//  void			*pret;
//  test_tree_t           *node;
//  
//  root = NULL;
//  for (i = 2; i >= 0; i--)
//    {
//      elem = malloc(sizeof(*elem));
//      elem->key = i;
//      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
//      CuAssertTrue(tc, ret);
//    }
//  node = (test_tree_t *)root;
//  for (i = 0; i <= 2; i++)
//    {
//      CuAssertIntEquals(tc, i, node->key);
//      node = ((test_tree_t *)node->splay_tree.right);
//    }
//  pret = splay_tree_lookup(&root, 1, splay_tree, SPLAY_TREE_COMPARE_KEY);
//  CuAssertPtrNotNull(tc, pret);
//  CuAssertPtrEquals(tc, pret, root);
//  CuAssertIntEquals(tc, 1, root->key);
//  CuAssertIntEquals(tc, 0, ((test_tree_t *)root->splay_tree.left)->key);
//  CuAssertIntEquals(tc, 2, ((test_tree_t *)root->splay_tree.right)->key);
//  for (i = 0; i < 3; i++)
//    {
//	  ret = splay_tree_remove(&root, i, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY);
//	  CuAssertTrue(tc, ret);
//    }
//  CuAssertPtrEquals(tc, NULL, root);
//}
//
//void Testsplay_tree_case2(CuTest *tc)
//{
//  test_tree_t   *root;
//  test_tree_t   *elem;
//  int                   i;
//  bool                  ret;
//  void                  *pret;
//  test_tree_t           *node;
//  
//  root = NULL;
//  for (i = 0; i < 4; i++)
//    {
//      elem = malloc(sizeof(*elem));
//      elem->key = i;
//      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
//      CuAssertTrue(tc, ret);
//    }
//  node = (test_tree_t *)root;
//  for (i = 0; i < 4; i++)
//    {
//      CuAssertIntEquals(tc, i, node->key);
//      node = ((test_tree_t *)node->splay_tree.right);
//    }
//  pret = splay_tree_lookup(&root, 2, splay_tree, SPLAY_TREE_COMPARE_KEY);
//  CuAssertPtrNotNull(tc, pret);
//  CuAssertPtrEquals(tc, pret, root);
//  node = (test_tree_t *)root;
//  CuAssertIntEquals(tc, 2, node->key);
//  CuAssertIntEquals(tc, 3, ((test_tree_t *)node->splay_tree.right)->key);
//  node = (test_tree_t *)node->splay_tree.left;
//  CuAssertIntEquals(tc, 1, node->key);
//  CuAssertIntEquals(tc, 0, ((test_tree_t *)node->splay_tree.left)->key);
//  for (i = 0; i < 4; i++)
//    {
//          ret = splay_tree_remove(&root, i, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY);
//          CuAssertTrue(tc, ret);
//    }
//  CuAssertPtrEquals(tc, NULL, root);
//}
//
//void Testsplay_tree_case3(CuTest *tc)
//{
//  test_tree_t   *root;
//  test_tree_t   *elem;
//  int                   i;
//  bool                  ret;
//  void                  *pret;
//  test_tree_t           *node;
//  
//  root = NULL;
//  for (i = 0; i < 5; i++)
//    {
//      elem = malloc(sizeof(*elem));
//      elem->key = i;
//      ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
//      CuAssertTrue(tc, ret);
//    }
//
////  elem = malloc(sizeof(*elem));
////  elem->key = 3;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
////
////  elem = malloc(sizeof(*elem));
////  elem->key = 4;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
////
////  elem = malloc(sizeof(*elem));
////  elem->key = 1;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
////
////  elem = malloc(sizeof(*elem));
////  elem->key = 0;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
////
////  elem = malloc(sizeof(*elem));
////  elem->key = 2;
////  ret = splay_tree_insert(&root, elem, splay_tree, SPLAY_TREE_COMPARE);
////  CuAssertTrue(tc, ret);
//
//  node = (test_tree_t *)root;
//  for (i = 0; i < 5; i++)
//    {
//      CuAssertIntEquals(tc, i, node->key);
//      node = ((test_tree_t *)node->splay_tree.right);
//    }
//  pret = splay_tree_lookup(&root, 3, splay_tree, SPLAY_TREE_COMPARE_KEY);
//  CuAssertPtrNotNull(tc, pret);
//  CuAssertPtrEquals(tc, pret, root);
//  node = (test_tree_t *)root;
//  CuAssertIntEquals(tc, 3, node->key);
//  CuAssertIntEquals(tc, 4, ((test_tree_t *)node->splay_tree.right)->key);
//  node = (test_tree_t *)node->splay_tree.left;
//  CuAssertIntEquals(tc, 1, node->key);
//  CuAssertIntEquals(tc, 0, ((test_tree_t *)node->splay_tree.left)->key);
//  CuAssertIntEquals(tc, 2, ((test_tree_t *)node->splay_tree.right)->key);
//
//  pret = splay_tree_lookup(&root, 2, splay_tree, SPLAY_TREE_COMPARE_KEY);
//  CuAssertPtrNotNull(tc, pret);
//  CuAssertPtrEquals(tc, pret, root);
//  node = (test_tree_t *)root;
//  CuAssertIntEquals(tc, 2, node->key);
//  node = (test_tree_t *)node->splay_tree.right;
//  CuAssertIntEquals(tc, 3, node->key);
//  CuAssertIntEquals(tc, 4, ((test_tree_t *)node->splay_tree.right)->key);
//  node = (test_tree_t *)root->splay_tree.left;
//  CuAssertIntEquals(tc, 1, node->key);
//  CuAssertIntEquals(tc, 0, ((test_tree_t *)node->splay_tree.left)->key);
//    
//  for (i = 0; i < 5; i++)
//    {
//          ret = splay_tree_remove(&root, i, splay_tree, SPLAY_TREE_COMPARE, SPLAY_TREE_COMPARE_KEY);
//          CuAssertTrue(tc, ret);
//    }
//  CuAssertPtrEquals(tc, NULL, root);
//}
