/*
 * Copyright 2022 Adobe
 * All Rights Reserved.
 *
 * NOTICE: Adobe permits you to use, modify, and distribute this file in
 * accordance with the terms of the Adobe license agreement accompanying
 * it.
 */
#pragma once

#include <thread>
#include <vector>
#include <cmath>

namespace foo {

class ThreadPool
{
public:
    template <typename Index, typename Callable>
    static void parallel_for(Index start, Index end, Callable func)
    {
        // Create pool and launch jobs
        std::vector<std::thread> pool;
        pool.reserve(end - start + 1);
        for (Index i = start; i < end; ++i) {
            pool.emplace_back(func, i);
        }

        // Wait for jobs to finish
        for (std::thread& t : pool) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    // Serial version for easy comparison
    template <typename Index, typename Callable>
    static void sequential_for(Index start, Index end, Callable func)
    {
        for (Index i = start; i < end; i++) {
            func(i);
        }
    }
};

} // namespace foo
