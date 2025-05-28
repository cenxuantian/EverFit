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

#include "processor.hpp"
#include "processor_cpp.hpp"

namespace everfit {
class ProcessorFactory {
public:
    std::tuple<EVERFIT_ERROR_T, std::unique_ptr<Processor>>
    create_processor([[maybe_unused]] everfit_pipeline_process_options const& process_options)
    {
        switch (process_options.lang) {
        case EVERFIT_LANG_C_CPP:
            return { EVERFIT_ERROR_SUCCEED, std::make_unique<CppProcessor>() };

        // Note: here when explicitly input EVERFIT_LANG_UNKNOWN as language, we return
        // DefaultProcessor
        case EVERFIT_LANG_UNKNOWN:
            return { EVERFIT_ERROR_SUCCEED, std::make_unique<DefaultProcessor>() };
        default:
            return { EVERFIT_ERROR_LANG_NOT_SUPPORTED, std::make_unique<DefaultProcessor>() };
        }
    }
};
} // namespace everfit
