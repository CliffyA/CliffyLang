#ifndef _NB_MEMORY_H_
#define _NB_MEMORY_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#include "nbType.h"
		#include "nbPlatform.h"

		#ifndef NB_EMSCRIPTEN
			#define NB_MEMORY_DEBUG
		#endif
		#define NB_MEMORY_DEBUG_OVERFLOW
		#define NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE 32

		#define nbMalloc(x) nbMemoryManager_Malloc(x, __FILE__, __LINE__)
		#define nbFree(x) nbMemoryManager_Free(x)

		extern void nbMemoryManager_Startup(void);
		extern void nbMemoryManager_Shutdown(void);

		extern Bool nbMemoryManager_Active(void);
		
		extern void* nbMemoryManager_Malloc(size_t nSize, const char* szFile, int nLine);
		extern void nbMemoryManager_Free(void* pPointer);

		#ifdef DUCK_SECRET
			#ifdef NB_MEMORY_DEBUG

				#include "nbMutex.h"

				typedef struct ndAllocation ndAllocation;
				struct ndAllocation
				{
					void* pPointer;
					Uint32 nSize;
					Uint32 nId;
					char* szFile;
					int nLine;
					ndAllocation* pPrevious;
					ndAllocation* pNext;
				};

				typedef struct nbMemoryManager nbMemoryManager;
				struct nbMemoryManager
				{
					ndAllocation* pLastAllocation;
					Uint32 nLastId;

					#ifdef NB_MEMORY_DEBUG_OVERFLOW
						Uint8 nOverflowCheck[NB_MEMORY_DEBUG_OVERFLOW_CHECK_SIZE];
					#endif

					nbMutex* pMutex;
				};
				extern nbMemoryManager* nb_pMemoryManager;
			#endif
		#endif

	#ifdef __cplusplus
	}
	#endif

#endif
