#ifndef _NB_TEST_H_
#define _NB_TEST_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		//#include "nbType.h"
		#include <stdio.h>
		#include <setjmp.h>

		extern jmp_buf nbTest_jumpBuffer;

		extern void nbTest_Startup(void);
		extern void nbTest_Shutdown(void);
		extern void nbTest_AssertBreak(void);

		#define NB_TEST_STARTUP() \
			int main(int argc, const char* argv[]) \
			{ \
				int bError = 0; \
				nbTest_Startup(); \
				printf("\nTest Plox\n");

		#define NB_TEST_SHUTDOWN() \
				if (!bError) nbTest_Shutdown(); \
				printf("\n"); \
				return bError; \
			}

		#define NB_TEST_BEGIN(test_case_name, test_name) \
			void test_##test_case_name##_ ##test_name(void)

		#define NB_TEST_REGISTER(test_case_name, test_name) \
			extern NB_TEST_BEGIN(test_case_name, test_name)

		#define NB_TEST_RUN(test_case_name, test_name) \
		{ \
			printf("%s %s\n", # test_case_name, # test_name); \
			if (!setjmp(nbTest_jumpBuffer)) \
				test_##test_case_name##_ ##test_name(); \
			else \
			{ \
				printf("FAILED\n"); \
				bError = 1; \
			} \
		}

		#define NB_TEST_ASSERT(a, b, test, file, line) do { if (!(a)) { printf("\t%s(%d) : %s(%s)\n\n", file, line, test, b); nbTest_AssertBreak(); } } while (0)
		#define ASSERT_TRUE(a) NB_TEST_ASSERT(a, #a, "ASSERT_TRUE", __FILE__, __LINE__)
		#define ASSERT_FALSE(a) NB_TEST_ASSERT(!(a), #a, "ASSERT_FALSE", __FILE__, __LINE__)
		#define ASSERT_EQ(x,y) NB_TEST_ASSERT((x) == (y), #x", "#y, "ASSERT_EQ", __FILE__, __LINE__)
		#define ASSERT_NE(x,y) NB_TEST_ASSERT((x) != (y), #x", "#y, "ASSERT_NE", __FILE__, __LINE__)
		#define ASSERT_GT(x,y) NB_TEST_ASSERT((x) > (y), #x", "#y, "ASSERT_GT", __FILE__, __LINE__)
		#define ASSERT_LT(x,y) NB_TEST_ASSERT((x) < (y), #x", "#y, "ASSERT_LT", __FILE__, __LINE__)

	#ifdef __cplusplus
	}
	#endif
#endif
