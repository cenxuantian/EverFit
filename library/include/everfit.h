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

/**
 * Simple example of everfit
 *
 * Grammar:
 *      define:
 *      [#] macro_name ( $arg1: Type1 | Type2, $arg2 : Type1 *) { body... }
 *
 *      call
 *      [>] marcro_name (arg1, arg2)
 *
 *
 * Macro replace define
 *      [#] macro_value { 10 }
 *  to use this
 *      [>] macro_value
 *
 * Macro function stype replace
 *      [#] if ($cond: efexpr, $expr: rtexpr) {
 *          // check if cond is EFExpr
 *          // if true, then replace
 *      }
 *
 *      [#] get($arglist, $)
 *
 *      [#] macro_add ($x:ConstVal | RuntimeVal, $y:ConstVal | RuntimeVal) { ($x
 * + $y) } to use this
 *      [>] macro_add (1,2)  // this will be replaced by (1+2)
 *      [>] macro_add ([> macro_value] , 1)
 *
 *      // for c++
 *      [#] macro_sum ($x*) {
 *          [&](){
 *              [>]if ([>]len($x) > 0, {})
 *          }
 *       }
 *
 */

#ifndef __EVERFIT_EVERFIT_H__
#define __EVERFIT_EVERFIT_H__

#include "defines.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

EVERFIT_ERROR_T everfit_pipeline_create(void** pipeline, const everfit_pipeline_options* options);
EVERFIT_ERROR_T everfit_pipeline_destroy(void** pipeline);

/// @brief This function preprocess the `input` string and out put to the
/// `output`
/// @param lang The language type
/// @param input input string
/// @param output output str, if no enough space, will return EVERFIT_ERROR_BUF_TOO_SMALL
/// @return error code
EVERFIT_ERROR_T everfit_preprocess(void* pipeline,
                                   everfit_pipeline_process_options* options,
                                   const char* input,
                                   int* input_size,
                                   char* output,
                                   int* output_size);

#ifdef __cplusplus
}
#endif

#endif
