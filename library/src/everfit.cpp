/**
 * MIT License
 *
 * Copyright (c) 2025 Cenxuan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../include/everfit.h"
#include "code_stream.hpp"
#include "pipeline.hpp"

EVERFIT_ERROR_T everfit_pipeline_create(void** pipeline, const everfit_pipeline_options* options)
{
    // auto& pipe = reinterpret_cast<everfit::Pipeline**>(pipeline);
    auto pipe = new everfit::Pipeline(*options);
    EVERFIT_ASSERT_AND_RETURN(pipe);
    *reinterpret_cast<everfit::Pipeline**>(pipeline) = pipe;
    return EVERFIT_ERROR_SUCCEED;
}

EVERFIT_ERROR_T everfit_pipeline_destroy(void** pipeline)
{
    auto p_pipe = *reinterpret_cast<everfit::Pipeline**>(pipeline);
    if (p_pipe) {
        delete p_pipe;
        *pipeline = nullptr;
    }
    return EVERFIT_ERROR_SUCCEED;
};

EVERFIT_ERROR_T everfit_preprocess([[maybe_unused]] void* pipeline,
                                   [[maybe_unused]] everfit_pipeline_process_options* options,
                                   [[maybe_unused]] const char* input,
                                   [[maybe_unused]] int* input_size,
                                   [[maybe_unused]] char* output,
                                   [[maybe_unused]] int* output_size)
{
    return EVERFIT_ERROR_SUCCEED;
}

EVERFIT_ERROR_T everfit_error_msg([[maybe_unused]] int error_code, char* output, int* output_size)
{
    if (!output || !*output || !output_size || !*output_size) {
        return EVERFIT_ERROR_BUF_TOO_SMALL;
    }
    auto copy_text = [&](const char* text) {
        auto text_len = strlen(text);
        if ((*output_size) <= static_cast<int>(text_len)) {
            return EVERFIT_ERROR_BUF_TOO_SMALL;
        }
        if (!memcpy(output, text, text_len)) {
            return EVERFIT_ERROR_SYSTEM_ERR;
        }
        output[text_len] = 0;
        return EVERFIT_ERROR_SUCCEED;
    };
    return copy_text("[needs to be implemented]");
}
