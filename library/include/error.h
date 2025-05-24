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