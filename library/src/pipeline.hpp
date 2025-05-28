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

#pragma once

#include "../include/everfit.h"
#include "code_stream.hpp"
#include "processor_factory.hpp"

namespace everfit {

class Pipeline {
private:
    everfit_pipeline_options options;

public:
    Pipeline(everfit_pipeline_options const& in_options)
        : options(in_options)
    {
    }

    ~Pipeline() { }

    EVERFIT_ERROR_T
    process([[maybe_unused]] everfit_pipeline_process_options const& process_options,
            [[maybe_unused]] CodeStream const& in_stream,
            [[maybe_unused]] WriteStream& out_stream)
    {
        ProcessorFactory fac;
        auto [ret, processor] = fac.create_processor(process_options);
        EVERFIT_RETURN_ON_ERROR(ret); // check if return an error
        EVERFIT_ASSERT_AND_RETURN(processor.get()); // check if processor is a nullptr
        EVERFIT_RETURN_ON_ERROR(processor->process(in_stream, out_stream));
        return EVERFIT_ERROR_SUCCEED;
    }
};

} // namespace everfit
