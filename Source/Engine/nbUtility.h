#ifndef _NB_UTILITY_H_
#define _NB_UTILITY_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#include "nbType.h"

		#define NB_MAX(a,b) (((a) > (b)) ? (a) : (b))
		#define NB_MIN(a,b) (((a) < (b)) ? (a) : (b))

		extern Uint32 nbUtility_GetDate(void);
		extern Int32 nbUtility_NextPowerOf2(Int32 n);
		extern void nbUtility_Sleep(Uint32 nTime);

		extern char nbUtility_RandomChar(void);
		extern void nbUtility_Bin2Hex(Uint8* pIn, size_t nInSize, char* szOut, size_t nOutSize);


	#ifdef __cplusplus
	}
	#endif
#endif