#define DUCK_SECRET
#include "nbPlatform.h"
#include "nbMemoryManager.h"

	nbPlatform* nbPlatform_Create(nbPlatform_Destroy_CB* pDestroy, nbPlatform_MainLoop_CB* pMainLoop, nbPlatform_GetTime_CB* pGetTime, nbPlatform_GetScreenWidth_CB* pGetScreenWidth, nbPlatform_GetScreenHeight_CB* pGetScreenHeight, nbPlatform_GetGlVersion_CB* pGetGlVersion, nbPlatform_Audio_Push_CB* pAudioPush, nbPlatform_Audio_GetSampleRate_CB* pAudioGetSampleRate, nbPlatform_ShowKeyboard_CB* pShowKeyboard, nbPlatform_HideKeyboard_CB* pHideKeyboard)
	{
		nbPlatform* pPlatform = (nbPlatform*)nbMalloc(sizeof(nbPlatform));
			pPlatform->pDestroy = pDestroy;
			pPlatform->pMainLoop = pMainLoop;
			pPlatform->pGetTime = pGetTime;
			pPlatform->pGetScreenWidth = pGetScreenWidth;
			pPlatform->pGetScreenHeight = pGetScreenHeight;
			pPlatform->pGetGlVersion = pGetGlVersion;
			pPlatform->pAudioPush = pAudioPush;
			pPlatform->pAudioGetSampleRate = pAudioGetSampleRate;
			pPlatform->pShowKeyboard = pShowKeyboard;
			pPlatform->pHideKeyboard = pHideKeyboard;
		return pPlatform;
	}

	void nbPlatform_Destroy(nbPlatform* pPlatform)
	{
		pPlatform->pDestroy();
		nbFree(pPlatform);
	}