#ifndef _NB_STRING_H_
#define _NB_STRING_H_
	#if defined __cplusplus
	extern "C" {
	#endif
		#include "nbType.h"
		#include "nbBlob.h"
		
		typedef struct nbString nbString;
		typedef struct nbSplitString nbSplitString;

		extern nbString* nbString_Create(const char* szString);
		extern nbString* nbString_Clone(const nbString* pString);
		extern void nbString_Destroy(nbString* pString);

		extern Bool nbString_Compare(const nbString* pStringA, const nbString* pStringB); // change to something like strcmp one day
		extern Bool nbString_IsEqual(const nbString* pStringA, const nbString* pStringB);
		
		extern Uint32 nbString_GetLength(nbString* pString);
		extern const char* nbString_GetCString(const nbString* pString);

		extern Uint32 nbString_GetUnicodeLength(nbString* pString);
		extern Uint32 nbString_GetUnicodeChar(nbString* pString, Uint32 nIndex);
		
		extern void nbString_Set(nbString* pString, const char* szString);
		extern void nbString_SetString(nbString* pString, const nbString* pString2);
		extern void nbString_Append(nbString* pString, const char* szString);
		extern void nbString_AppendString(nbString* pString, const nbString* pString2);
		extern void nbString_AppendChar(nbString* pString, const char c);
		extern void nbString_AppendUnicodeChar(nbString* pString, Uint32 nChar);
		extern void nbString_AppendUint8(nbString* pString, const Uint8 n);
		extern void nbString_AppendInt32(nbString* pString, const Int32 n);
		extern void nbString_AppendInt64(nbString* pString, const Int64 n);
		extern void nbString_AppendUint32(nbString* pString, const Uint32 n);
		extern void nbString_AppendFloat(nbString* pString, const float f);

		extern void nbString_Replace(nbString* pString, const char* szFind, const char* szReplace);

		extern void nbString_SubString(nbString* pString, Uint32 nStart, Uint32 nLength);

		extern Bool nbString_StartsWith(nbString* pString, const char* szCompare);
		extern Bool nbString_EndsWith(nbString* pString, const char* szCompare);


		/* Blobby Things */
		extern nbString* nbString_CreateFromBlob(nbBlob* pBlob);
		extern void nbString_ToBlob(nbString* pString, nbBlob* pBlob);
		extern Bool nbString_FromBlob(nbString* pString, nbBlob* pBlob);


		/* Split String */
		extern nbSplitString* nbSplitString_Create(const char* szString, const char* szSplit);
		extern void nbSplitString_Destroy(nbSplitString* pSplitString);
		extern Uint32 nbSplitString_GetNumString(nbSplitString* pSplitString);
		extern const char* nbSplitString_GetString(nbSplitString* pSplitString, Uint32 nIndex);


		#ifdef DUCK_SECRET
			#include "nbVector.h"

			struct nbString
			{
				Uint32 nLength;
				Uint32 nBufferSize;
				char* szString;
			};

			struct nbSplitString
			{
				nbVector* pVector;
			};

			void nbString_SizeToFit(nbString* pString, Uint32 nLength);
		#endif

	#ifdef __cplusplus
	}
	#endif
#endif
