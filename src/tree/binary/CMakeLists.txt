
include_directories(${libslds_SOURCE_DIR}/src/include)

add_library(tree_binary OBJECT aa_tree.c avl_rotation.c bst_tree.c ebst_tree.c kd_tree.c left_child_right_sibling_tree.c radix_tree.c randomized_btree.c redblack_tree.c scapegoat_tree.c splay_tree.c t_tree.c treap.c weight_balanced_tree.c)
