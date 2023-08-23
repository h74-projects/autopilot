#include "mu_test.h"
#include <iostream>
#include "var.hpp"


BEGIN_TEST(var_int_test)
    Var var(42);
    ASSERT_EQUAL(static_cast<int>(var), 42);
END_TEST

BEGIN_TEST(var_double_test)
    Var var(3.14);
    ASSERT_EQUAL(static_cast<double>(var), 3.14);
END_TEST

BEGIN_TEST(var_bool_test)
    Var var(true);
    ASSERT_EQUAL(static_cast<bool>(var), true);
END_TEST

BEGIN_TEST(var_float_test)
    Var var(1.234f);
    ASSERT_EQUAL(static_cast<float>(var), 1.234f);
END_TEST

BEGIN_TEST(double_test)
    Var var = 3.14;
    double ko = var;
    ASSERT_EQUAL(ko, 3.14);
END_TEST

BEGIN_TEST(bool_test)
    Var var = true;
   // bool go = var;
    Var j = var;
    Var k = 2;
    //bool op = true; 
    ASSERT_THAT(var);
    
    ASSERT_EQUAL(j.type_id(), var.type_id());
    ASSERT_NOT_EQUAL(j.type_id(), k.type_id());

END_TEST

BEGIN_TEST(arithmetic_operators_test)
    Var var1 = 5;
    Var var2 = 3;
    Var c = 5.5;

    Var sum = static_cast<int>(var1) + static_cast<int>(var2);
    ASSERT_EQUAL(static_cast<int>(sum), 8);

    Var difference = static_cast<int>(var1) - static_cast<int>(var2);
    ASSERT_EQUAL(static_cast<int>(difference), 2);

    Var product = static_cast<int>(var1) * static_cast<int>(var2);
    ASSERT_EQUAL(static_cast<int>(product), 15);

    Var quotient = static_cast<int>(var1) / static_cast<int>(var2);
    ASSERT_EQUAL(static_cast<int>(quotient), 1);
    int var3 = var1 + var2;
    std::cout<< var3 << '\n';

END_TEST

BEGIN_TEST(comparison_operators_test)
    Var var1 = 5;
    Var var2 = 3;
    Var var3 = 5.0;
    Var v = 5.4;
    Var var4 = true;

    ASSERT_THAT(var1 != v);
    ASSERT_THAT(var1 != var2);

    ASSERT_THAT(var1 != var2);

    ASSERT_THAT(var1 > var2);
    ASSERT_THAT(var1 >= var2);
    ASSERT_THAT(var1 > var2);
    ASSERT_THAT(var1 >= var2);

    ASSERT_THAT(var4 == true);
    ASSERT_THAT(var4 != false);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(var_int_test)
    TEST(var_double_test)
    TEST(var_bool_test)
    TEST(var_float_test)
    TEST(double_test)
    TEST(bool_test)
    TEST(arithmetic_operators_test)
    TEST(comparison_operators_test)
END_SUITE