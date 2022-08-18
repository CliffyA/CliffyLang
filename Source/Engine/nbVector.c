#define DUCK_SECRET
#include "nbVector.h"
#include "nbMemoryManager.h"
#include "nbAssert.h"
#include <string.h>
#include <stdlib.h>

	nbVector* nbVector_Create(void)
	{
		nbVector* pVector;

		pVector = (nbVector*)nbMalloc(sizeof(nbVector));
			pVector->nArraySize = DUCK_VECTOR_DEFAULT_ARRAY_SIZE;
			pVector->pArray = (void**)nbMalloc(pVector->nArraySize * DUCK_VECTOR_POINTER_SIZE);
		return pVector;
	}

	void nbVector_Destroy(nbVector* pVector)
	{
		nbAssert(pVector);
		nbFree(pVector->pArray);
		nbFree(pVector);
	}


	void nbVector_PushFront(nbVector* pVector, void* pObject)
	{
		nbAssert(pVector);

		if (pVector->nSize == pVector->nArraySize)
			nbVector_Expand(pVector);

		memmove(pVector->pArray + 1, pVector->pArray, DUCK_VECTOR_POINTER_SIZE*pVector->nSize);
		pVector->pArray[0] = pObject;
		pVector->nSize++;
	}
	
	void nbVector_PushBack(nbVector* pVector, void* pObject)
	{
		nbAssert(pVector);

		if (pVector->nSize == pVector->nArraySize)
			nbVector_Expand(pVector);

		pVector->pArray[pVector->nSize] = pObject;
		pVector->nSize++;
	}

	void* nbVector_PopFront(nbVector* pVector)
	{
		void* pObject = nbVector_GetFront(pVector);
		if (pVector->nSize > 0)
		{
			memmove(pVector->pArray, pVector->pArray + 1, DUCK_VECTOR_POINTER_SIZE*(pVector->nSize-1));
			pVector->nSize--;
		}
		return pObject;
	}

	void* nbVector_PopBack(nbVector* pVector)
	{
		void* pObject = nbVector_GetBack(pVector);
		if (pVector->nSize > 0)
			pVector->nSize--;
		return pObject;
	}

	Uint32 nbVector_GetSize(nbVector* pVector)
	{
		nbAssert(pVector);
		return pVector->nSize;
	}

	void* nbVector_Get(nbVector* pVector, Uint32 nIndex)
	{
		nbAssert(pVector);
		nbAssert(nIndex < pVector->nSize);
		return pVector->pArray[nIndex];
	}

	void* nbVector_GetFront(nbVector* pVector)
	{
		if (pVector->nSize == 0)
			return NULL;
		return nbVector_Get(pVector, 0);
	}

	void* nbVector_GetBack(nbVector* pVector)
	{
		if (pVector->nSize == 0)
			return NULL;
		return nbVector_Get(pVector, nbVector_GetSize(pVector)-1);
	}

	void* nbVector_GetRandom(nbVector* pVector)
	{
		Uint32 nIndex;
		if (pVector->nSize == 0)
			return NULL;
		nIndex = rand() % pVector->nSize;
		return pVector->pArray[nIndex];
	}

	void nbVector_Set(nbVector* pVector, Uint32 nIndex, void* pObject)
	{
		nbAssert(pVector);
		nbAssert(nIndex < pVector->nSize);
		pVector->pArray[nIndex] = pObject;
	}

	void nbVector_Insert(nbVector* pVector, Uint32 nIndex, void* pObject)
	{
		nbAssert(pVector);

		if (nIndex == 0)
		{
			nbVector_PushFront(pVector, pObject);
			return;
		}

		nbAssert(nIndex <= pVector->nSize);

		if (pVector->nSize == pVector->nArraySize)
			nbVector_Expand(pVector);

		memmove(pVector->pArray + nIndex + 1, pVector->pArray + nIndex, DUCK_VECTOR_POINTER_SIZE*(pVector->nSize-nIndex));
		pVector->pArray[nIndex] = pObject;
		pVector->nSize++;
	}

	void nbVector_Erase(nbVector* pVector, Uint32 nIndex)
	{
		Uint32 nNumRemain;
		nbAssert(nIndex < pVector->nSize);

		nNumRemain = pVector->nSize - nIndex - 1;
		if (nNumRemain > 0)
			memmove(pVector->pArray + nIndex, pVector->pArray + nIndex + 1, DUCK_VECTOR_POINTER_SIZE * nNumRemain);
		pVector->nSize--;
	}

	void nbVector_Clear(nbVector* pVector)
	{
		pVector->nSize = 0;
	}

	void nbVector_Shuffle(nbVector* pVector)
	{
		Uint32 i;
		for (i = 0; i < pVector->nSize - 1; i++) 
		{
			Uint32 j = i + rand() / (RAND_MAX / (pVector->nSize - i) + 1);
			void* p = pVector->pArray[j];
			pVector->pArray[j] = pVector->pArray[i];
			pVector->pArray[i] = p;
		}
	}

	void nbVector_Expand(nbVector* pVector)
	{
		void** pNewArray;
		pVector->nArraySize *= 2;
		pNewArray = (void**)nbMalloc(DUCK_VECTOR_POINTER_SIZE*pVector->nArraySize);
		memcpy(pNewArray, pVector->pArray, DUCK_VECTOR_POINTER_SIZE*pVector->nSize);
		nbFree(pVector->pArray);
		pVector->pArray = pNewArray;
	}