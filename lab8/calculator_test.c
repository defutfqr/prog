#include "unity.h"
#include "calculator.h"

void setUp(void) {

}

void tearDown(void) {

}


void test_add_int(void) {
    TEST_ASSERT_EQUAL_INT(5, add(2, 3)); 
    TEST_ASSERT_EQUAL_INT(-1, add(2, -3)); 
}


void test_subtract_int(void) {
    TEST_ASSERT_EQUAL_INT(-1, subtract(2, 3)); 
    TEST_ASSERT_EQUAL_INT(5, subtract(2, -3)); 
}


void test_multiply_int(void) {
    TEST_ASSERT_EQUAL_INT(6, multiply(2, 3)); 
    TEST_ASSERT_EQUAL_INT(-6, multiply(-2, 3)); 
}


void test_divide_int(void) {
    TEST_ASSERT_EQUAL_INT(2, divide(6, 3));  
    TEST_ASSERT_EQUAL_INT(0, divide(0, 3)); 
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_int);
    RUN_TEST(test_subtract_int);
    RUN_TEST(test_multiply_int);
    RUN_TEST(test_divide_int);
    return UNITY_END();
}
