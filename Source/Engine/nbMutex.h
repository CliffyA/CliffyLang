#ifndef _NB_MUTEX_H_
#define _NB_MUTEX_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#include "nbPlatform.h"

		#ifndef NB_EMSCRIPTEN
		
			typedef struct nbMutex nbMutex;
			
			extern nbMutex* nbMutex_Create(void);
			extern void nbMutex_Destroy(nbMutex* pMutex);

			extern void nbMutex_Lock(nbMutex* pMutex);
			extern void nbMutex_Unlock(nbMutex* pMutex);

			#ifdef NB_MUTEX_SECRET
				#if defined(NB_WINDOWS)
					#include <windows.h>
				#else
					#include <pthread.h>
				#endif

				#include "nbType.h"

				struct nbMutex
				{
					Bool bMemoryManaged;
					#if defined(NB_WINDOWS)
						CRITICAL_SECTION hMutex;
					#else
						pthread_mutex_t hMutex;
					#endif
				};

			#endif
		#endif

	#ifdef __cplusplus
	}
	#endif
#endif
