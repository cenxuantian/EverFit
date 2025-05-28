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
#include "code_stream.hpp"
#include "common.hpp"
#include <everfit.h>
#include <string>
#include <vector>

namespace everfit {

class Macro {
public:
    enum class ArgType {
        const_expr,
        runtime_expr,
    };
    enum class Narg {
        simgle,
        any,
        at_least_once,
    };
    struct Arg {
        std::string name;
        ArgType type;
        Narg narg;
        bool operator==(Arg const& other) const
        {
            return name == other.name && type == other.type && narg == other.narg;
        }
    };

    std::string name;
    std::vector<Arg> args;
    std::string body;

public:
    Macro()
        : name()
        , args()
        , body()
    {
    }

    Macro(std::string const& in_name, std::vector<Arg> const& in_args, std::string const& in_body)
        : name(in_name)
        , args(in_args)
        , body(in_body)
    {
    }

    Macro([[maybe_unused]] CodeStream const& code_stream)
        : name()
        , args()
        , body()
    {
    }

    bool operator==(Macro const& other) const
    {
        return name == other.name && args == other.args && body == other.body;
    }
};

} // namespace everfit
