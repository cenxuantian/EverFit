#include "../include/everfit.h"

int everfit_preprocess([[maybe_unused]] int lang, [[maybe_unused]] const char* input,
                       [[maybe_unused]] char* output)
{
    return EVERFIT_ERROR_SUCCEED;
}

void everfit_error_msg([[maybe_unused]] int error_code, [[maybe_unused]] char* output) { }
