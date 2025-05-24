
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
/// @param output output str, if no enough space, will return EVERFIT_BUF_TOO_SMALL
/// @return error code
EVERFIT_ERROR_T everfit_preprocess(void* pipeline,
                                   int lang,
                                   const char* input,
                                   int* input_size,
                                   char* output,
                                   int* output_size);

#ifdef __cplusplus
}
#endif

#endif
