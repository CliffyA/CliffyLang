#ifndef _NB_ASSERT_H_
#define _NB_ASSERT_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#if defined(_MSC_VER)
			#include <Windows.h>
			#include <stdio.h>
			#define nbAssert(x) { if (!(x)) { printf("Assert: %s (%d) : %s\n", __FILE__, __LINE__, #x); DebugBreak(); } }
		#elif defined(CMAKE_PLATFORM_ANDROID)
			#include <assert.h>
			#include <stdio.h>
			#include <android/log.h>
		//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "test");
			#define nbAssert(x) { if (!(x)) { __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Assert: %s (%d) : %s\n", __FILE__, __LINE__, #x); assert(0); } }
		#else
			#include <assert.h>
			#include <stdio.h>
			#define nbAssert(x) { if (!(x)) { printf("Assert: %s (%d) : %s\n", __FILE__, __LINE__, #x); assert(0); } }
		#endif

	#ifdef __cplusplus
	}
	#endif
#endif