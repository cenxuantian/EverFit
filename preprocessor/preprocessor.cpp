#include "everfit.h"

#include <argparse/argparse.hpp>

#include <cstring>
#include <everfit.h>
#include <iostream>
#include <memory>

#define INLINE_CODE(...) #__VA_ARGS__

int main(int argc, char** argv)
{
    std::vector<std::string> cpp_files;
    argparse::ArgumentParser args("argparse");
    args.add_argument("--cpp")
        .help("The input cpp file(s) to process.")
        .nargs(argparse::nargs_pattern::at_least_one)
        .store_into(cpp_files);
    args.add_argument("-i")
        .help("Inplace edit <file>s, if specified.")
        .nargs(argparse::nargs_pattern::at_least_one)
        .store_into(cpp_files);

    // try to parse the input args
    try {
        args.parse_args(argc, argv);
        printf("args ok");
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << args;
        return 1;
    }

    const char* input = INLINE_CODE(everfit !test { () => { 1 } });
    int intput_len = strlen(input);
    int output_len = intput_len * 2;
    char* output = (char*)malloc(output_len);
    EVERFIT_ASSERT_AND_RETURN(input);
    EVERFIT_ASSERT_AND_RETURN(output);

    printf("Everfit input str content:\n%s\n", input);

    void* pipeline = nullptr;
    everfit_pipeline_options options {};
    EVERFIT_CHECK(everfit_pipeline_create(&pipeline, &options));
    EVERFIT_CHECK(
        everfit_preprocess(pipeline, EVERFIT_LANG_C_CPP, input, &intput_len, output, &output_len));

    printf("Everfit output str content:\n%s\n", output);

    ::free(output);
    output = nullptr;
    EVERFIT_CHECK(everfit_pipeline_destroy(&pipeline));

    return 0;
}