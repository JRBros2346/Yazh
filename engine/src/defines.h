#pragma once

#include<cstdint>

// Unsigned int types.
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed int types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef bool b;

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
#	define YPLATFORM_WINDOWS 1
#	ifndef _WIN64
#		error "64-bit is required on Windows!"
#	endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#	define YPLATFORM_LINUX 1
#	if defined(__ANDROID__)
#		define YPLATFORM_ANDROID 1
#	endif

// Catch anything not caught by the above.

#elif defined(_POSIX_VERSION)
// Posix
#	define YPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#	define YPLATFORM_APPLE 1
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#		define YPLATFORM_IOS 1
#		define YPLATFORM_IOS_SIMULATOR 1
#	elif TARGET_OS_IPHONE
#		define YPLATFORM_IOS 1
// iOS device
#	elif TARGET_OS_MAC
// Other kinds of Mac OS
#	else
#		error "Unknown Apple platform"
#	endif
#elif defined(__unix__)
#	define YPLATFORM_UNIX 1
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

