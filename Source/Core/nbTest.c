#define DUCK_SECRET
#include "nbTest.h"
//#include "nbMemoryManager.h"
//#include "nbHttpManager.h"
//#include "nbFileManager.h"
//#include "nbPlatform.h"
//#include "nbApplication.h"

#include <stdlib.h>
#include <time.h>

	jmp_buf nbTest_jumpBuffer;

	void nbTest_Startup(void)
	{
		srand((unsigned int)time(NULL));

//		nbApplication_Startup(NULL, NULL);

//		nbHttpManager_Startup();
//		nbFileManager_Startup();
	}

	void nbTest_Shutdown(void)
	{
		/*nbHttpManager_Shutdown();
		nbFileManager_Shutdown();
		nbMemoryManager_Shutdown();*/

		//nbApplication_Shutdown();


	}

	void nbTest_AssertBreak(void)
	{
		#ifdef NB_WINDOWS
			__debugbreak();
		#endif
		longjmp(nbTest_jumpBuffer, 1);
	}
