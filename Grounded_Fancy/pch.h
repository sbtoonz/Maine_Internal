// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG(format, ...) std::printf("[%s:%s:%i]" format "\n", __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
// add headers that you want to pre-compile here
#include "framework.h"
#include <detours.h>
#include <detver.h>
#include <syelog.h>
#include <SDK.h>
using namespace CG;
#include "../imgui/imgui.h"
#include "Utils/json.hpp"
#include "Utils/HookManager.h"
#endif //PCH_H
