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

#include        <stdio.h>

#include	<tree.h>

#include	"include/avl_rotation.h"

static void splay(void **tree, 
                  void *node, 
                  unsigned int m)
  {
    /* A splay operation essentially drags the node to the root of the tree */
    /* with AVL rotations. */
    if (node == NULL 
        || tree == NULL 
        || *tree == NULL)
      return;
    while (GET_FIELD(node, m, splay_tree_t)->parent != NULL) /* node != *tree */
      {
        void *parent;

        parent = GET_FIELD(node, m, splay_tree_t)->parent;
        if (GET_FIELD(parent, m, splay_tree_t)->parent == NULL) /* parent is the root. */
          {
            if (node == GET_FIELD(parent, m, splay_tree_t)->_btree_base.left)
              _avl_rotate_right(tree, node, m);
            else
              _avl_rotate_left(tree, node, m);
          }
        else
          {
            void *grandparent;            

            grandparent = GET_FIELD(parent, m, splay_tree_t)->parent;
            if ( (node == GET_FIELD(parent, m, splay_tree_t)->_btree_base.left && parent == GET_FIELD(grandparent, m, splay_tree_t)->_btree_base.left) || (node == GET_FIELD(parent, m, splay_tree_t)->_btree_base.right && parent == GET_FIELD(grandparent, m, splay_tree_t)->_btree_base.right))
              {             
                if (node == GET_FIELD(parent, m, splay_tree_t)->_btree_base.left)
                  {
                    _avl_rotate_left(tree, parent, m);
                    _avl_rotate_left(tree, node, m);
                  }
                else
                  {
                    _avl_rotate_right(tree, parent, m);
                    _avl_rotate_right(tree, node, m);
                  }
              }
            else
              {
                if (node == GET_FIELD(parent, m, splay_tree_t)->_btree_base.left)
                  {
                    _avl_rotate_left(tree, node, m);
                    _avl_rotate_right(tree, node, m);
                  }
                else
                  {
                    _avl_rotate_right(tree, node, m);
                    _avl_rotate_left(tree, node, m);
                  }
              }
          }
      }
    //*tree = node;
  }

bool _splay_tree_init(void *tree,
    unsigned int m)
  {
    if (tree)
      {
        GET_FIELD(tree, m, splay_tree_t)->parent = NULL;
        GET_FIELD(tree, m, splay_tree_t)->_btree_base.left = NULL;
        GET_FIELD(tree, m, splay_tree_t)->_btree_base.right = NULL;
        return (true);
      }
    return (false);
  }

void *_splay_tree_lookup(void **tree, 
                          void *key, 
                          unsigned int m,
                          btree_compare_key_p compare_key_func)
  {
    void *it;
  
    if (tree == NULL 
        || *tree == NULL
        || compare_key_func == NULL)
      return (NULL);
    it = _binary_tree_lookup(tree, key, m, compare_key_func);
    if (it != NULL)
    	splay(tree, it, m);
    return (it);
  }

bool _splay_tree_insert(void **tree,
                        void *new,
                        unsigned int m,
                        btree_compare_p compare_func)
  {
    void *it;
    int ret;

    if (tree == NULL
        || new == NULL
        || compare_func == NULL)
        return (false);
    GET_FIELD(new, m, splay_tree_t)->parent = NULL;
    GET_FIELD(new, m, splay_tree_t)->_btree_base.left = NULL;
    GET_FIELD(new, m, splay_tree_t)->_btree_base.right = NULL;
    if (*tree == NULL)
    *tree = new;
    else
      {
        it = *tree;
        while (1)
          {
            ret = compare_func(it, new);
            switch (ret)
              {
                case BTREE_LEFT:
                if (GET_FIELD(it, m, splay_tree_t)->_btree_base.left == NULL)
                  {
                    GET_FIELD(it, m, splay_tree_t)->_btree_base.left = new;
                    GET_FIELD(new, m, splay_tree_t)->parent = it;
                    splay(tree, new, m);				  
                    return(true);
                  }
                else
                  {
                    it = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
                  }
                break;

                case BTREE_RIGHT:
                if (GET_FIELD(it, m, splay_tree_t)->_btree_base.right == NULL)
                  {
                    GET_FIELD(it, m, splay_tree_t)->_btree_base.right = new;
                    GET_FIELD(new, m, splay_tree_t)->parent = it;
                    splay(tree, new, m);
                    return (true);
                  }
                else
                  {
                    it = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
                  }
                break;
                case BTREE_MATCH:
                return (false);
              }
          }
      }
    return (true);
  }

bool _splay_tree_remove(void **tree,
    void *key,
    unsigned int m,
    btree_compare_p compare_func,
    btree_compare_key_p compare_key_func)
  {
    void *prev_it;
    void *it;
    int ret;

    if (tree == NULL
        || *tree == NULL
        || compare_func == NULL
        || compare_key_func == NULL)
    return (false);
    prev_it = NULL;
    it = *tree;
    while (it)
      {
        ret = compare_key_func(it, key);
        switch (ret)
          {
            case BTREE_LEFT:
            prev_it = it;
            it = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
            break;
            case BTREE_RIGHT:
            prev_it = it;
            it = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
            break;
            case BTREE_MATCH:
            /* We found the node. */
            if (GET_FIELD(it, m, splay_tree_t)->_btree_base.left == NULL &&
                GET_FIELD(it, m, splay_tree_t)->_btree_base.right == NULL)
              {
                if (prev_it == NULL)
                *tree = NULL;
                else
                  {
                    GET_FIELD(it, m, splay_tree_t)->parent = NULL;
                    if (GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left == it)
                    GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left = NULL;
                    else
                    GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.right = NULL;
                  }
              }
            else
              {
                if (GET_FIELD(it, m, splay_tree_t)->_btree_base.left != NULL &&
                    GET_FIELD(it, m, splay_tree_t)->_btree_base.right != NULL)
                  {
                    void *lp;
                    void *lpp;
                    void *rp;
                    void *rpp;

                    lpp = NULL;
                    lp = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
                    while (GET_FIELD(lp, m, splay_tree_t)->_btree_base.right)
                      {
                        lpp = lp;
                        lp = GET_FIELD(lp, m, splay_tree_t)->_btree_base.right;
                      }
                    rpp = NULL;
                    rp = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
                    while (GET_FIELD(rp, m, splay_tree_t)->_btree_base.left)
                      {
                        rpp = rp;
                        rp = GET_FIELD(rp, m, splay_tree_t)->_btree_base.left;
                      }
                    if (compare_func(it, lp) <= compare_func(it, rp))
                      {
                        /* we choose left. */
                        GET_FIELD(lpp, m, splay_tree_t)->_btree_base.right = GET_FIELD(lp, m, splay_tree_t)->_btree_base.left;
                        GET_FIELD(GET_FIELD(lp, m, splay_tree_t)->_btree_base.left, m, splay_tree_t)->parent = lpp;
                        if (prev_it == NULL)
                        *tree = lp;
                        else
                          {
                            GET_FIELD(lp, m, splay_tree_t)->parent = prev_it;
                            if (GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left == it)
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left = lp;
                            else
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.right = lp;
                          }
                        GET_FIELD(lp, m, splay_tree_t)->_btree_base.left = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
                        GET_FIELD(it, m, splay_tree_t)->parent = NULL;
                      }
                    else
                      {
                        /* we choose right. */
                        GET_FIELD(rpp, m, splay_tree_t)->_btree_base.left = GET_FIELD(rp, m, splay_tree_t)->_btree_base.right;
                        GET_FIELD(GET_FIELD(rp, m, splay_tree_t)->_btree_base.left, m, splay_tree_t)->parent = rpp;
                        if (prev_it == NULL)
                        *tree = rp;
                        else
                          {
                            GET_FIELD(rp, m, splay_tree_t)->parent = prev_it;
                            if (GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left == it)
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left = rp;
                            else
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.right = rp;
                          }
                        GET_FIELD(rp, m, splay_tree_t)->_btree_base.right = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
                        GET_FIELD(it, m, splay_tree_t)->parent = NULL;
                      }
                  }
                else
                  {
                    GET_FIELD(it, m, splay_tree_t)->parent = prev_it;
                    if (GET_FIELD(it, m, splay_tree_t)->_btree_base.left != NULL)
                      {
                        if (prev_it == NULL)
                        *tree = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
                        else
                          {
                            if (GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left == it)
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
                            else
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.right = GET_FIELD(it, m, splay_tree_t)->_btree_base.left;
                          }
                      }
                    else
                      {
                        if (prev_it == NULL)
                        *tree = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
                        else
                          {
                            if (GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left == it)
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.left = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
                            else
                            GET_FIELD(prev_it, m, splay_tree_t)->_btree_base.right = GET_FIELD(it, m, splay_tree_t)->_btree_base.right;
                          }
                      }
                  }
              }
            splay(tree, prev_it, m);
            return (true);
          }
      }
    return (false);
  }

bool _splay_tree_prune(void **tree,
                        void *subtree,
                        unsigned int m,
                        btree_compare_p compare_func)
  {
    if (tree == NULL
        || *tree == NULL
        || subtree == NULL
        || compare_func)
    return (false);
    return (false);
  }

void *_splay_tree_graft(void **tree, 
                        void *key, 
                        unsigned int m,
                        btree_compare_key_p compare_key_func)
  {
    if (tree == NULL 
        || *tree == NULL 
        || compare_key_func)
      return (NULL);
    return (NULL);
  }
