#define DUCK_SECRET
#include "nbMemoryManager.h"
#include "nbAssert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	#ifdef NB_MEMORY_DEBUG
		nbMemoryManager* nb_pMemoryManager = NULL;
	#endif

	void nbMemoryManager_Startup(void)
	{
		#ifdef NB_MEMORY_DEBUG
			nbMutex* pMutex;

			nbAssert(!nb_pMemoryManager);

			pMutex = nbMutex_Create();

			nb_pMemoryManager = (nbMemoryManager*)malloc(sizeof(nbMemoryManager));
			memset(nb_pMemoryManager, 0, sizeof(nbMemoryManager));

			nb_pMemoryManager->pMutex = pMutex;
		#endif
	}
	
	void nbMemoryManager_Shutdown(void)
	{
		#ifdef NB_MEMORY_DEBUG
			nbMutex_Lock(nb_pMemoryManager->pMutex);
				if (nb_pMemoryManager->pLastAllocation)
				{
					//ndAllocation* pTemp = s_pAllocationList;
					printf("********************** Leaks Detected ************************\n");
					while (nb_pMemoryManager->pLastAllocation)
					{
						printf("[%d] %s (%d)\n", nb_pMemoryManager->pLastAllocation->nId, nb_pMemoryManager->pLastAllocation->szFile, nb_pMemoryManager->pLastAllocation->nLine);
						nbMemoryManager_Free(nb_pMemoryManager->pLastAllocation->pPointer);
					}
					nbAssert(TEH_FALSE);
				}
			nbMutex_Unlock(nb_pMemoryManager->pMutex);

			nbMutex_Destroy(nb_pMemoryManager->pMutex);

			free(nb_pMemoryManager);
			nb_pMemoryManager = NULL;
		#endif
	}

	Bool nbMemoryManager_Active(void)
	{
		#ifdef NB_MEMORY_DEBUG
			return nb_pMemoryManager != NULL;
		#else
			return TEH_FALSE;
		#endif
	}


/* Public Functionality */
	void* nbMemoryManager_Malloc(size_t nSize, const char* szFile, int nLine)
	{
		//printf("%zu %s %d\n", nSize, szFile, nLine);
		#ifdef NB_MEMORY_DEBUG

			ndAllocation* pNext;
			size_t nAllocSize;
			void* pPointer;
		
			//if (nSize > 1024*1024*1)
			//	printf("Big ALLOC! %s:%d\n", szFile, nLine);

			if (!nb_pMemoryManager)
			{
				printf("**************** Plz initialize nbMemoryManager ****************\n");
				printf("%s:%d\n", szFile, nLine);
				nbAssert(nb_pMemoryManager); // you have not called nbApplication_Startup/nbMemoryManager_Startup
			}

			nbMutex_Lock(nb_pMemoryManager->pMutex);

				nAllocSize = sizeof(ndAllocation) + nSize;
				#ifdef NB_MEMORY_DEBUG_OVERFLOW
					nAllocSize += NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE * 2;
				#endif

				pNext = (ndAllocation*)malloc(nAllocSize);
				memset(pNext, 0, nAllocSize);

				pNext->nSize = (Uint32)nSize;

				#ifdef NB_MEMORY_DEBUG_OVERFLOW
					pNext->pPointer = ((Uint8*)pNext) + sizeof(ndAllocation) + NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE;
				#else
					pNext->pPointer = ((Uint8*)pNext) + sizeof(ndAllocation);
				#endif

				//nbAssert(pNext->pPointer);
				//memset(pNext->pPointer, 0, nSize);
				pNext->nId = ++nb_pMemoryManager->nLastId;
				pNext->szFile = (char*)malloc(strlen(szFile)+1);
				nbAssert(pNext->szFile);
				strcpy(pNext->szFile, szFile);
				pNext->nLine = nLine;

				/*if (pNext->nId == 236)
				{
					int ff = 0;
				}*/
				
				if (nb_pMemoryManager->pLastAllocation)
				{
					pNext->pPrevious = nb_pMemoryManager->pLastAllocation;
					nb_pMemoryManager->pLastAllocation->pNext = pNext;
				}
				nb_pMemoryManager->pLastAllocation = pNext;

				pPointer = nb_pMemoryManager->pLastAllocation->pPointer;

			nbMutex_Unlock(nb_pMemoryManager->pMutex);
			
			return pPointer;
		#else
			void* pPointer = malloc(nSize);
			memset(pPointer, 0, nSize);
			return pPointer;
		#endif
	}
	
	void nbMemoryManager_Free(void* pPointer)
	{
		#ifdef NB_MEMORY_DEBUG
			ndAllocation* pAllocation;
			
			if (!pPointer)
				return;

			nbMutex_Lock(nb_pMemoryManager->pMutex);

				#ifdef NB_MEMORY_DEBUG_OVERFLOW
					pAllocation = (ndAllocation*)(((Uint8*)pPointer) - sizeof(ndAllocation) - NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE);

					if (memcmp(((Uint8*)pAllocation) + sizeof(ndAllocation), nb_pMemoryManager->nOverflowCheck, NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE) != 0)
					{
						printf("Before Check! [%d] %s (%d)\n", pAllocation->nId, pAllocation->szFile, pAllocation->nLine);
						nbAssert(TEH_FALSE);
					}

					if (memcmp(((Uint8*)pAllocation) + sizeof(ndAllocation) + NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE + pAllocation->nSize, nb_pMemoryManager->nOverflowCheck, NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE) != 0)
					{
						printf("After Check! [%d] %s (%d)\n", pAllocation->nId, pAllocation->szFile, pAllocation->nLine);
						nbAssert(TEH_FALSE);
					}
					
				#else
					pAllocation = (ndAllocation*)(((Uint8*)pPointer) - sizeof(ndAllocation));
				#endif

				if (pAllocation->pPrevious)
					pAllocation->pPrevious->pNext = pAllocation->pNext;

				if (pAllocation->pNext)
					pAllocation->pNext->pPrevious = pAllocation->pPrevious;
				
				if (!pAllocation->pNext)
					nb_pMemoryManager->pLastAllocation = pAllocation->pPrevious;

				free(pAllocation->szFile);
				free(pAllocation);

			nbMutex_Unlock(nb_pMemoryManager->pMutex);

			//printf("Unknown pointer: %x\n", (unsigned int)pPointer);
			//nbAssert(TEH_FALSE);
		#else
			free(pPointer);
		#endif
	}