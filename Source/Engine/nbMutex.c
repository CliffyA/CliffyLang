#define NB_MUTEX_SECRET
#include "nbMutex.h"

#ifndef NB_EMSCRIPTEN
	#include "nbMemoryManager.h"
	#include "nbAssert.h"

	#include <string.h>
	#include <stdlib.h>


		nbMutex* nbMutex_Create()
		{
			nbMutex* pMutex;

			if (nbMemoryManager_Active())
			{
				pMutex = nbMalloc(sizeof(nbMutex));
				pMutex->bMemoryManaged = TEH_TRUE;
			}
			else
			{
				pMutex = malloc(sizeof(nbMutex));
				memset(pMutex, 0, sizeof(nbMutex));
			}

			#if defined(NB_WINDOWS)
				InitializeCriticalSection(&pMutex->hMutex);
			#else
				pthread_mutex_init(&pMutex->hMutex, NULL);
			#endif

			return pMutex;
		}

		void nbMutex_Destroy(nbMutex* pMutex)
		{
			nbAssert(pMutex);

			#if defined(NB_WINDOWS)
				DeleteCriticalSection(&pMutex->hMutex);
			#else
				pthread_mutex_destroy(&pMutex->hMutex);
			#endif

			if (pMutex->bMemoryManaged)
			{
				nbFree(pMutex);
			}
			else
			{
				free(pMutex);
			}
		}

		void nbMutex_Lock(nbMutex* pMutex)
		{
			#if defined(NB_WINDOWS)
				EnterCriticalSection(&pMutex->hMutex);
			#else
				pthread_mutex_lock(&pMutex->hMutex);
			#endif
		}

		void nbMutex_Unlock(nbMutex* pMutex)
		{
			#if defined(NB_WINDOWS)
				LeaveCriticalSection(&pMutex->hMutex);
			#else
				pthread_mutex_unlock(&pMutex->hMutex);
			#endif
		}
#endif