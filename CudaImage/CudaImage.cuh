#include "../MagaFirstTermCourseProject.FormsApp/ClusteredImage.h"

using namespace CommonTypes;

#ifndef KERNEL
#define KERNEL
ClusteredImage calc(std::vector<Pixel>& pixels, int k);
bool healthCheck();
#endif