#include "CudaImage.h"
#include "CudaImage.cuh"
#include <windows.h>

ClusteredImage KMeans(std::vector<Pixel>& pixels, int k)
{
	return calc(pixels, k);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
