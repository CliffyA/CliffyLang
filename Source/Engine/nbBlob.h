#ifndef _NB_BLOB_H_
#define _NB_BLOB_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#include "nbType.h"
	
		typedef struct nbBlob nbBlob;
		extern nbBlob* nbBlob_Create(void);
		extern nbBlob* nbBlob_Clone(const nbBlob* pBlob);
		extern void nbBlob_Destroy(nbBlob* pBlob);

		extern void nbBlob_Clear(nbBlob* pBlob);
		
		extern const Uint8* nbBlob_GetData(const nbBlob* pBlob);
		extern Uint32 nbBlob_GetSize(const nbBlob* pBlob);
		extern Uint32 nbBlob_GetOffset(const nbBlob* pBlob);

		extern void nbBlob_SetOffset(nbBlob* pBlob, Uint32 nOffset);

		extern Bool nbBlob_Equals(const nbBlob* pBlobA, const nbBlob* pBlobB);
		
		extern void nbBlob_PackData(nbBlob* pBlob, const Uint8* pData, Uint32 nSize);
		extern void nbBlob_PackBool(nbBlob* pBlob, const Bool bBool);
		extern void nbBlob_PackUint8(nbBlob* pBlob, const Uint8 nUint8);
		extern void nbBlob_PackUint16(nbBlob* pBlob, const Uint16 nUint16);
		extern void nbBlob_PackUint32(nbBlob* pBlob, const Uint32 nUint32);
		extern void nbBlob_PackInt8(nbBlob* pBlob, const Int8 nInt8);
		extern void nbBlob_PackInt16(nbBlob* pBlob, const Int16 nInt16);
		extern void nbBlob_PackInt32(nbBlob* pBlob, const Int32 nInt32);
		extern void nbBlob_PackFloat(nbBlob* pBlob, const Float fFloat);
		extern void nbBlob_PackDouble(nbBlob* pBlob, const Double fDouble);
		extern void nbBlob_PackString(nbBlob* pBlob, const char* szString);
		extern void nbBlob_PackBlob(nbBlob* pBlob, const nbBlob* pPackBlob);

		extern void nbBlob_UnpackData(nbBlob* pBlob, Uint8* pData, Uint32 nSize);
		extern Bool nbBlob_UnpackBool(nbBlob* pBlob);
		extern Uint8 nbBlob_UnpackUint8(nbBlob* pBlob);
		extern Uint16 nbBlob_UnpackUint16(nbBlob* pBlob);
		extern Uint32 nbBlob_UnpackUint32(nbBlob* pBlob);
		extern Int16 nbBlob_UnpackInt16(nbBlob* pBlob);
		extern Int32 nbBlob_UnpackInt32(nbBlob* pBlob);
		extern Float nbBlob_UnpackFloat(nbBlob* pBlob);

		extern Bool nbBlob_CheckUnpackData(nbBlob* pBlob, void* pData, Uint32 nSize);
		extern Bool nbBlob_CheckUnpackBool(nbBlob* pBlob, Bool* pBool);
		extern Bool nbBlob_CheckUnpackUint8(nbBlob* pBlob, Uint8* pUint8);
		extern Bool nbBlob_CheckUnpackUint16(nbBlob* pBlob, Uint16* pUint16);
		extern Bool nbBlob_CheckUnpackUint32(nbBlob* pBlob, Uint32* pUint32);
		extern Bool nbBlob_CheckUnpackInt8(nbBlob* pBlob, Int8* pInt8);
		extern Bool nbBlob_CheckUnpackInt16(nbBlob* pBlob, Int16* pInt16);
		extern Bool nbBlob_CheckUnpackInt32(nbBlob* pBlob, Int32* pInt32);
		extern Bool nbBlob_CheckUnpackBlob(nbBlob* pBlob, nbBlob* pOutBlob);


		#ifdef DUCK_SECRET
			#define NB_BLOB_DEFAULT_SIZE 1024
			struct nbBlob
			{
				Uint32 nBufferSize;
				Uint8* pBuffer;

				Uint32 nSize;
				Uint32 nOffset;
			};
		#endif

	#ifdef __cplusplus
	}
	#endif
#endif
