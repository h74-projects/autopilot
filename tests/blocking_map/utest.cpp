#include "mu_test.h"
#include "blocking_map.hpp"

#include <string>
#include <vector>
#include <thread>
#include <cstddef> // size_t

BEGIN_TEST(basic_test)
    concurrency::BlockingMap<std::string,int> map;
    map["first"] = 0;
    std::vector<std::thread> threads;
    int big_number = 1'000'000;
    threads.reserve(big_number);
    auto thread = [&map] {
        ++map.at("first");
    };
    for (int i = 0; i < big_number; ++i) {
        threads.push_back(std::thread{thread});
    }
    for (auto& it : threads) {
        it.join();
    }
    ASSERT_EQUAL(map.at("first"),big_number);

END_TEST

BEGIN_SUITE("not all those who wander are lost")
    TEST(basic_test)

END_SUITE