cmake_minimum_required(VERSION 3.10.0)
project(everfit VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(LIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/library/include)
set(LIB_SRC_DIR ${PROJECT_SOURCE_DIR}/library/src)


# this is the library target
add_library(libeverfit library/src/everfit.cpp)
target_include_directories(libeverfit PUBLIC ${LIB_INCLUDE_DIR})
target_compile_options(libeverfit PUBLIC -Werror -Wall -Wextra)
if(MSVC)
set(LIB_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}libeverfit.lib)
else()
set(LIB_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libeverfit.lib)
endif()


# this is the preprocessor target
add_executable(everfit preprocessor/preprocessor.cpp)
target_include_directories(everfit PUBLIC ${LIB_INCLUDE_DIR})
target_link_directories(everfit PUBLIC ${LIB_INCLUDE_DIR})
target_link_libraries(everfit PUBLIC libeverfit)
add_dependencies(everfit libeverfit)



# tests
add_executable(test_code_stream test/code_stream.cpp)
target_include_directories(test_code_stream PUBLIC ${LIB_SRC_DIR})
add_test(test_code_stream test_code_stream)
target_link_directories(test_code_stream PUBLIC ${LIB_INCLUDE_DIR})
target_link_libraries(test_code_stream PUBLIC libeverfit)
add_dependencies(test_code_stream libeverfit)