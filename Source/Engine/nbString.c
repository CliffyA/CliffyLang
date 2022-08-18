#define DUCK_SECRET
#include "nbString.h"
#include "nbMemoryManager.h"
#include "nbAssert.h"
#include <utf8proc/utf8proc.h>
#include <string.h>
#include <stdio.h>

	nbString* nbString_Create(const char* szString)
	{
		nbString* pString = (nbString*)nbMalloc(sizeof(nbString));
		nbString_Set(pString, szString);
		return pString;
	}

	nbString* nbString_Clone(const nbString* pString)
	{
		nbAssert(pString);
		return nbString_Create(nbString_GetCString(pString));
	}

	void nbString_Destroy(nbString* pString)
	{
		nbAssert(pString);
		nbFree(pString->szString);
		nbFree(pString);
	}

	Bool nbString_Compare(const nbString* pStringA, const nbString* pStringB)
	{
		return strcmp(pStringA->szString, pStringB->szString) == 0;
	}

	Bool nbString_IsEqual(const nbString* pStringA, const nbString* pStringB)
	{
		return strcmp(pStringA->szString, pStringB->szString) == 0;
	}
	
	Uint32 nbString_GetLength(nbString* pString)
	{
		nbAssert(pString);
		return pString->nLength;
	}
	
	const char* nbString_GetCString(const nbString* pString)
	{
		nbAssert(pString);
		return pString->szString;
	}

	extern Uint32 nbString_GetUnicodeLength(nbString* pString)
	{
		Uint32 nLength = 0;
		ssize_t nOffset = 0;
		//ssize_t nPrevious = 0;
		while (TEH_TRUE)
		{
			int32_t nChar;
			ssize_t nReadSize = utf8proc_iterate((const uint8_t*)pString->szString + nOffset, pString->nLength - nOffset, &nChar);
			if (nReadSize < 0 || nChar < 0)
				break;
			//nPrevious = nOffset;
			nOffset += nReadSize;
			nLength++;
		}

		return nLength;
	}

	Uint32 nbString_GetUnicodeChar(nbString* pString, Uint32 nIndex)
	{
		Uint32 nLength = 0;
		ssize_t nOffset = 0;
		//ssize_t nPrevious = 0;
		while (TEH_TRUE)
		{
			int32_t nChar;
			ssize_t nReadSize = utf8proc_iterate((const uint8_t*)pString->szString + nOffset, pString->nLength - nOffset, &nChar);
			if (nReadSize < 0 || nChar < 0)
				break;
			//nPrevious = nOffset;
			nOffset += nReadSize;

			if (nLength == nIndex)
				return nChar;
			
			nLength++;
		}

		return 0;
	}
	
	void nbString_Set(nbString* pString, const char* szString)
	{
		Uint32 nLength;
		nbAssert(pString);
		nLength = (Uint32)strlen(szString);
		nbString_SizeToFit(pString, nLength);
		memcpy(pString->szString, szString, nLength);
		pString->nLength = nLength;
		pString->szString[pString->nLength] = '\0';
	}

	void nbString_SetString(nbString* pString, const nbString* pString2)
	{
		nbString_Set(pString, pString2->szString);
	}

	void nbString_Append(nbString* pString, const char* szString)
	{
		Uint32 nLength;
		nbAssert(pString);
		nLength = (Uint32)strlen(szString);
		nbString_SizeToFit(pString, pString->nLength + nLength);
		memcpy(pString->szString + pString->nLength, szString, nLength);
		pString->nLength += nLength;
		pString->szString[pString->nLength] = '\0';
	}
	
	void nbString_AppendString(nbString* pString, const nbString* pString2)
	{
		nbAssert(pString);
		nbString_SizeToFit(pString, pString->nLength + pString2->nLength);
		memcpy(pString->szString + pString->nLength, pString2->szString, pString2->nLength);
		pString->nLength += pString2->nLength;
		pString->szString[pString->nLength] = '\0';
	}
	
	void nbString_AppendChar(nbString* pString, const char c)
	{
		nbAssert(pString);
		nbString_SizeToFit(pString, pString->nLength + 1);
		pString->szString[pString->nLength] = c;
		pString->nLength++;
		pString->szString[pString->nLength] = '\0';
	}

	void nbString_AppendUnicodeChar(nbString* pString, Uint32 nChar)
	{
		//int nTemp = 0;
		ssize_t nSize;
		char szTemp[8];
		nbAssert(pString);


		nSize = utf8proc_encode_char(nChar, (uint8_t*)szTemp);
		nbAssert(nSize < 8);
		szTemp[nSize] = '\0';

		nbString_Append(pString, szTemp);

		//nTemp++;
	}
	
	void nbString_AppendUint8(nbString* pString, const Uint8 n)
	{
		nbAssert(pString);
		nbString_AppendUint32(pString, n);
	}

	extern void nbString_AppendInt32(nbString* pString, const Int32 n)
	{
		char szTemp[32];
		nbAssert(pString);
		sprintf(szTemp, "%d", n);
		nbString_Append(pString, szTemp);
	}

	extern void nbString_AppendInt64(nbString* pString, const Int64 n)
	{
		char szTemp[32];
		nbAssert(pString);
		#ifdef PRId64
			sprintf(szTemp, "%" PRId64 "", n);
		#else
			sprintf(szTemp, "%lld", n);
		#endif
		nbString_Append(pString, szTemp);
	}

	void nbString_AppendUint32(nbString* pString, const Uint32 n)
	{
		char szTemp[32];
		nbAssert(pString);
		sprintf(szTemp, "%u", n);
		nbString_Append(pString, szTemp);
	}

	void nbString_AppendFloat(nbString* pString, const float f)
	{
		char szTemp[32];
		nbAssert(pString);
		sprintf(szTemp, "%f", f);
		nbString_Append(pString, szTemp);
	}

	void nbString_Replace(nbString* pString, const char* szFind, const char* szReplace)
	{
		Uint32 i = 0;
		Uint32 nFindLength = (Uint32)strlen(szFind);
		nbString* pTemp = nbString_Create("");
		while (i < pString->nLength)
		{
			if (memcmp(pString->szString + i, szFind, nFindLength) == 0)
			{
				nbString_Append(pTemp, szReplace);
				i += strlen(szFind);
				continue;
			}
			nbString_AppendChar(pTemp, pString->szString[i]);
			i++;
		}
		nbString_Set(pString, pTemp->szString);
		nbString_Destroy(pTemp);
	}

	Bool nbString_StartsWith(nbString* pString, const char* szCompare)
	{
		if (pString->nLength < strlen(szCompare))
			return TEH_FALSE;
		if (memcmp(pString->szString, szCompare, strlen(szCompare)) == 0)
			return TEH_TRUE;
		return TEH_FALSE;
	}

	Bool nbString_EndsWith(nbString* pString, const char* szCompare)
	{
		size_t nLength = strlen(szCompare);
		if (pString->nLength < nLength)
			return TEH_FALSE;
		if (memcmp(pString->szString + pString->nLength - nLength, szCompare, nLength) == 0)
			return TEH_TRUE;
		return TEH_FALSE;
	}

	void nbString_SubString(nbString* pString, Uint32 nStart, Uint32 nLength)
	{
		Uint32 nIndex = 0;
		ssize_t nOffset = 0;
		ssize_t nStartOffset = 0;
		ssize_t nFinishOffset = 0;
		
		// todo unicodes
		nbAssert(nStart <= pString->nLength);
		nbAssert(nStart + nLength <= pString->nLength);

		while (TEH_TRUE)
		{
			int32_t nChar;
			ssize_t nReadSize = utf8proc_iterate((const uint8_t*)pString->szString + nOffset, pString->nLength - nOffset, &nChar);
			
		//	
			//if (nReadSize < 0 || nChar < 0)
			//	break;
			
			if (nIndex == nStart)
				nStartOffset = nOffset;
			if (nIndex == nStart+nLength)
			{
				nFinishOffset = nOffset;
				break;
			}

			nbAssert(nReadSize > 0 && nChar > 0);

			nOffset += nReadSize;
			nIndex++;
		}

		memmove((Uint8*)pString->szString, (Uint8*)pString->szString+nStartOffset, nFinishOffset-nStartOffset);
		pString->nLength = (Uint32)(nFinishOffset-nStartOffset);
		pString->szString[pString->nLength] = '\0';
	}


	// Bloblike wotsits
	nbString* nbString_CreateFromBlob(nbBlob* pBlob)
	{
		nbString* pString = (nbString*)nbMalloc(sizeof(nbString));
		nbString_FromBlob(pString, pBlob);
		return pString;
	}

	void nbString_ToBlob(nbString* pString, nbBlob* pBlob)
	{
		nbBlob_PackUint32(pBlob, pString->nLength);
		nbBlob_PackData(pBlob, (Uint8*)pString->szString, pString->nLength);
	}

	Bool nbString_FromBlob(nbString* pString, nbBlob* pBlob)
	{
		Bool bResult;
		pString->nLength = nbBlob_UnpackUint32(pBlob);
		nbString_SizeToFit(pString, pString->nLength);
		bResult = nbBlob_CheckUnpackData(pBlob, (Uint8*)pString->szString, pString->nLength);
		if (!bResult)
			pString->nLength = 0;
		pString->szString[pString->nLength] = '\0';
		return bResult;
	}




	/* Split String */
	nbSplitString* nbSplitString_Create(const char* szString, const char* szSplit)
	{
		Uint32 i = 0;
		Uint32 nStringLength = (Uint32)strlen(szString);
		Uint32 nSplitLength = (Uint32)strlen(szSplit);

		nbSplitString* pSplitString = (nbSplitString*)nbMalloc(sizeof(nbSplitString));
		nbString* sTemp = nbString_Create("");

		pSplitString->pVector = nbVector_Create();
		
		while (i < nStringLength)
		{
			if (i + nSplitLength < nStringLength)
			{
				if (memcmp(szString + i, szSplit, nSplitLength) == 0)
				{
					nbVector_PushBack(pSplitString->pVector, sTemp);
					sTemp = nbString_Create("");
					i += nSplitLength;
					continue;
				}
			}

			nbString_AppendChar(sTemp, szString[i]);
			i++;
		}

		if (nbString_GetLength(sTemp) > 0)
			nbVector_PushBack(pSplitString->pVector, sTemp);
		else
			nbString_Destroy(sTemp);

		return pSplitString;
	}
	
	void nbSplitString_Destroy(nbSplitString* pSplitString)
	{
		Uint32 i;
		for (i = 0; i < nbVector_GetSize(pSplitString->pVector); i++)
			nbString_Destroy((nbString*)nbVector_Get(pSplitString->pVector, i));
		nbVector_Destroy(pSplitString->pVector);
		nbFree(pSplitString);
	}

	Uint32 nbSplitString_GetNumString(nbSplitString* pSplitString)
	{
		return nbVector_GetSize(pSplitString->pVector);
	}
	
	const char* nbSplitString_GetString(nbSplitString* pSplitString, Uint32 nIndex)
	{
		return nbString_GetCString((nbString*)nbVector_Get(pSplitString->pVector, nIndex));
	}

	#ifdef DUCK_SECRET
		void nbString_SizeToFit(nbString* pString, Uint32 nLength)
		{
			nbAssert(pString);
			if (pString->nBufferSize < nLength+1)
			{
				if (pString->nBufferSize == 0)
				{
					pString->nBufferSize = nLength+1;
					pString->szString = (char*)nbMalloc(pString->nBufferSize);
				}
				else 
				{
					char* szOldString = pString->szString;

					while (pString->nBufferSize < nLength+1)
						pString->nBufferSize = pString->nBufferSize << 1;
				
					pString->szString = (char*)nbMalloc(pString->nBufferSize);
					memcpy(pString->szString, szOldString, pString->nLength+1);
					nbFree(szOldString);
				}
			}
		}
	#endif
