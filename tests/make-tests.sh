#!/usr/bin/env bash

# Auto generate single AllTests file for CuTest.
# Searches through all *.c files in the current directory.
# Prints to stdout.
# Author: Asim Jalis
# Date: 01/08/2003

FILES=`find $1 -type f -name '*.c'`
#if test $# -eq 0 ; then FILES=*.c ; else FILES=$* ; fi

output="$1/AllTests.c"

echo ' 

/* This is auto-generated code. Edit at your own peril. */

#include <stdio.h>

#include "CuTest.h"

' > $output

cat $FILES | grep '^void[ \t]*Test' | 
    sed -e 's/(.*$//' \
        -e 's/$/(CuTest*);/' \
        -e 's/^/extern /' >> $output

echo \
'

void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

' >> $output
cat $FILES | grep '^void Test' | 
    sed -e 's/^void //' \
        -e 's/(.*$//' \
        -e 's/^/    SUITE_ADD_TEST(suite, /' \
        -e 's/$/);/' >> $output
echo \
'
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main(void)
{
    RunAllTests();
    return (0);
}
' >> $output
