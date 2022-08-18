#ifndef _NB_VECTOR_H_
#define _NB_VECTOR_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#include "nbType.h"
	
		typedef struct nbVector nbVector;
		extern nbVector* nbVector_Create(void);
		extern void nbVector_Destroy(nbVector* pVector);
		
		extern void nbVector_PushFront(nbVector* pVector, void* pObject);
		extern void nbVector_PushBack(nbVector* pVector, void* pObject);
		extern void* nbVector_PopFront(nbVector* pVector);
		extern void* nbVector_PopBack(nbVector* pVector);
		extern Uint32 nbVector_GetSize(nbVector* pVector);
		extern void* nbVector_Get(nbVector* pVector, Uint32 nIndex);
		extern void* nbVector_GetFront(nbVector* pVector);
		extern void* nbVector_GetBack(nbVector* pVector);
		extern void* nbVector_GetRandom(nbVector* pVector);
		extern void nbVector_Set(nbVector* pVector, Uint32 nIndex, void* pObject);
		extern void nbVector_Insert(nbVector* pVector, Uint32 nIndex, void* pObject);
		extern void nbVector_Erase(nbVector* pVector, Uint32 nIndex);
		extern void nbVector_Clear(nbVector* pVector);

		extern void nbVector_Shuffle(nbVector* pVector);

		#ifdef DUCK_SECRET
			#define DUCK_VECTOR_DEFAULT_ARRAY_SIZE 32
			#define DUCK_VECTOR_POINTER_SIZE sizeof(void*)
			struct nbVector
			{
				Uint32 nSize;

				Uint32 nArraySize;
				void** pArray;
			};

			extern void nbVector_Expand(nbVector* pVector);
		#endif

	#ifdef __cplusplus
	}
	#endif
#endif
