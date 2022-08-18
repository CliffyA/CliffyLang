#ifndef _NB_TYPE_H_
#define _NB_TYPE_H_

	#if defined __cplusplus
	extern "C" {
	#endif

		#include <stddef.h>
		#include <stdint.h>

		#define TEH_FALSE   0
		#define TEH_TRUE    1


		#define NB_FALSE   0
		#define NB_TRUE    1


		#define NB_TYPE_BOOL 0
		#define NB_TYPE_INT8 1
		#define NB_TYPE_INT16 2
		#define NB_TYPE_INT32 3
		#define NB_TYPE_INT64 4

		#define NB_TYPE_UINT8 5
		#define NB_TYPE_UINT16 7
		#define NB_TYPE_UINT32 8
		
		#define NB_TYPE_STRING 9
		#define NB_TYPE_BLOB 10
		

		typedef int Bool;
#ifndef bool
		typedef int bool;
#endif
		typedef int8_t Int8;
		typedef int16_t Int16;
		typedef int32_t Int32;
		typedef int64_t Int64;

		typedef uint8_t Uint8;
		typedef uint16_t Uint16;
		typedef uint32_t Uint32;
		typedef uint64_t Uint64;

		typedef float Float;
		typedef double Double;

	#ifdef __cplusplus
	}
	#endif
#endif
