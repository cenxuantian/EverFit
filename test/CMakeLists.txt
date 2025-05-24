# tests
add_executable(test_code_stream code_stream.cpp)
target_include_directories(test_code_stream PUBLIC ${LIB_SRC_DIR})
add_test(test_code_stream test_code_stream)
target_link_directories(test_code_stream PUBLIC ${LIB_INCLUDE_DIR})
target_link_libraries(test_code_stream PUBLIC libeverfit)
add_dependencies(test_code_stream libeverfit)