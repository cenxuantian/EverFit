#pragma once
#include "code_stream.hpp"
namespace everfit {

class Pipeline {
public:
    struct PipelineOptions { };

private:
    PipelineOptions options;
    CodeStream code_stream;

public:
    Pipeline(PipelineOptions const& in_options, const char* in_code_stream)
        : options(in_options)
        , code_stream(in_code_stream)
    {
    }
};

} // namespace everfit
