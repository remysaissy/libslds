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

#ifndef	__LIBSLDS_TREE_H__
#error	"Direct inclusion not allowed. Please include tree.h instead."
#endif

#ifndef	__LIBSLDS_BINARY_SPLAY_TREE_H__
#define	__LIBSLDS_BINARY_SPLAY_TREE_H__

/* Splay trees. Bottom-up implementation. */

/*
 * Data structure.
 */
typedef struct		splay_tree_s
{
binary_tree_base_t	_btree_base;
  void			*parent; /** the parent node. */  

}			splay_tree_t;

/* Implementation. */

#define	splay_tree_init(tree, m)						\
	_splay_tree_init((void *)(tree),						\
		   (unsigned int)offsetof(typeof(*(tree)), m))

#define	splay_tree_lookup(tree, key, m, compare_key_func)			\
	_splay_tree_lookup((void **)&(tree),						\
			(void *)(key),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_key_func)

#define	splay_tree_insert(tree, new, m, compare_func)			\
	_splay_tree_insert((void **)&(tree),						\
			(void *)(new),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_func)

#define	splay_tree_remove(tree, key, m, compare_func, compare_key_func)	\
     _splay_tree_remove((void **)&(tree),						\
    		 (void *)(key),						\
		  (unsigned int)offsetof(typeof(*(tree)), m),		\
		  compare_func,						\
		  compare_key_func)

#define	splay_tree_prune(tree, subtree, m, compare_key_func)			\
		_splay_tree_prune((void **)&(tree),						\
				(void *)(subtree),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_func)

#define	splay_tree_graft(tree, key, m, compare_key_func)			\
	_splay_tree_graft((void **)&(tree),						\
			(void *)(key),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_key_func)

#define	splay_tree_walk_preorder(tree, m, walk_func, data)						\
		_binary_tree_walk_preorder((void **)&(tree),								\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

#define	splay_tree_walk_inorder(tree, m, walk_func, data)						\
		_binary_tree_walk_inorder((void **)&(tree),								\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

#define	splay_tree_walk_postorder(tree, m, walk_func, data)						\
		_binary_tree_walk_postorder((void **)&(tree),						\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))



/* tree implementation. */

bool	_splay_tree_init(void *tree,
			 unsigned int m);

void	*_splay_tree_lookup(void **tree, 
			    void *key, 
			    unsigned int m, 
			    btree_compare_key_p compare_key_func);

bool	_splay_tree_insert(void **tree,
			   void *new, 
			   unsigned int m, 
			   btree_compare_p compare_func);

bool	_splay_tree_remove(void **tree,
			   void *key, 
			   unsigned int m, 
			   btree_compare_p compare_func,
			   btree_compare_key_p compare_key_func);

// TODO: prune.
bool	_splay_tree_prune(void **tree,						
		     void *subtree,						
		     unsigned int m,	
		     btree_compare_p compare_func);

// TODO: graft.
void	*_splay_tree_graft(void **tree,
		     void *key,
		     unsigned int m,
		     btree_compare_key_p compare_key_func);


#endif /* __LIBSLDS_BINARY_SPLAY_TREE_H__ */
