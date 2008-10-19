 

/* This is auto-generated code. Edit at your own peril. */

#include <stdio.h>

#include "CuTest.h"


extern void Testbinary_tree_init(CuTest*);
extern void Testbinary_tree_insert(CuTest*);
extern void Testbinary_tree_lookup(CuTest*);
extern void Testbinary_tree_remove(CuTest*);
extern void Testbinary_tree_walk_preorder(CuTest*);
extern void Testbinary_tree_walk_inorder(CuTest*);
extern void Testbinary_tree_walk_postorder(CuTest*);
extern void Testbinary_tree_graft(CuTest*);
extern void Testbinary_tree_prune(CuTest*);
extern void Testnary_tree_init(CuTest*);
extern void Testnary_tree_insert(CuTest*);
extern void Testnary_tree_lookup(CuTest*);
extern void Testnary_tree_remove(CuTest*);
extern void Testnary_tree_walk_preorder(CuTest*);
extern void Testnary_tree_walk_inorder(CuTest*);
extern void Testnary_tree_walk_postorder(CuTest*);
extern void Testnary_tree_graft(CuTest*);
extern void Testnary_tree_prune(CuTest*);
extern void Teststack(CuTest*);
extern void Testqueue(CuTest*);
extern void Testslist(CuTest*);
extern void Testclist(CuTest*);
extern void Testdlist(CuTest*);
extern void Testhashtable_init(CuTest*);
extern void Testhashtable_insert(CuTest*);
extern void Testhashtable_lookup(CuTest*);
extern void Testhashtable_remove(CuTest*);


void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();


    SUITE_ADD_TEST(suite, Testbinary_tree_init);
    SUITE_ADD_TEST(suite, Testbinary_tree_insert);
    SUITE_ADD_TEST(suite, Testbinary_tree_lookup);
    SUITE_ADD_TEST(suite, Testbinary_tree_remove);
    SUITE_ADD_TEST(suite, Testbinary_tree_walk_preorder);
    SUITE_ADD_TEST(suite, Testbinary_tree_walk_inorder);
    SUITE_ADD_TEST(suite, Testbinary_tree_walk_postorder);
    SUITE_ADD_TEST(suite, Testbinary_tree_graft);
    SUITE_ADD_TEST(suite, Testbinary_tree_prune);
    SUITE_ADD_TEST(suite, Testnary_tree_init);
    SUITE_ADD_TEST(suite, Testnary_tree_insert);
    SUITE_ADD_TEST(suite, Testnary_tree_lookup);
    SUITE_ADD_TEST(suite, Testnary_tree_remove);
    SUITE_ADD_TEST(suite, Testnary_tree_walk_preorder);
    SUITE_ADD_TEST(suite, Testnary_tree_walk_inorder);
    SUITE_ADD_TEST(suite, Testnary_tree_walk_postorder);
    SUITE_ADD_TEST(suite, Testnary_tree_graft);
    SUITE_ADD_TEST(suite, Testnary_tree_prune);
    SUITE_ADD_TEST(suite, Teststack);
    SUITE_ADD_TEST(suite, Testqueue);
    SUITE_ADD_TEST(suite, Testslist);
    SUITE_ADD_TEST(suite, Testclist);
    SUITE_ADD_TEST(suite, Testdlist);
    SUITE_ADD_TEST(suite, Testhashtable_init);
    SUITE_ADD_TEST(suite, Testhashtable_insert);
    SUITE_ADD_TEST(suite, Testhashtable_lookup);
    SUITE_ADD_TEST(suite, Testhashtable_remove);

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

