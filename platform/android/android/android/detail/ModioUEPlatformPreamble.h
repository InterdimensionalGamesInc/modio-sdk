/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io SDK.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-sdk/blob/main/LICENSE>)
 *
 */

 // clang-format off

#include "Clang/ClangPlatformCompilerPreSetup.h"
#include "HAL/PlatformMisc.h"
#include "Misc/AssertionMacros.h"
#include "Android/AndroidPlatform.h"
#include "Android/AndroidPlatformCompilerPreSetup.h"
#include "Android/AndroidPlatformCompilerSetup.h"

// NOTE!! I tried to add "-Wshadow" as a "target_compile_options" in many CMake files:
// platform/macos/macos, asio.cmake, howeever it dit not like it.
#pragma GCC diagnostic push

// This is required by file "resolver_base.hpp" in line 69 which complains about this:
// Declaration shadows a variable in namespace 'asio::ip'
// https://github.com/chriskohlhoff/asio/issues/721
#pragma GCC diagnostic ignored "-Wshadow"

// clang-format on
