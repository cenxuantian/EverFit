# tests

find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

function(add_test_from_src test_name src)
    add_executable(${test_name} ${src})
    target_include_directories(${test_name} PUBLIC ${LIB_SRC_DIR})
    target_link_directories(${test_name} PUBLIC ${LIB_INCLUDE_DIR})
    target_link_libraries(${test_name} PUBLIC libeverfit)
    add_dependencies(${test_name} libeverfit)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

function(add_parse_test test_name)
    add_test(NAME ${test_name} COMMAND ${BASH_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/test/test_compare.sh 
        --src-dir ${CMAKE_SOURCE_DIR} 
        --name ${test_name}
        )
endfunction()


add_test_from_src(test_code_stream code_stream.cpp)
add_parse_test(test_simple_replace)
