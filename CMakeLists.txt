#
# Copyright 2022 Adobe
# All Rights Reserved.
#
# NOTICE: Adobe permits you to use, modify, and distribute this file in
# accordance with the terms of the Adobe license agreement accompanying
# it.
#
cmake_minimum_required(VERSION 3.20)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")

# Replace all instances of "foo" with your project name
project(Foo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(PREPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(sanitizers)

include(onetbb)
file(GLOB_RECURSE INC_FILES "src/*.h")
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_library(mylib INTERFACE ${INC_FILES} ${SRC_FILES})
add_library(mylib::mylib ALIAS mylib)
target_include_directories(mylib INTERFACE src)
target_link_libraries(mylib INTERFACE TBB::tbb)

include(CTest)
add_subdirectory(tests)
