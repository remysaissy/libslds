
include_directories(${libslds_SOURCE_DIR}/src/include)

add_library(hash OBJECT hash.c integer_hashing.c string_hashing.c)