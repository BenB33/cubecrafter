#ifndef CUBED_CRAFTER_ASSERTS_H
#define CUBED_CRAFTER_ASSERTS_H


#ifdef CC_PLATFORM_WINDOWS
#	define CC_DEBUG_BREAK() __debugbreak()
#endif // CC_PLATFORM_WINDOWS


#if defined(CC_PLATFORM_LINUX) || defined(CC_PLATFORM_MACOS)
#	include <signal.h>
#	define CC_DEBUG_BREAK() raise(SIGTRAP)
#endif // CC_PLATFORM_LINUX || CC_PLATFORM_MACOS


#ifdef CC_BUILD_DEBUG
#	include <iostream>
#	define CC_ASSERT(x, ...) { if(!x) { std::cerr << __VA_ARGS__ << "\n"; CC_DEBUG_BREAK(); } }
#else
#	define CC_ASSERT(x, ...)
#endif // CC_BUILD_DEBUG

#endif // CUBED_CRAFTER_ASSERTS_H