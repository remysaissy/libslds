
include_directories(${libslds_SOURCE_DIR}/src/include)

add_library(list OBJECT clist.c dlist.c slist.c)