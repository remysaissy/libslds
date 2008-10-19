/*
 * This file is part of libslds

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

#ifndef	__LIBSLDS_TREE_H__
#error	"Direct inclusion not allowed. Please include tree.h instead."
#endif

#ifndef	__LIBSLDS_BTREE_H__
#define	__LIBSLDS_BTREE_H__

/*
 * This header implements binary search trees.
 * In order to be flexible, the key lookup line is
 * left to the caller through a macro so it can be
 * set and unset at will.
 */

/* Data type. */

typedef struct	btree_s
{
  void		*left;
  void		*right;

}		btree_t;

/* Implementation. */

#define	btree_init(tree, m)						\
	_btree_init((tree),						\
		   (unsigned int)offsetof(typeof(*(tree)), m))

#define	btree_lookup(tree, key, m, compare_key_func)			\
	_btree_lookup((tree),						\
		     (key),						\
		     (unsigned int)offsetof(typeof(**(tree)), m),	\
		     compare_key_func)

#define	btree_insert(tree, new, m, compare_func)			\
	_btree_insert((tree),						\
		     (new),						\
		     (unsigned int)offsetof(typeof(**(tree)), m),	\
		     compare_func)

#define	btree_remove(tree, key, m, compare_func, compare_key_func)	\
     _btree_remove((tree),						\
		  (key),						\
		  (unsigned int)offsetof(typeof(**(tree)), m),		\
		  compare_func,						\
		  compare_key_func)

/* tree implementation. */

bool	_btree_init(void *tree,
		    unsigned int m);

void	*_btree_lookup(void **tree, 
		       void *key, 
		       unsigned int m, 
		       tree_compare_key_p compare_key_func);

bool	_btree_insert(void **tree,
		      void *new, 
		      unsigned int m, 
		      tree_compare_p compare_func);

bool	_btree_remove(void **tree,
		      void *key, 
		      unsigned int m, 
		      tree_compare_p compare_func,
		      tree_compare_key_p compare_key_func);

#endif /* __LIBSLDS_BTREE_H__ */

