#include "thread_pool.h"

#include <tbb/parallel_for.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("parallel_cow_tbb", "[tbb]")
{
    std::atomic_int x = 0;
    tbb::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_tbb2", "[tbb]")
{
    std::atomic_int x = 0;
    tbb::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_tbb3", "[tbb]")
{
    std::atomic_int x = 0;
    tbb::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_tbb4", "[tbb]")
{
    std::atomic_int x = 0;
    tbb::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_std", "[std]")
{
    std::atomic_int x = 0;
    foo::ThreadPool::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_std2", "[std]")
{
    std::atomic_int x = 0;
    foo::ThreadPool::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_std3", "[std]")
{
    std::atomic_int x = 0;
    foo::ThreadPool::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}

TEST_CASE("parallel_cow_std4", "[std]")
{
    std::atomic_int x = 0;
    foo::ThreadPool::parallel_for(0, 100, [&](int i) { x += i; });
    REQUIRE(x == 4950);
}
