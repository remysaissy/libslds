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
#define	__LIBSLDS_TREE_H__

/* This is the generic header for trees. */

#include	<stdbool.h>
#include	<stdint.h>
#include	<stddef.h>

/** Comparison function.  */
/* TREE_COMPARE(n1, n2) */
/* This macro should return the */
/* following values. */
/*  < 0 n1 is smaller than n2 */
/*  0   n1 and n2 are equal */
/*  > 0 n1 is greater than n2 */
typedef int (*tree_compare_p)(void *n1, void *n2);
typedef int (*tree_compare_key_p)(void *key, void *n2);

#include	"common.h"

#include	"btree.h"
#include	"splay_tree.h"

#endif /* __LIBSLDS_TREE_H__ */
