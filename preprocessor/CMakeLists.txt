# Fetch argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

set(PREPROCESSOR_EXE_NAME everfit)

# this is the preprocessor target
add_executable(${PREPROCESSOR_EXE_NAME} preprocessor.cpp)
target_include_directories(${PREPROCESSOR_EXE_NAME} PRIVATE 
    ${LIB_INCLUDE_DIR}
    thrid_party/include
)
target_include_directories(${PREPROCESSOR_EXE_NAME} PRIVATE )
target_link_directories(${PREPROCESSOR_EXE_NAME} PRIVATE ${LIB_INCLUDE_DIR})
target_link_libraries(${PREPROCESSOR_EXE_NAME} PRIVATE libeverfit argparse)
add_dependencies(${PREPROCESSOR_EXE_NAME} libeverfit)

