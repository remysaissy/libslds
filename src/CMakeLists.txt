
add_subdirectory(hash)
add_subdirectory(list)
add_subdirectory(tree)

add_library(slds $<TARGET_OBJECTS:hash> $<TARGET_OBJECTS:list> $<TARGET_OBJECTS:tree_binary> $<TARGET_OBJECTS:tree_nary>)