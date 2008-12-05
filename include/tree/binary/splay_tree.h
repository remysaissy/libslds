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

#include    <tree.h>

/*
 * Data structure.
 */
typedef btree_t splay_tree_t;

/**
 * Initialize a splay tree node.
 * @param tree The root of the tree.
 * @param m The name of the splay tree data structure in tree.
 * @return true on success, false on error.
 */
#define splay_tree_init(tree, m)                     \
    _btree_init((void *)(tree),                     \
           (unsigned int)offsetof(typeof(*(tree)), m))

/**
 * Look for a node in a splay tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The name of the splay tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error.
 */
#define splay_tree_lookup(tree, key, m, compare_key_func)            \
    _splay_tree_lookup((void **)&(tree),                       \
        (void *)(key),                      \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_key_func)

/**
 * Insert a splay tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The name of the splay tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
#define splay_tree_insert(tree, new, m, compare_func)            \
    _btree_insert((void **)&(tree),                     \
              (void *)(new),                        \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_func)

/**
 * Remove a splay tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The name of the splay tree data structure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
#define splay_tree_remove(tree, key, m, compare_func, compare_key_func)  \
     _btree_remove((void **)&(tree),                        \
         (void *)(key),                     \
          (unsigned int)offsetof(typeof(*(tree)), m),       \
          compare_func,                     \
          compare_key_func)

/**
 * Graft a susplay_tree in a splay tree.
 * @param tree The root of the tree.
 * @param susplay_tree susplay_tree to be graft.
 * @param m The name of the splay tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A susplay_tree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
#define splay_tree_graft(tree, susplay_tree, m, compare_func)         \
    _btree_graft((void **)&(tree),                      \
        (void *)(susplay_tree),                      \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_func)

/**
 * Prune a splay tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The name of the splay tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The susplay_tree on success, NULL on error.
 */
#define splay_tree_prune(tree, key, m, compare_key_func)         \
    _btree_prune((void **)&(tree),                      \
        (void *)(key),                      \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_key_func)

/**
 * Step along the tree in a pre-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the splay tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define splay_tree_walk_preorder(tree, m, walk_func, data)                       \
        _btree_walk_preorder((void **)&(tree),                                \
                            (unsigned int)offsetof(typeof(*(tree)), m), \
                            walk_func,                                      \
                            (void *)(data))

/**
 * Step along the tree in a in-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the splay tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define splay_tree_walk_inorder(tree, m, walk_func, data)                        \
        _btree_walk_inorder((void **)&(tree),                             \
                            (unsigned int)offsetof(typeof(*(tree)), m), \
                            walk_func,                                      \
                            (void *)(data))

/**
 * Step along the tree in a post-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the splay tree datas tructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define splay_tree_walk_postorder(tree, m, walk_func, data)                      \
        _btree_walk_postorder((void **)&(tree),                       \
                            (unsigned int)offsetof(typeof(*(tree)), m), \
                            walk_func,                                      \
                            (void *)(data))


/* tree implementation. */

/**
 * Look for a node in a splay tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error.
 */
void    *_splay_tree_lookup(void **tree,
               void *key,
               unsigned int m,
               btree_compare_key_p compare_key_func);

#endif /* __LIBSLDS_BINARY_SPLAY_TREE_H__ */
