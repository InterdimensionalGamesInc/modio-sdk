#
#  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
#
#  This file is part of the mod.io SDK.
#
#  Distributed under the MIT License. (See accompanying file LICENSE or
#   view online at <https://github.com/modio/modio-sdk/blob/main/LICENSE>)
#

if (NOT TARGET platform)
	add_library(platform INTERFACE)
endif()

target_compile_features(platform INTERFACE cxx_std_14)
target_compile_definitions(platform INTERFACE -DFU2_WITH_NO_EMPTY_PROPAGATION)
target_include_directories(platform INTERFACE ${CMAKE_CURRENT_LIST_DIR})

find_library(FOUNDATION Foundation)
find_library(CFNETWORK CFNetwork)

target_link_libraries(platform INTERFACE httpparser pthread ghc_filesystem ${FOUNDATION} ${CFNETWORK})
