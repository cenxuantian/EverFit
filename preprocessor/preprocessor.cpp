#include "everfit.h"

#include <argparse/argparse.hpp>

#include <cstring>
#include <everfit.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#define INLINE_CODE(...) #__VA_ARGS__

int main(int argc, char** argv)
{

    argparse::ArgumentParser args("argparse");

    std::vector<std::string> cpp_files;
    args.add_argument("--cpp")
        .help("The input cpp file(s) to process.")
        .nargs(argparse::nargs_pattern::at_least_one)
        .store_into(cpp_files);
    args.add_argument("-i").help("Inplace edit <file>s, if specified.").flag();
    args.add_argument("-o", "--output").help("output_file path").nargs(1).default_value("NULL");
    ;

    // try to parse the input args
    try {
        args.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << args;
        return 1;
    }

    [[maybe_unused]] const bool inplace_edit = args.get<bool>("-i");
    [[maybe_unused]] const std::string output_path = args.get<std::string>("-o");

    void* pipeline = nullptr;
    everfit_pipeline_options options {};
    EVERFIT_CHECK(everfit_pipeline_create(&pipeline, &options));

    for (const auto& i : cpp_files) {
        std::ifstream in_file { i };
        EVERFIT_ASSERT_AND_RETURN(in_file.is_open());
        std::string content((std::istreambuf_iterator<char>(in_file)),
                            std::istreambuf_iterator<char>());

        const char* input = content.c_str();
        int intput_len = strlen(input);
        int output_len = intput_len * 2;
        char* output = (char*)malloc(output_len);
        EVERFIT_ASSERT_AND_RETURN(input);
        EVERFIT_ASSERT_AND_RETURN(output);

        everfit_pipeline_process_options process_options {};
        EVERFIT_CHECK(everfit_preprocess(
            pipeline, &process_options, input, &intput_len, output, &output_len));

        printf("%s", input);
        // printf("Everfit output str content:\n%s\n", output);

        ::free(output);
        output = nullptr;
    }

    EVERFIT_CHECK(everfit_pipeline_destroy(&pipeline));

    return 0;
}