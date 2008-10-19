 

/* This is auto-generated code. Edit at your own peril. */

#include <stdio.h>

#include "CuTest.h"


extern void Teststack_init(CuTest*);
extern void Teststack_push(CuTest*);
extern void Teststack_push_with_invalid_new(CuTest*);
extern void Teststack_pop(CuTest*);
extern void Teststack_pop_with_invalid_item(CuTest*);
extern void Testclist_init(CuTest*);
extern void Testclist_init_with_null_pointer(CuTest*);
extern void Testclist_insert_after(CuTest*);
extern void Testclist_insert_after_with_invalid_root(CuTest*);
extern void Testclist_insert_after_with_invalid_new(CuTest*);
extern void Testclist_insert_before(CuTest*);
extern void Testclist_insert_before_with_null_before(CuTest*);
extern void Testclist_insert_before_with_not_null_before(CuTest*);
extern void Testclist_insert_before_with_invalid_root(CuTest*);
extern void Testclist_insert_before_with_invalid_new(CuTest*);
extern void Testclist_remove(CuTest*);
extern void Testclist_remove_with_invalid_root(CuTest*);
extern void Testclist_remove_with_invalid_item(CuTest*);
extern void Testqueue_init(CuTest*);
extern void Testqueue_add(CuTest*);
extern void Testqueue_add_with_null_before(CuTest*);
extern void Testqueue_add_with_not_null_before(CuTest*);
extern void Testqueue_add_with_invalid_new(CuTest*);
extern void Testqueue_remove(CuTest*);
extern void Testqueue_remove_with_invalid_item(CuTest*);
extern void Testdlist_init(CuTest*);
extern void Testdlist_init_with_null_pointer(CuTest*);
extern void Testdlist_add_head(CuTest*);
extern void Testdlist_add_head_with_invalid_root(CuTest*);
extern void Testdlist_add_head_with_invalid_new(CuTest*);
extern void Testdlist_insert_after(CuTest*);
extern void Testdlist_insert_after_with_null_after(CuTest*);
extern void Testdlist_insert_after_with_not_null_after(CuTest*);
extern void Testdlist_insert_after_with_invalid_root(CuTest*);
extern void Testdlist_insert_after_with_invalid_new(CuTest*);
extern void Testdlist_insert_before(CuTest*);
extern void Testdlist_insert_before_with_null_before(CuTest*);
extern void Testdlist_insert_before_with_not_null_before(CuTest*);
extern void Testdlist_insert_before_with_invalid_root(CuTest*);
extern void Testdlist_insert_before_with_invalid_new(CuTest*);
extern void Testdlist_remove(CuTest*);
extern void Testdlist_remove_with_invalid_root(CuTest*);
extern void Testdlist_remove_with_invalid_item(CuTest*);
extern void Testslist_init(CuTest*);
extern void Testslist_init_with_null_pointer(CuTest*);
extern void Testslist_add_head(CuTest*);
extern void Testslist_add_head_with_invalid_root(CuTest*);
extern void Testslist_add_head_with_invalid_new(CuTest*);
extern void Testslist_insert_after(CuTest*);
extern void Testslist_insert_after_with_null_after(CuTest*);
extern void Testslist_insert_after_with_not_null_after(CuTest*);
extern void Testslist_insert_after_with_invalid_root(CuTest*);
extern void Testslist_insert_after_with_invalid_new(CuTest*);
extern void Testslist_remove(CuTest*);
extern void Testslist_remove_with_invalid_root(CuTest*);
extern void Testslist_remove_with_invalid_item(CuTest*);
extern void Testslist_fast_remove(CuTest*);
extern void Testslist_fast_remove_with_null_plist(CuTest*);
extern void Testslist_fast_remove_with_invalid_root(CuTest*);
extern void Testslist_fast_remove_with_invalid_slist(CuTest*);
extern void Testnary_tree_init(CuTest*);
extern void Testnary_tree_insert(CuTest*);
extern void Testnary_tree_lookup(CuTest*);
extern void Testnary_tree_remove(CuTest*);
extern void Testnary_tree_walk_preorder(CuTest*);
extern void Testnary_tree_walk_inorder(CuTest*);
extern void Testnary_tree_walk_postorder(CuTest*);
extern void Testnary_tree_graft(CuTest*);
extern void Testnary_tree_prune(CuTest*);
extern void Testbinary_tree_init(CuTest*);
extern void Testbinary_tree_insert(CuTest*);
extern void Testbinary_tree_lookup(CuTest*);
extern void Testbinary_tree_remove(CuTest*);
extern void Testbinary_tree_walk_preorder(CuTest*);
extern void Testbinary_tree_walk_inorder(CuTest*);
extern void Testbinary_tree_walk_postorder(CuTest*);
extern void Testbinary_tree_graft(CuTest*);
extern void Testbinary_tree_prune(CuTest*);
extern void Testhashtable_init(CuTest*);
extern void Testhashtable_insert(CuTest*);
extern void Testhashtable_lookup(CuTest*);
extern void Testhashtable_remove(CuTest*);


void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();


    SUITE_ADD_TEST(suite, Teststack_init);
    SUITE_ADD_TEST(suite, Teststack_push);
    SUITE_ADD_TEST(suite, Teststack_push_with_invalid_new);
    SUITE_ADD_TEST(suite, Teststack_pop);
    SUITE_ADD_TEST(suite, Teststack_pop_with_invalid_item);
    SUITE_ADD_TEST(suite, Testclist_init);
    SUITE_ADD_TEST(suite, Testclist_init_with_null_pointer);
    SUITE_ADD_TEST(suite, Testclist_insert_after);
    SUITE_ADD_TEST(suite, Testclist_insert_after_with_invalid_root);
    SUITE_ADD_TEST(suite, Testclist_insert_after_with_invalid_new);
    SUITE_ADD_TEST(suite, Testclist_insert_before);
    SUITE_ADD_TEST(suite, Testclist_insert_before_with_null_before);
    SUITE_ADD_TEST(suite, Testclist_insert_before_with_not_null_before);
    SUITE_ADD_TEST(suite, Testclist_insert_before_with_invalid_root);
    SUITE_ADD_TEST(suite, Testclist_insert_before_with_invalid_new);
    SUITE_ADD_TEST(suite, Testclist_remove);
    SUITE_ADD_TEST(suite, Testclist_remove_with_invalid_root);
    SUITE_ADD_TEST(suite, Testclist_remove_with_invalid_item);
    SUITE_ADD_TEST(suite, Testqueue_init);
    SUITE_ADD_TEST(suite, Testqueue_add);
    SUITE_ADD_TEST(suite, Testqueue_add_with_null_before);
    SUITE_ADD_TEST(suite, Testqueue_add_with_not_null_before);
    SUITE_ADD_TEST(suite, Testqueue_add_with_invalid_new);
    SUITE_ADD_TEST(suite, Testqueue_remove);
    SUITE_ADD_TEST(suite, Testqueue_remove_with_invalid_item);
    SUITE_ADD_TEST(suite, Testdlist_init);
    SUITE_ADD_TEST(suite, Testdlist_init_with_null_pointer);
    SUITE_ADD_TEST(suite, Testdlist_add_head);
    SUITE_ADD_TEST(suite, Testdlist_add_head_with_invalid_root);
    SUITE_ADD_TEST(suite, Testdlist_add_head_with_invalid_new);
    SUITE_ADD_TEST(suite, Testdlist_insert_after);
    SUITE_ADD_TEST(suite, Testdlist_insert_after_with_null_after);
    SUITE_ADD_TEST(suite, Testdlist_insert_after_with_not_null_after);
    SUITE_ADD_TEST(suite, Testdlist_insert_after_with_invalid_root);
    SUITE_ADD_TEST(suite, Testdlist_insert_after_with_invalid_new);
    SUITE_ADD_TEST(suite, Testdlist_insert_before);
    SUITE_ADD_TEST(suite, Testdlist_insert_before_with_null_before);
    SUITE_ADD_TEST(suite, Testdlist_insert_before_with_not_null_before);
    SUITE_ADD_TEST(suite, Testdlist_insert_before_with_invalid_root);
    SUITE_ADD_TEST(suite, Testdlist_insert_before_with_invalid_new);
    SUITE_ADD_TEST(suite, Testdlist_remove);
    SUITE_ADD_TEST(suite, Testdlist_remove_with_invalid_root);
    SUITE_ADD_TEST(suite, Testdlist_remove_with_invalid_item);
    SUITE_ADD_TEST(suite, Testslist_init);
    SUITE_ADD_TEST(suite, Testslist_init_with_null_pointer);
    SUITE_ADD_TEST(suite, Testslist_add_head);
    SUITE_ADD_TEST(suite, Testslist_add_head_with_invalid_root);
    SUITE_ADD_TEST(suite, Testslist_add_head_with_invalid_new);
    SUITE_ADD_TEST(suite, Testslist_insert_after);
    SUITE_ADD_TEST(suite, Testslist_insert_after_with_null_after);
    SUITE_ADD_TEST(suite, Testslist_insert_after_with_not_null_after);
    SUITE_ADD_TEST(suite, Testslist_insert_after_with_invalid_root);
    SUITE_ADD_TEST(suite, Testslist_insert_after_with_invalid_new);
    SUITE_ADD_TEST(suite, Testslist_remove);
    SUITE_ADD_TEST(suite, Testslist_remove_with_invalid_root);
    SUITE_ADD_TEST(suite, Testslist_remove_with_invalid_item);
    SUITE_ADD_TEST(suite, Testslist_fast_remove);
    SUITE_ADD_TEST(suite, Testslist_fast_remove_with_null_plist);
    SUITE_ADD_TEST(suite, Testslist_fast_remove_with_invalid_root);
    SUITE_ADD_TEST(suite, Testslist_fast_remove_with_invalid_slist);
    SUITE_ADD_TEST(suite, Testnary_tree_init);
    SUITE_ADD_TEST(suite, Testnary_tree_insert);
    SUITE_ADD_TEST(suite, Testnary_tree_lookup);
    SUITE_ADD_TEST(suite, Testnary_tree_remove);
    SUITE_ADD_TEST(suite, Testnary_tree_walk_preorder);
    SUITE_ADD_TEST(suite, Testnary_tree_walk_inorder);
    SUITE_ADD_TEST(suite, Testnary_tree_walk_postorder);
    SUITE_ADD_TEST(suite, Testnary_tree_graft);
    SUITE_ADD_TEST(suite, Testnary_tree_prune);
    SUITE_ADD_TEST(suite, Testbinary_tree_init);
    SUITE_ADD_TEST(suite, Testbinary_tree_insert);
    SUITE_ADD_TEST(suite, Testbinary_tree_lookup);
    SUITE_ADD_TEST(suite, Testbinary_tree_remove);
    SUITE_ADD_TEST(suite, Testbinary_tree_walk_preorder);
    SUITE_ADD_TEST(suite, Testbinary_tree_walk_inorder);
    SUITE_ADD_TEST(suite, Testbinary_tree_walk_postorder);
    SUITE_ADD_TEST(suite, Testbinary_tree_graft);
    SUITE_ADD_TEST(suite, Testbinary_tree_prune);
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

