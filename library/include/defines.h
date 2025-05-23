#ifndef __EVERFIT_DEFINES_H__
#define __EVERFIT_DEFINES_H__

#define EVERFIT_LANG_C_CPP 1

// errors
typedef int EVERFIT_ERROR_T;
#define EVERFIT_ERROR_SUCCEED 0
#define EVERFIT_ERROR_UNKNOWN 1
#define EVERFIT_ERROR_ASSERT 2

#define EVERFIT_ASSERT_AND_RETURN(...)                                                             \
    if (!static_cast<bool>(__VA_ARGS__)) {                                                         \
        printf("Everfit Assertion failed on [" __FILE__ ":%d]\n", __LINE__);                       \
        return EVERFIT_ERROR_ASSERT;                                                               \
    }

#endif