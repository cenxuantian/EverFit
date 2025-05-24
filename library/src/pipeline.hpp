#pragma once

#include "../include/everfit.h"
#include "code_stream.hpp"

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

    EVERFIT_ERROR_T process([[maybe_unused]] everfit_pipeline_process_options const& process_option,
                            [[maybe_unused]] CodeStream const& in_stream,
                            [[maybe_unused]] WriteStream const& out_stream)
    {

        return EVERFIT_ERROR_SUCCEED;
    }
};

} // namespace everfit
