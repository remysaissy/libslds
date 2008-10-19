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

#include	<stdlib.h>
#include	<string.h>

#include	<CuTest.h>

#include	<list.h>

typedef struct	list_test_s
{
  dlist_t	dlist;

}				list_test_t;

void Testdlist(CuTest *tc)
{
  list_test_t	*root = NULL;
  list_test_t	elem;
  list_test_t	elem2;
  list_test_t	elem3;

  dlist_init(root, dlist);
  dlist_add_head(root, &elem, dlist);
  CuAssertPtrEquals(tc, &elem, root);
  dlist_add_after(root, &elem, &elem2, dlist);
  CuAssertPtrEquals(tc, &elem, root);
  dlist_add_before(root, &elem, &elem3, dlist);
  CuAssertPtrEquals(tc, &elem3, root);
  dlist_remove(root, root, dlist);
  CuAssertPtrEquals(tc, &elem, root);
  dlist_remove(root, root, dlist);
  CuAssertPtrEquals(tc, &elem2, root);
  dlist_remove(root, root, dlist);
  CuAssertPtrEquals(tc, NULL, root);
  dlist_remove(root, root, dlist);
}
