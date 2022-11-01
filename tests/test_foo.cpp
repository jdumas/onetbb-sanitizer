/*
 * Copyright 2022 Adobe
 * All Rights Reserved.
 *
 * NOTICE: Adobe permits you to use, modify, and distribute this file in
 * accordance with the terms of the Adobe license agreement accompanying
 * it.
 */
#include "copy_on_write_ptr.h"
#include "thread_pool.h"

#include <tbb/parallel_for.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("parallel_cow_tbb")
{
    int N = 100;
    using Array = std::vector<double>;

    std::vector<foo::copy_on_write_ptr<Array>> attrs;
    for (int i = 0; i < N; ++i) {
        auto ptr = std::make_shared<Array>(10);
        attrs.emplace_back(std::move(ptr));
        attrs.push_back(attrs.back());
    }
    tbb::parallel_for(0, N, [&](int i) { (*attrs[i].write())[0] = 1; });
}

TEST_CASE("parallel_cow_std")
{
    int N = 100;
    using Array = std::vector<double>;

    std::vector<foo::copy_on_write_ptr<Array>> attrs;
    for (int i = 0; i < N; ++i) {
        auto ptr = std::make_shared<Array>(10);
        attrs.emplace_back(std::move(ptr));
        attrs.push_back(attrs.back());
    }
    foo::ThreadPool::parallel_for(0, N, [&](int i) { (*attrs[i].write())[0] = 1; });
}
