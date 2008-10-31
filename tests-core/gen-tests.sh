#!/usr/bin/env bash
## This file is part of libslds

## Copyright (C) Remy Saissy <remy.saissy@gmail.com>
## libslds is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## libslds is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


if [ "$1" == "" ];
then
    echo "Usage: $0 <root path to scan.>"
    echo "Please note that the root path is the Libslds project root path."
    echo "Data scanned are written in the test-core/Alltests.c file."
    exit;
fi

DIRS="`find $1 -maxdepth 1 -type d -not -name '.*' -and -not -name '*include*' -and -not -name 'libslds' -and -not -name 'tests-core' -printf \"%h/%f \"`"
OUTPUT="$1/tests-core/AllTests.c"

echo "$DIRS"

echo "/* DOT NOT EDIT. Code generated by $0. $1 */


#include <stdio.h>

/* The CUnit test library header. */
#include <CuTest.h>

" > $OUTPUT

# Each directory is a component... a test suite.
# First, create a full listing of function declaration.
for entry in $DIRS;
do
  TESTS="`find $entry -type d -name 'tests' -printf \"%h/%f \"`"
  for tst in $TESTS;
  do
    cat $tst/*.c | egrep -i "^void[ \t]+test" | 
    sed -e 's/^void//' \
        -e 's/(.*$//' \
        -e 's/$/(CuTest*);/' \
        -e 's/^/extern void/' >> $OUTPUT
  done
done

# Now, create the main function.
echo \
'

void RunAllTests(void) 
{
' >> $OUTPUT

for entry in $DIRS;
do
  suite="`basename $entry`"
  echo \
"   CuString *output_$suite = CuStringNew();
    CuSuite* suite_$suite = CuSuiteNew();" >> $OUTPUT
done

# Add tests.
for entry in $DIRS;
do
  echo >> $OUTPUT
  suite="`basename $entry`"
  TESTS="`find $entry -type d -name 'tests' -printf \"%h/%f \"`"
  for tst in $TESTS;
  do
    cat $tst/*.c | egrep -i '^void[ \t]+test' | 
    sed -e 's/void//' \
        -e 's/(.*$//' \
        -e "s/^/    SUITE_ADD_TEST(suite_$suite, /" \
        -e 's/$/);/' >> $OUTPUT
  done
done

# Run tests.
for entry in $DIRS;
do
  suite="`basename $entry`"
echo \
"
    CuSuiteRun(suite_$suite);
    printf(\"$suite test results:\\n\");
    CuSuiteSummary(suite_$suite, output_$suite);
    CuSuiteDetails(suite_$suite, output_$suite);" >> $OUTPUT
echo "    printf(\"%s\\n\", output_$suite->buffer);" >> $OUTPUT
done

echo \
'
}

int main(void)
{
    RunAllTests();
    return (0);
}
' >> $OUTPUT

