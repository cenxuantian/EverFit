#include "everfit.h"

#include <cstring>
#include <everfit.h>
#include <iostream>
#include <memory>

#define INLINE_CODE(...) #__VA_ARGS__

int main()
{
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