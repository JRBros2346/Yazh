#pragma once

#include<cstdint>
#include<string>

// Unsigned int types.
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

// Signed int types.
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// Floating point types
using f32 = float;
using f64 = double;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#	define STATIC_ASSERT _Static_assert
#else
#	define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#	define YPLATFORM_WINDOWS true
#	ifndef _WIN64
#		error "64-bit is required on Windows!"
#	endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#	define YPLATFORM_LINUX true
#	if defined(__ANDROID__)
#		define YPLATFORM_ANDROID true
#	endif

// Catch anything not caught by the above.

#elif defined(_POSIX_VERSION)
// Posix
#	define YPLATFORM_POSIX true
#elif __APPLE__
// Apple platforms
#	define YPLATFORM_APPLE true
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#		define YPLATFORM_IOS true
#		define YPLATFORM_IOS_SIMULATOR true
#	elif TARGET_OS_IPHONE
#		define YPLATFORM_IOS true
// iOS device
#	elif TARGET_OS_MAC
// Other kinds of Mac OS
#	else
#		error "Unknown Apple platform"
#	endif
#elif defined(__unix__)
#	define YPLATFORM_UNIX true
#else
#	error "Unknown platform!"
#endif

#ifdef YEXPORT
// Exports
#	ifdef KPLATFORM_WINDOWS
#		define YAPI __declspec(dllexport)
#	else
#		define YAPI __attribute__((visibility("default")))
#	endif
#else
// Imports
#	ifdef KPLATFORM_WINDOWS
#		define YAPI __declspec(dllimport)
#	else
#		define YAPI
#	endif
#endif

