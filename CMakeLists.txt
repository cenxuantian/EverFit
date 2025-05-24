cmake_minimum_required(VERSION 3.10.0)
project(everfit VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(LIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/library/include)
set(LIB_SRC_DIR ${PROJECT_SOURCE_DIR}/library/src)


option(BUILD_PREPROCESSOR "Build preprocessor" ON)
option(BUILD_TESTS "Build unit tests" ON)


if(MSVC)
set(LIB_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}libeverfit.lib)
else()
set(LIB_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libeverfit.lib)
endif()

add_subdirectory (library)

if(${BUILD_PREPROCESSOR})
    add_subdirectory (preprocessor)
endif()
if(${BUILD_TESTS})
    # if build tests, preprocessor is needed
    if (NOT ${BUILD_PREPROCESSOR})
        add_subdirectory (preprocessor)
    endif()
    add_subdirectory (test)
endif()



