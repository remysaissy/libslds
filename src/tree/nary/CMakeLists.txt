
include_directories(${libslds_SOURCE_DIR}/src/include)

add_library(tree_nary OBJECT 234_tree.c 23_tree.c ab_tree.c b_tree.c bplus_tree.c bstar_tree.c common.c fusion_tree.c gist_tree.c hilbert_rtree.c nary_tree.c oc_tree.c quad_tree.c r_tree.c rplus_tree.c rstar_tree.c ternary_tree.c top_tree.c tpyramid_tree.c trie_tree.c ub_tree.c)
