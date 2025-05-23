#include <cstring>
#include <everfit.h>
#include <iostream>
#include <memory>

#define INLINE_CODE(...) #__VA_ARGS__

int main()
{
    const char* input = INLINE_CODE(everfit !test { () => { 1 } });
    char* output = nullptr;

    printf("Everfit input str content:\n%s\n", input);

    if (auto ret = everfit_preprocess(EVERFIT_LANG_C_CPP, input, output) != EVERFIT_ERROR_SUCCEED) {
        everfit_error_msg(ret, output);
        printf("Everfit ERROR: %s\n", output);
    } else {
        printf("Everfit output str content:\n%s\n", output);
    }

    if (output) {
        ::free(output);
        output = nullptr;
    }

    return 0;
}