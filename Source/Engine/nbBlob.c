#define DUCK_SECRET
#include "nbBlob.h"
#include "nbMemoryManager.h"
#include "nbAssert.h"
#include <string.h>

	nbBlob* nbBlob_Create(void)
	{
		nbBlob* pBlob = (nbBlob*)nbMalloc(sizeof(nbBlob));
		
		pBlob->nBufferSize = NB_BLOB_DEFAULT_SIZE;
		pBlob->pBuffer = (Uint8*)nbMalloc(pBlob->nBufferSize);

		pBlob->nSize = 0;
		pBlob->nOffset = 0;

		return pBlob;
	}

	nbBlob* nbBlob_Clone(const nbBlob* pBlob)
	{
		nbBlob* pCloneBlob;
		nbAssert(pBlob);
		pCloneBlob = nbBlob_Create();
		nbBlob_PackData(pCloneBlob, nbBlob_GetData(pBlob), nbBlob_GetSize(pBlob));
		pCloneBlob->nOffset = 0;
		return pCloneBlob;
	}

	void nbBlob_Destroy(nbBlob* pBlob)
	{
		nbAssert(pBlob);
		nbFree(pBlob->pBuffer);
		nbFree(pBlob);
	}

	void nbBlob_Clear(nbBlob* pBlob)
	{
		nbAssert(pBlob);
		pBlob->nSize = 0;
		pBlob->nOffset = 0;
	}
	
	const Uint8* nbBlob_GetData(const nbBlob* pBlob) { return pBlob->pBuffer; }
	Uint32 nbBlob_GetSize(const nbBlob* pBlob) { return pBlob->nSize; }
	Uint32 nbBlob_GetOffset(const nbBlob* pBlob) { return pBlob->nOffset; }

	void nbBlob_SetOffset(nbBlob* pBlob, Uint32 nOffset) { pBlob->nOffset = nOffset; }

	Bool nbBlob_Equals(const nbBlob* pBlobA, const nbBlob* pBlobB)
	{
		if (pBlobA->nSize == pBlobB->nSize)
			if (memcmp(pBlobA->pBuffer, pBlobB->pBuffer, pBlobA->nSize) == 0)
				return TEH_TRUE;
		return TEH_FALSE;
	}
	
	void nbBlob_PackData(nbBlob* pBlob, const Uint8* pData, Uint32 nSize)
	{
		nbAssert(pBlob);
		if (pBlob->nOffset + nSize > pBlob->nBufferSize)
		{
			Uint8* pOldBuffer = pBlob->pBuffer;
			while (pBlob->nOffset + nSize > pBlob->nBufferSize)
			{
				// if we are over 100mb, just use the target size, otherwise we'll blow out the RAMs
				if (pBlob->nOffset + nSize > 1024*1024*100)
					pBlob->nBufferSize = pBlob->nOffset + nSize;
				else
					pBlob->nBufferSize <<= 1;
			}
			
			pBlob->pBuffer = (Uint8*)nbMalloc(pBlob->nBufferSize);
			memcpy(pBlob->pBuffer, pOldBuffer, pBlob->nSize);
			nbFree(pOldBuffer);
		}

		memcpy(pBlob->pBuffer + pBlob->nOffset, pData, nSize);
		pBlob->nOffset += nSize;
		if (pBlob->nOffset > pBlob->nSize)
			pBlob->nSize = pBlob->nOffset;
	}

	void nbBlob_PackBool(nbBlob* pBlob, const Bool bBool) { nbBlob_PackUint8(pBlob, (Uint8)bBool); }
	void nbBlob_PackUint8(nbBlob* pBlob, const Uint8 nUint8) { nbBlob_PackData(pBlob, (const Uint8*)&nUint8, sizeof(Uint8)); }
	void nbBlob_PackUint16(nbBlob* pBlob, const Uint16 nUint16) { nbBlob_PackData(pBlob, (const Uint8*)&nUint16, sizeof(Uint16)); }
	void nbBlob_PackUint32(nbBlob* pBlob, const Uint32 nUint32) { nbBlob_PackData(pBlob, (const Uint8*)&nUint32, sizeof(Uint32)); }
	void nbBlob_PackInt8(nbBlob* pBlob, const Int8 nInt8) { nbBlob_PackData(pBlob, (const Uint8*)&nInt8, sizeof(Int8)); }
	void nbBlob_PackInt16(nbBlob* pBlob, const Int16 nInt16) { nbBlob_PackData(pBlob, (const Uint8*)&nInt16, sizeof(Int16)); }
	void nbBlob_PackInt32(nbBlob* pBlob, const Int32 nInt32) { nbBlob_PackData(pBlob, (const Uint8*)&nInt32, sizeof(Int32)); }
	void nbBlob_PackFloat(nbBlob* pBlob, const Float fFloat) { nbBlob_PackData(pBlob, (const Uint8*)&fFloat, sizeof(Float)); }
	void nbBlob_PackDouble(nbBlob* pBlob, const Double fDouble) { nbBlob_PackData(pBlob, (const Uint8*)&fDouble, sizeof(Double)); }

	void nbBlob_PackString(nbBlob* pBlob, const char* szString)
	{
		Uint32 nLength = (Uint32)strlen(szString);
		nbBlob_PackUint32(pBlob, nLength);
		nbBlob_PackData(pBlob, (const Uint8*)szString, nLength);
	}
	
	void nbBlob_PackBlob(nbBlob* pBlob, const nbBlob* pPackBlob)
	{
		nbBlob_PackUint32(pBlob, pPackBlob->nSize);
		nbBlob_PackData(pBlob, pPackBlob->pBuffer, pPackBlob->nSize);
	}



	void nbBlob_UnpackData(nbBlob* pBlob, Uint8* pData, Uint32 nSize)
	{
		nbAssert(pBlob);
		//printf("%u %u %u\n", pBlob->nOffset, nSize, pBlob->nSize);
		nbAssert(pBlob->nOffset + nSize <= pBlob->nSize);

		memcpy(pData, pBlob->pBuffer + pBlob->nOffset, nSize);
		pBlob->nOffset += nSize;
	}
	Bool nbBlob_UnpackBool(nbBlob* pBlob) { Uint8 n; Bool b; nbBlob_UnpackData(pBlob, &n, sizeof(Uint8)); b = n; return b; }
	Uint8 nbBlob_UnpackUint8(nbBlob* pBlob) { Uint8 n; nbBlob_UnpackData(pBlob, (Uint8*)&n, sizeof(Uint8)); return n; }
	Uint16 nbBlob_UnpackUint16(nbBlob* pBlob) { Uint16 n; nbBlob_UnpackData(pBlob, (Uint8*)&n, sizeof(Uint16)); return n; }
	Uint32 nbBlob_UnpackUint32(nbBlob* pBlob) { Uint32 n; nbBlob_UnpackData(pBlob, (Uint8*)&n, sizeof(Uint32)); return n; }
	Int16 nbBlob_UnpackInt16(nbBlob* pBlob) { Int16 n; nbBlob_UnpackData(pBlob, (Uint8*)&n, sizeof(Int16)); return n; }
	Int32 nbBlob_UnpackInt32(nbBlob* pBlob) { Int32 n; nbBlob_UnpackData(pBlob, (Uint8*)&n, sizeof(Int32)); return n; }
	Float nbBlob_UnpackFloat(nbBlob* pBlob) { Float f; nbBlob_UnpackData(pBlob, (Uint8*)&f, sizeof(Float)); return f; }


	Bool nbBlob_CheckUnpackData(nbBlob* pBlob, void* pData, Uint32 nSize)
	{
		if (!pBlob)
			return TEH_FALSE;

		if (pBlob->nOffset + nSize > pBlob->nSize)
			return TEH_FALSE;

		memcpy(pData, pBlob->pBuffer + pBlob->nOffset, nSize);
		pBlob->nOffset += nSize;

		return TEH_TRUE;
	}

	Bool nbBlob_CheckUnpackBool(nbBlob* pBlob, Bool* pBool) { Uint8 n; Bool bResult = nbBlob_CheckUnpackData(pBlob, &n, sizeof(Uint8)); *pBool = n; return bResult; }
	Bool nbBlob_CheckUnpackUint8(nbBlob* pBlob, Uint8* pUint8) { return nbBlob_CheckUnpackData(pBlob, pUint8, sizeof(Uint8)); }
	Bool nbBlob_CheckUnpackUint16(nbBlob* pBlob, Uint16* pUint16) { return nbBlob_CheckUnpackData(pBlob, pUint16, sizeof(Uint16)); }
	Bool nbBlob_CheckUnpackUint32(nbBlob* pBlob, Uint32* pUint32) { return nbBlob_CheckUnpackData(pBlob, pUint32, sizeof(Uint32)); }
	Bool nbBlob_CheckUnpackInt8(nbBlob* pBlob, Int8* pInt8) { return nbBlob_CheckUnpackData(pBlob, pInt8, sizeof(Int8)); }
	Bool nbBlob_CheckUnpackInt16(nbBlob* pBlob, Int16* pInt16) { return nbBlob_CheckUnpackData(pBlob, pInt16, sizeof(Int16)); }
	Bool nbBlob_CheckUnpackInt32(nbBlob* pBlob, Int32* pInt32) { return nbBlob_CheckUnpackData(pBlob, pInt32, sizeof(Int32)); }

	Bool nbBlob_CheckUnpackBlob(nbBlob* pBlob, nbBlob* pOutBlob)
	{
		Uint32 nSize;

		if (!nbBlob_CheckUnpackUint32(pBlob, &nSize))
			return TEH_FALSE;

		if (pBlob->nOffset + nSize > pBlob->nSize)
			return TEH_FALSE;

		nbBlob_PackData(pOutBlob, pBlob->pBuffer + pBlob->nOffset, nSize);
		pBlob->nOffset += nSize;

		return TEH_TRUE;
	}
