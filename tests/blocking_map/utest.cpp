#include "mu_test.h"
#include "blocking_map.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstddef> // size_t

BEGIN_TEST(basic_test)
    concurrency::BlockingMap<std::string,int> map;
    map["first"] = 0;
    std::vector<std::thread> threads;
    int big_number = 10'000;
    threads.reserve(big_number);
    auto thread_inc = [&map] {
        ++map.at("first");
    }; 
    for (int i = 0; i < big_number; ++i) {
        threads.emplace_back(std::thread{thread_inc});
    }
    for (int i = 0; i < big_number; ++i) {
        threads.at(i).join();
    }
    threads.clear();    
    ASSERT_EQUAL(map.at("first"),big_number);

    map["second"] = 0;
    auto thread_add = [&map](int const& a_times) {
        for (int i = 0; i < a_times; ++i) {
            ++map.at("second");
        }
    };

    for (int i = 0; i < big_number; ++i) {
        threads.emplace_back(std::thread(thread_add,big_number));
    }
    for (int i = 0; i < big_number; ++i) {
        threads.at(i).join();
    }
    ASSERT_EQUAL(map.at("second"),big_number*big_number);    

END_TEST

BEGIN_SUITE("not all those who wander are lost")
    TEST(basic_test)

END_SUITE