#
# Copyright 2022 Adobe
# All Rights Reserved.
#
# NOTICE: Adobe permits you to use, modify, and distribute this file in
# accordance with the terms of the Adobe license agreement accompanying
# it.
#
cmake_minimum_required(VERSION 3.20)

# Replace all instances of "foo" with your project name
project(Foo)

list(PREPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(sanitizers)

include(CTest)
add_subdirectory(tests)
