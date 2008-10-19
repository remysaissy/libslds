/*
** This file is part of libslds

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__LIBSLDS_HASH_H__
#define	__LIBSLDS_HASH_H__

#include	<stddef.h>
#include	<stdbool.h>

#include	"common.h"
#include	"list.h"

/*
 * Hashtable data structure:
 *  - hashtable_t
 *
 * How to use the hashtables:
 * Every data structure has an optional macro parameter: the hash parameter.
 * This parameter allows your implementation to use several hashtables in the
 * same host data structure but if you leave it empty, the macro simply
 * assume that the hash data structure is located at the very beginning of
 * the data structure.
 * NOTE: For now, the parameter is mandatory because I don't know how to
 * check for an empty parameter with cpp.
 */

/* Data structures */

/**
 * \brief	A basic data type to be included in every data structure that
 *		that expect to be used in a hashtable.
 */
typedef slist_t	hashtable_t;

/* This is the hashing function. */
/* It returns and uint32_t */
/* #define	HASHING_FUNCTION(key) */

/* Comparison between two entries during a lookup */
/* returns 0 if equal. */
/* #define	HASHING_COMPARE(key, elem) */

typedef unsigned int (*hashing_function_p)(void *key);
typedef unsigned int (*hashing_compare_p)(void *key, void *it);

/* Hashtable */

#define	hashtable_init(hash, n)					\
 _hashtable_init((void **)(hash), (n))


#define	hashtable_insert(hash, key, content, m, hash_func)	\
 _hashtable_insert((void **)(hash),				\
		   (void *)(key),				\
		   (void *)(content),				\
		   (int)offsetof(typeof(**(hash)), m),		\
		   (hash_func))

#define	hashtable_lookup(hash, key, m, hash_func, hash_comp)	\
 _hashtable_lookup((void **)(hash),				\
		   (void *)(key),				\
		   (int)offsetof(typeof(**(hash)), m),		\
		   (hash_func),					\
		   (hash_comp))

#define	hashtable_remove(hash, key, entry, m, hash_func)	\
 _hashtable_remove((void **)(hash),				\
		   (void *)(key),				\
		   (void *)(entry),				\
		   (int)offsetof(typeof(**(hash)), m),		\
		   (hash_func))


/* hashtable implementation. */

bool	_hashtable_init(void **hash, int n);

bool	_hashtable_insert(void **hash,
			  void *key,
			  void *content,
			  int m,
			  hashing_function_p hash_func);

void	*_hashtable_lookup(void **hash,
			   void *key,
			   int m,
			   hashing_function_p hash_func,
			   hashing_compare_p hash_comp);

bool	_hashtable_remove(void **hash,
			  void *key,
			  void *entry,
			  int m,
			  hashing_function_p hash_func);

#endif /* __LIBSLDS_HASH_H__ */
