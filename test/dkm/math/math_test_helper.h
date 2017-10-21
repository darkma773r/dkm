#ifndef _DKM_MATH_TEST_HELPER_H_
#define _DKM_MATH_TEST_HELPER_H_

#define ASSERT_ARRAY_EQ(expected, actual, size) \
    for (int i=0; i<size; ++i){\
        ASSERT_EQ(expected[i], actual[i]);\
    }

#define ASSERT_ARRAY_NEAR(expected, actual, size, delta)\
    for (int i=0; i<size; ++i){\
        ASSERT_NEAR(expected[i], actual[i], delta);\
    }

#endif
