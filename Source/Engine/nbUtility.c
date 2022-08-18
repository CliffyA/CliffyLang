#include "nbUtility.h"
#include "nbPlatform.h"
#include "nbAssert.h"

#include <time.h>
#ifdef NB_WINDOWS
	#include <windows.h> // for Sleep
#else
	#include <unistd.h> // for usleep
#endif

#ifdef NB_EMSCRIPTEN
	#include <emscripten.h>
#endif

#include <stdlib.h>
#include <string.h>

	extern Uint32 nbUtility_GetDate(void)
	{
		time_t nTime;
		time(&nTime);

		return (Uint32)nTime;
	}

	Int32 nbUtility_NextPowerOf2(Int32 n)
	{
		if ((n & (n - 1)) != 0)
		{
			n |= (n >> 16);
			n |= (n >> 8);
			n |= (n >> 4);
			n |= (n >> 2);
			n |= (n >> 1);
			++n;
		}
		return n;
	}

	void nbUtility_Sleep(Uint32 nTime)
	{
		#ifdef NB_WINDOWS
			Sleep(nTime);
		#else
			#ifdef NB_EMSCRIPTEN
				emscripten_sleep(nTime);
			#else
				usleep(nTime*1000);
			#endif
		#endif
	}

	char nbUtility_RandomChar(void)
	{
		const char* CHAR_ARRAY = "0123456789abcdefghijklmnopqrstuvwxyz";
		int nIndex = rand() % strlen(CHAR_ARRAY);
		return CHAR_ARRAY[nIndex];
	}


	void nbUtility_Bin2Hex(Uint8* pIn, size_t nInSize, char* szOut, size_t nOutSize)
	{
		static const char cHexCharArray[16] = "0123456789abcdef";
		size_t i;

		nbAssert(nOutSize >= nInSize * 2 + 1);

		for (i = 0; i < nInSize; i++)
		{
			szOut[i*2] = cHexCharArray[pIn[i] / 16];
			szOut[i*2+1] = cHexCharArray[pIn[i] % 16];
		}
		szOut[nInSize*2] = '\0';
	}
