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

#ifndef __EVERFIT_ERROR_H__
#define __EVERFIT_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EVERFIT_ERROR_MESSAGE_LEN 50

// errors
typedef int EVERFIT_ERROR_T;
#define EVERFIT_ERROR_SUCCEED 0
#define EVERFIT_ERROR_UNKNOWN 1
#define EVERFIT_ERROR_ASSERT 2
#define EVERFIT_BUF_TOO_SMALL 3
#define EVERFIT_SYSTEM_ERROR 4

/// @brief This function translate the error_code into readable string
/// @param error_code input error code
/// @param output output str, if no enough space, will return EVERFIT_BUF_TOO_SMALL
EVERFIT_ERROR_T everfit_error_msg(int error_code, char* output, int* output_size);

#define EVERFIT_ASSERT_AND_RETURN(...)                                                             \
    if (!static_cast<bool>(__VA_ARGS__)) {                                                         \
        printf("Everfit Assertion failed on [" __FILE__ ":%d]\n", __LINE__);                       \
        return EVERFIT_ERROR_ASSERT;                                                               \
    }

#define EVERFIT_CHECK(...)                                                                         \
    if (EVERFIT_ERROR_T error_code = __VA_ARGS__ != EVERFIT_ERROR_SUCCEED) {                       \
        char error_msg[EVERFIT_ERROR_MESSAGE_LEN];                                                 \
        int len = EVERFIT_ERROR_MESSAGE_LEN;                                                       \
        everfit_error_msg(error_code, error_msg, &len);                                            \
        printf("Everfit Error: on [" __FILE__ ":%d]\n", __LINE__);                                 \
    }

#ifdef __cplusplus
}
#endif

#endif