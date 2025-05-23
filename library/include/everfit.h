
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

#ifdef __cplusplus
extern "C" {
#endif

/// @brief This function preprocess the `input` string and out put to the
/// `output`
/// @param lang The language type
/// @param input input string
/// @param output output str, this function will reallocate the buffer
/// @return error code
EVERFIT_ERROR_T everfit_preprocess(int lang, const char* input, char* output);

/// @brief This function translate the error_code into readable string
/// @param error_code input error code
/// @param output output string, this function will reallocate the buffer
void everfit_error_msg(int error_code, char* output);

#ifdef __cplusplus
}
#endif

#endif
