# this is the library target
add_library(libeverfit src/everfit.cpp)
target_include_directories(libeverfit PUBLIC ${LIB_INCLUDE_DIR})
target_compile_options(libeverfit PUBLIC -Werror -Wall -Wextra)