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

#include	<tree.h>

bool	_btree_init(void *tree, unsigned int m)
{
  if (tree)
    {
      GET_FIELD(tree, m, btree_t)->left = NULL;
      GET_FIELD(tree, m, btree_t)->right = NULL;
      return (true);
    }
  return (false);
}

void	*_btree_lookup(void **tree,
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
	it = GET_FIELD(it, m, btree_t)->left;
      else
	{
	  if (ret > 0)
	    it = GET_FIELD(it, m, btree_t)->right;
	  else
	    break;
	}
    }
  return (it);
}

bool	_btree_insert(void **tree,
		      void *new,
		      unsigned int m,
		      tree_compare_p compare_func)
{
  void	*it;
  int	ret;

  if (tree == NULL
      || new == NULL
      || compare_func == NULL)
    return (false);
  GET_FIELD(new, m, btree_t)->left = NULL;
  GET_FIELD(new, m, btree_t)->right = NULL;
  if (*tree == NULL)
    *tree = new;
  else
    {
      it = *tree;
      while (1)
	{
	  ret = compare_func(new, it);
	  if (ret < 0)
	    {
	      if (GET_FIELD(it, m, btree_t)->left == NULL)
		{
		  GET_FIELD(it, m, btree_t)->left = new;
		  break;
		}
	      else
		it = GET_FIELD(it, m, btree_t)->left;
	    }
	  else
	    {
	      if (ret > 0)
		{
		  if (GET_FIELD(it, m, btree_t)->right == NULL)
		    {
		      GET_FIELD(it, m, btree_t)->right = new;
		      break;
		    }
		  else
		    it = GET_FIELD(it, m, btree_t)->right;
		}
	      else
		return (false);
	    }
	}
    }
  return (true);
}

bool	_btree_remove(void **tree,
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
	  it = GET_FIELD(it, m, btree_t)->left;
	}
      else
	{
	  if (ret > 0)
	    {
	      prev_it = it;
	      it = GET_FIELD(it, m, btree_t)->right;
	    }
	  else
	    {
	      if (GET_FIELD(it, m, btree_t)->left == NULL &&
		  GET_FIELD(it, m, btree_t)->right == NULL)
		{
		  if (prev_it == NULL)
		    *tree = NULL;
		  else
		    {
		      if (GET_FIELD(prev_it, m, btree_t)->left == it)
			GET_FIELD(prev_it, m, btree_t)->left = NULL;
		      else
			GET_FIELD(prev_it, m, btree_t)->right = NULL;
		    }
		}
	      else
		{
		  if (GET_FIELD(it, m, btree_t)->left != NULL &&
		      GET_FIELD(it, m, btree_t)->right != NULL)
		    {
		      void	*lp;
		      void	*lpp;
		      void	*rp;
		      void	*rpp;

		      lpp = NULL;
		      lp = GET_FIELD(it, m, btree_t)->left;
		      while (GET_FIELD(lp, m, btree_t)->right)
			{
			  lpp = lp;
			  lp = GET_FIELD(lp, m, btree_t)->right;
			}
		      rpp = NULL;
		      rp = GET_FIELD(it, m, btree_t)->right;
		      while (GET_FIELD(rp, m, btree_t)->left)
			{
			  rpp = rp;
			  rp = GET_FIELD(rp, m, btree_t)->left;
			}
		      if (compare_func(it, lp) <= compare_func(rp, it))
			{
			  /* we choose left. */
			  GET_FIELD(lpp, m, btree_t)->right = GET_FIELD(lp, m, btree_t)->left;
			  if (prev_it == NULL)
			    *tree = lp;
			  else
			    {
			      if (GET_FIELD(prev_it, m, btree_t)->left == it)
				GET_FIELD(prev_it, m, btree_t)->left = lp;
			      else
				GET_FIELD(prev_it, m, btree_t)->right = lp;
			    }
			  GET_FIELD(lp, m, btree_t)->left = GET_FIELD(it, m, btree_t)->left;
			}
		      else
			{
			  /* we choose right. */
			  GET_FIELD(rpp, m, btree_t)->left = GET_FIELD(rp, m, btree_t)->right;
			  if (prev_it == NULL)
			    *tree = rp;
			  else
			    {
			      if (GET_FIELD(prev_it, m, btree_t)->left == it)
				GET_FIELD(prev_it, m, btree_t)->left = rp;
			      else
				GET_FIELD(prev_it, m, btree_t)->right = rp;
			    }
			  GET_FIELD(rp, m, btree_t)->right = GET_FIELD(it, m, btree_t)->right;
			}
		    }
		  else
		    {
		      if (GET_FIELD(it, m, btree_t)->left != NULL)
			{
			  if (prev_it == NULL)
			    *tree = GET_FIELD(it, m, btree_t)->left;
			  else
			    {
			      if (GET_FIELD(prev_it, m, btree_t)->left == it)
				GET_FIELD(prev_it, m, btree_t)->left = GET_FIELD(it, m, btree_t)->left;
			      else
				GET_FIELD(prev_it, m, btree_t)->right = GET_FIELD(it, m, btree_t)->left;
			    }
			}
		      else
			{
			  if (prev_it == NULL)
			    *tree = GET_FIELD(it, m, btree_t)->right;
			  else
			    {
			      if (GET_FIELD(prev_it, m, btree_t)->left == it)
				GET_FIELD(prev_it, m, btree_t)->left = GET_FIELD(it, m, btree_t)->right;
			      else
				GET_FIELD(prev_it, m, btree_t)->right = GET_FIELD(it, m, btree_t)->right;
			    }
			}
		    }
		}
	      return (true);
	    }
	}
    }
  return (false);
}
