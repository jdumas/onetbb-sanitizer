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
        // Estimate number of threads in the pool
        const static unsigned nb_threads_hint = std::thread::hardware_concurrency();
        const static unsigned nb_threads = (nb_threads_hint == 0u ? 8u : nb_threads_hint);

        // Size of a slice for the range functions
        Index n = end - start + 1;
        Index slice = (Index)std::round(n / static_cast<double>(nb_threads));
        slice = std::max(slice, Index(1));

        // [Helper] Inner loop
        auto launchRange = [&func](int k1, int k2) {
            for (Index k = k1; k < k2; k++) {
                func(k);
            }
        };

        // Create pool and launch jobs
        std::vector<std::thread> pool;
        pool.reserve(nb_threads);
        Index i1 = start;
        Index i2 = std::min(start + slice, end);
        for (unsigned i = 0; i + 1 < nb_threads && i1 < end; ++i) {
            pool.emplace_back(launchRange, i1, i2);
            i1 = i2;
            i2 = std::min(i2 + slice, end);
        }
        if (i1 < end) {
            pool.emplace_back(launchRange, i1, end);
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
