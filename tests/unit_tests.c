/* 
 * This file is part of ExAmour

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

#include	<stdbool.h>
#include	<stdint.h>
#include	<stdio.h>
#include	<stdlib.h>

#include	"unit_tests.h"

bool	do_lists(void);
bool	do_hashs(void);
bool	do_trees(void);

static const unit_tests_t	unit_tests[] =
  {
    {"Lists", do_lists},
    {"Hashs", do_hashs},
    {"Trees", do_trees},
    {NULL, NULL}
  };


int		main(int argc, char **argv)
{
  uint32_t	i;
  int		ret;

  ret = 0;
  for (i = 0; unit_tests[i].test_desc != NULL; i++)
    {
      printf("Testing %s\n", unit_tests[i].test_desc);
      if (unit_tests[i].test_func() == true)
	printf("%s succeeded.\n", unit_tests[i].test_desc);
      else
	{
	  printf("%s failed.\n", unit_tests[i].test_desc);
	  ret = 1;
	}
    }
  return (0);
}
