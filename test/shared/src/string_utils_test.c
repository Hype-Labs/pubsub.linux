
#include "string_utils_test.h"

void string_utils_test()
{
    string_utils_test_to_lower_case();
}

void string_utils_test_to_lower_case()
{
    int ret;

    char str[] = "TestString";
    ret = string_utils_to_lower_case(str);
    CU_ASSERT(ret == 2);
    CU_ASSERT_STRING_EQUAL(str, "teststring");

    char str2[] = "HypeLabs_FOOD_SERVICE!";
    ret = string_utils_to_lower_case(str2);
    CU_ASSERT(ret == 13);
    CU_ASSERT_STRING_EQUAL(str2, "hypelabs_food_service!");
}
