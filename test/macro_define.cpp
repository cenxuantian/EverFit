#include "test_common.hpp"
#include <assert.h>
#include <macro.hpp>

void run_test(std::string input, everfit::Macro const& expected)
{
    everfit::CodeStream code(input.data(), input.size());
    assert(everfit::Macro(code) == expected);
}

int main()
{

    run_test("", {});
    run_test("everfit_macro! return_val (){\n"
             "1\n"
             "}\n",
             { "return_val", {}, "1" });

    return 0;
}