/*
 * Copyright 2022 Adobe
 * All Rights Reserved.
 *
 * NOTICE: Adobe permits you to use, modify, and distribute this file in
 * accordance with the terms of the Adobe license agreement accompanying
 * it.
 */
#include <catch2/catch_test_macros.hpp>

#include <tbb/parallel_for.h>

TEST_CASE("test foo")
{
    std::atomic_int x = 0;
    tbb::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}
