#pragma once
#include <vector>
#include "../MagaFirstTermCourseProject.FormsApp/ClusteredImage.h"

#ifdef _DLLEXPORT_
#define _DECLARATOR_ __declspec(dllexport)
#else
#define _DECLARATOR_ __declspec(dllimport)
#endif

using namespace CommonTypes;



extern "C"
{
	ClusteredImage _DECLARATOR_ __cdecl KMeans(std::vector<Pixel>&, int);
	bool _DECLARATOR_ __cdecl HealthCheck();
}
