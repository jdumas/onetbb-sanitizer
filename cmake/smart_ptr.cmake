#
# Copyright 2022 Adobe. All rights reserved.
# This file is licensed to you under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License. You may obtain a copy
# of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
# OF ANY KIND, either express or implied. See the License for the specific language
# governing permissions and limitations under the License.
#
if(TARGET smart_ptr::smart_ptr)
    return()
endif()

message(STATUS "Third-party (external): creating target 'smart_ptr::smart_ptr'")

include(FetchContent)
FetchContent_Declare(
    smart_ptr
    GIT_REPOSITORY https://github.com/X-czh/smart_ptr.git
    GIT_TAG f1e4c2a0c76acbde1bafa3862e970b6a1ab96213
)

FetchContent_MakeAvailable(smart_ptr)

add_library(smart_ptr INTERFACE)
add_library(smart_ptr::smart_ptr ALIAS smart_ptr)

include(GNUInstallDirs)
target_include_directories(smart_ptr INTERFACE
    "$<BUILD_INTERFACE:${smart_ptr_SOURCE_DIR}>/include"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

