#ifndef _NB_PLATFORM_H_
#define _NB_PLATFORM_H_
	#if defined __cplusplus
	extern "C" {
	#endif

		#if defined (_WIN32)
			#define NB_WINDOWS

			#ifdef _WIN64
				#define NB_64
			#else
				#define NB_32
			#endif
		#endif

		#if defined (__APPLE__)
			#include "TargetConditionals.h"
			#if TARGET_OS_IPHONE
	/*) || defined(TARGET_IPHONE_SIMULATOR)*/
				#define NB_IOS
			#else
				#define NB_OSX
			#endif

			/*#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))*/
		#elif defined(EMSCRIPTEN)
			#define NB_EMSCRIPTEN
		#elif defined(CMAKE_PLATFORM_ANDROID)
			#define NB_ANDROID
		#elif defined(__linux__)
		/*defined(NB_WINDOWS)|| defined(NB_OSX)
	|| defined(NB_EMSCRIPTEN)*/
			#define NB_GLFW3
			#define NB_LINUX
		#endif

		

		#ifdef DUCK_SECRET
			#include "nbType.h"

			typedef struct nbPlatform nbPlatform;

			typedef void (nbPlatform_Destroy_CB)(void);
			typedef void (nbPlatform_MainLoop_CB)(void);
			typedef Uint64 (nbPlatform_GetTime_CB)(void);
			typedef int (nbPlatform_GetScreenWidth_CB)(void);
			typedef int (nbPlatform_GetScreenHeight_CB)(void);
			typedef int (nbPlatform_GetGlVersion_CB)(void);
			typedef Uint32 (nbPlatform_Audio_Push_CB)(Float* pLeftChannel, Float* pRightChannel, Uint32 nNumSample);
			typedef Uint32 (nbPlatform_Audio_GetSampleRate_CB)(void);
			typedef void (nbPlatform_ShowKeyboard_CB)(void);
			typedef void (nbPlatform_HideKeyboard_CB)(void);

			struct nbPlatform
			{
				void* pUserPointer;

				nbPlatform_Destroy_CB* pDestroy;
				nbPlatform_MainLoop_CB* pMainLoop;
				nbPlatform_GetTime_CB* pGetTime;
				nbPlatform_GetScreenWidth_CB* pGetScreenWidth;
				nbPlatform_GetScreenHeight_CB* pGetScreenHeight;
				nbPlatform_GetGlVersion_CB* pGetGlVersion;
				nbPlatform_Audio_Push_CB* pAudioPush;
				nbPlatform_Audio_GetSampleRate_CB* pAudioGetSampleRate;
				nbPlatform_ShowKeyboard_CB* pShowKeyboard;
				nbPlatform_HideKeyboard_CB* pHideKeyboard;
			};

			extern nbPlatform* nbPlatform_Create(nbPlatform_Destroy_CB* pDestroy, nbPlatform_MainLoop_CB* pMainLoop, nbPlatform_GetTime_CB* pGetTime, nbPlatform_GetScreenWidth_CB* pGetScreenWidth, nbPlatform_GetScreenHeight_CB* pGetScreenHeight, nbPlatform_GetGlVersion_CB* pGetGlVersion, nbPlatform_Audio_Push_CB* pAudioPush, nbPlatform_Audio_GetSampleRate_CB* pAudioGetSampleRate, nbPlatform_ShowKeyboard_CB* pShowKeyboard, nbPlatform_HideKeyboard_CB* pHideKeyboard);
			extern void nbPlatform_Destroy(nbPlatform* pPlatform);
		#endif

	#ifdef __cplusplus
	}
	#endif
#endif
