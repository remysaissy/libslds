/*
 * This file is part of libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * Splay Tree is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * Splay Tree is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<tree.h>

/* Perform an AVL left rotation. */
static void	splay_rotate_left(void **node, void **child, unsigned int m)
{
  if (node == NULL
      || *node == NULL
      || child == NULL
      || *child == NULL)
    return;
  GET_FIELD(*node, m, splay_tree_t)->left = GET_FIELD(*child, m, splay_tree_t)->right;
  if (GET_FIELD(*node, m, splay_tree_t)->left)
    GET_FIELD(GET_FIELD(*node, m, splay_tree_t)->left, m, splay_tree_t)->parent = *node;
  GET_FIELD(*child, m, splay_tree_t)->right = *node;
  GET_FIELD(*child, m, splay_tree_t)->parent = GET_FIELD(*node, m, splay_tree_t)->parent;
  GET_FIELD(*node, m, splay_tree_t)->parent = *child;
}

/* Perform an AVL right rotation. */
static void	splay_rotate_right(void **node, void **child, unsigned int m)
{
  if (node == NULL
      || *node == NULL
      || child == NULL
      || *child == NULL)
    return;
  GET_FIELD(*node, m, splay_tree_t)->right = GET_FIELD(*child, m, splay_tree_t)->left;
  if (GET_FIELD(*node, m, splay_tree_t)->right)
    GET_FIELD(GET_FIELD(*node, m, splay_tree_t)->right, m, splay_tree_t)->parent = *node;
  GET_FIELD(*child, m, splay_tree_t)->left = *node;
  GET_FIELD(*child, m, splay_tree_t)->parent = GET_FIELD(*node, m, splay_tree_t)->parent;
  GET_FIELD(*node, m, splay_tree_t)->parent = *child;
}

static void		splay(void **tree, void *node, unsigned int m)
{
  /* A splay operation essentially drags the node to the root of the tree */
  /* with AVL rotations. */
  if (node == NULL
      || tree == NULL
      || *tree == NULL)
    return;
  while (node != *tree)
    {
      void	*parent;

      parent = GET_FIELD(node, m, splay_tree_t)->parent;
      if (parent == *tree)
	{
	  if (node == GET_FIELD(parent, m, splay_tree_t)->left)
	    splay_rotate_left(tree, &node, m);
	  else
	    splay_rotate_right(tree, &node, m);
	}
      else
	{
	  void	*grandparent;
	 
	  grandparent = GET_FIELD(parent, m, splay_tree_t)->parent;
	  if (
	      (node == GET_FIELD(parent, m, splay_tree_t)->left
	       && parent == GET_FIELD(grandparent, m, splay_tree_t)->left)
	      ||
	      (node == GET_FIELD(parent, m, splay_tree_t)->right
	       && parent == GET_FIELD(grandparent, m, splay_tree_t)->right)
	      )
	    {
	      if (parent == GET_FIELD(grandparent, m, splay_tree_t)->left)
		splay_rotate_left(&grandparent, &parent, m);
	      else
		splay_rotate_right(&grandparent, &parent, m);
	      if (node == GET_FIELD(node, m, splay_tree_t)->left)
		splay_rotate_left(&GET_FIELD(node, m, splay_tree_t)->parent, &node, m);
	      else
		splay_rotate_right(&GET_FIELD(node, m, splay_tree_t)->parent, &node, m);
	    }
	  else
	    {
	      if (node == GET_FIELD(node, m, splay_tree_t)->left)
		splay_rotate_left(&GET_FIELD(node, m, splay_tree_t)->parent, &node, m);
	      else
		splay_rotate_right(&GET_FIELD(node, m, splay_tree_t)->parent, &node, m);
	      if (node == GET_FIELD(node, m, splay_tree_t)->left)
		splay_rotate_left(&GET_FIELD(node, m, splay_tree_t)->parent, &node, m);
	      else
		splay_rotate_right(&GET_FIELD(node, m, splay_tree_t)->parent, &node, m);
	    }
	}
    }  
}


bool	_splay_tree_init(void *tree,
			 unsigned int m)
{
  if (tree)
    {
      GET_FIELD(tree, m, splay_tree_t)->parent = NULL;
      GET_FIELD(tree, m, splay_tree_t)->left = NULL;
      GET_FIELD(tree, m, splay_tree_t)->right = NULL;
      return (true);
    }
  return (false);
}

void	*_splay_tree_lookup(void **tree,
			    void *key, 
			    unsigned int m, 
			    tree_compare_key_p compare_key_func)
{
  void	*it;
  int	ret;

  if (tree == NULL 
      || *tree == NULL
      || compare_key_func == NULL)
    return (NULL);
  it = *tree;
  while (it)
    {
      ret = compare_key_func(key, it);
      if (ret < 0)
	it = GET_FIELD(it, m, splay_tree_t)->left;
      else
	{
	  if (ret > 0)
	    it = GET_FIELD(it, m, splay_tree_t)->right;
	  else
	    {
	      /* we have found the good node. Splay the tree. */
	      splay(tree, it, m);
	      break;
	    }
	}
    }
  return (it);
}

bool	_splay_tree_insert(void **tree,
			   void *new, 
			   unsigned int m,
			   tree_compare_p compare_func)
{
  void	*it;
  void	*prev_it;
  int	ret;

  if (tree == NULL
      || new == NULL
      || compare_func == NULL)
    return (false);
  GET_FIELD(new, m, splay_tree_t)->parent = NULL;
  GET_FIELD(new, m, splay_tree_t)->left = NULL;
  GET_FIELD(new, m, splay_tree_t)->right = NULL;
  if (*tree == NULL)
    *tree = new;
  else
    {
      prev_it = NULL;
      it = *tree;
      while (1)
	{
	  ret = compare_func(new, it);
	  if (ret < 0)
	    {
	      if (GET_FIELD(it, m, splay_tree_t)->left == NULL)
		{
		  GET_FIELD(it, m, splay_tree_t)->left = new;
		  GET_FIELD(new, m, splay_tree_t)->parent = it;
		  break;
		}
	      else
		{
		  prev_it = it;
		  it = GET_FIELD(it, m, splay_tree_t)->left;
		}
	    }
	  else
	    {
	      if (ret > 0)
		{
		  if (GET_FIELD(it, m, splay_tree_t)->right == NULL)
		    {
		      GET_FIELD(it, m, splay_tree_t)->right = new;
		      GET_FIELD(new, m, splay_tree_t)->parent = it;
		      break;
		    }
		  else
		    {
		      prev_it = it;
		      it = GET_FIELD(it, m, splay_tree_t)->right;
		    }
		}
	      else
		return (false);
	    }
	}
    }
/*   if (prev_it) */
/*     splay(tree, new, m); */
  return (true);
}

bool	_splay_tree_remove(void **tree,
			   void *key, 
			   unsigned int m, 
			   tree_compare_p compare_func,
			   tree_compare_key_p compare_key_func)
{
  void	*prev_it;
  void	*it;
  int	ret;

  if (tree == NULL
      || compare_key_func == NULL)
    return (false);
  prev_it = NULL;
  it = *tree;
  while (it)
    {
      ret = compare_key_func(key, it);
      if (ret < 0)
	{
	  prev_it = it;
	  it = GET_FIELD(it, m, splay_tree_t)->left;
	}
      else
	{
	  if (ret > 0)
	    {
	      prev_it = it;
	      it = GET_FIELD(it, m, splay_tree_t)->right;
	    }
	  else
	    {
	      /* We found the node. */
	      if (GET_FIELD(it, m, splay_tree_t)->left == NULL &&
		  GET_FIELD(it, m, splay_tree_t)->right == NULL)
		{
		  if (prev_it == NULL)
		    *tree = NULL;
		  else
		    {
		      GET_FIELD(it, m, splay_tree_t)->parent = NULL;
		      if (GET_FIELD(prev_it, m, splay_tree_t)->left == it)
			GET_FIELD(prev_it, m, splay_tree_t)->left = NULL;
		      else
			GET_FIELD(prev_it, m, splay_tree_t)->right = NULL;
		    }
		}
	      else
		{
		  if (GET_FIELD(it, m, splay_tree_t)->left != NULL &&
		      GET_FIELD(it, m, splay_tree_t)->right != NULL)
		    {
		      void	*lp;
		      void	*lpp;
		      void	*rp;
		      void	*rpp;

		      lpp = NULL;
		      lp = GET_FIELD(it, m, splay_tree_t)->left;
		      while (GET_FIELD(lp, m, splay_tree_t)->right)
			{
			  lpp = lp;
			  lp = GET_FIELD(lp, m, splay_tree_t)->right;
			}
		      rpp = NULL;
		      rp = GET_FIELD(it, m, splay_tree_t)->right;
		      while (GET_FIELD(rp, m, splay_tree_t)->left)
			{
			  rpp = rp;
			  rp = GET_FIELD(rp, m, splay_tree_t)->left;
			}
		      if (compare_func(it, lp) <= compare_func(rp, it))
			{
			  /* we choose left. */
			  GET_FIELD(lpp, m, splay_tree_t)->right = GET_FIELD(lp, m, splay_tree_t)->left;
			  GET_FIELD(GET_FIELD(lp, m, splay_tree_t)->left, m, splay_tree_t)->parent = lpp;
			  if (prev_it == NULL)
			    *tree = lp;
			  else
			    {
			      GET_FIELD(lp, m, splay_tree_t)->parent = prev_it;
			      if (GET_FIELD(prev_it, m, splay_tree_t)->left == it)
				GET_FIELD(prev_it, m, splay_tree_t)->left = lp;
			      else
				GET_FIELD(prev_it, m, splay_tree_t)->right = lp;
			    }
			  GET_FIELD(lp, m, splay_tree_t)->left = GET_FIELD(it, m, splay_tree_t)->left;
			  GET_FIELD(it, m, splay_tree_t)->parent = NULL;
			}
		      else
			{
			  /* we choose right. */
			  GET_FIELD(rpp, m, splay_tree_t)->left = GET_FIELD(rp, m, splay_tree_t)->right;
			  GET_FIELD(GET_FIELD(rp, m, splay_tree_t)->left, m, splay_tree_t)->parent = rpp;
			  if (prev_it == NULL)
			    *tree = rp;
			  else
			    {
			      GET_FIELD(rp, m, splay_tree_t)->parent = prev_it;
			      if (GET_FIELD(prev_it, m, splay_tree_t)->left == it)
				GET_FIELD(prev_it, m, splay_tree_t)->left = rp;
			      else
				GET_FIELD(prev_it, m, splay_tree_t)->right = rp;
			    }
			  GET_FIELD(rp, m, splay_tree_t)->right = GET_FIELD(it, m, splay_tree_t)->right;
			  GET_FIELD(it, m, splay_tree_t)->parent = NULL;
			}
		    }
		  else
		    {
		      GET_FIELD(it, m, splay_tree_t)->parent = prev_it;
		      if (GET_FIELD(it, m, splay_tree_t)->left != NULL)
			{
			  if (prev_it == NULL)
			    *tree = GET_FIELD(it, m, splay_tree_t)->left;
			  else
			    {
			      if (GET_FIELD(prev_it, m, splay_tree_t)->left == it)
				GET_FIELD(prev_it, m, splay_tree_t)->left = GET_FIELD(it, m, splay_tree_t)->left;
			      else
				GET_FIELD(prev_it, m, splay_tree_t)->right = GET_FIELD(it, m, splay_tree_t)->left;
			    }
			}
		      else
			{
			  if (prev_it == NULL)
			    *tree = GET_FIELD(it, m, splay_tree_t)->right;
			  else
			    {
			      if (GET_FIELD(prev_it, m, splay_tree_t)->left == it)
				GET_FIELD(prev_it, m, splay_tree_t)->left = GET_FIELD(it, m, splay_tree_t)->right;
			      else
				GET_FIELD(prev_it, m, splay_tree_t)->right = GET_FIELD(it, m, splay_tree_t)->right;
			    }
			}
		    }
		}
	      if (prev_it)
		splay(tree, prev_it, m);
	      return (true);
	    }
	}
    }
  return (false);
}
