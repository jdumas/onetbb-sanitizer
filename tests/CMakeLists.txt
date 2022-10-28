#
# Copyright 2022 Adobe
# All Rights Reserved.
#
# NOTICE: Adobe permits you to use, modify, and distribute this file in
# accordance with the terms of the Adobe license agreement accompanying
# it.
#
include(catch2)
FetchContent_GetProperties(catch2)
include("${catch2_SOURCE_DIR}/extras/Catch.cmake")

file(GLOB TEST_SOURCES "*.h" "*.cpp")
add_executable(foo_tests ${TEST_SOURCES})

include(onetbb)
target_link_libraries(foo_tests PUBLIC
    Catch2::Catch2WithMain
    TBB::tbb
)

catch_discover_tests(foo_tests)
