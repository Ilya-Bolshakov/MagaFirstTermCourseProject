#pragma once
using namespace System;

#include <vector>

namespace CommonTypes {


    struct Pixel {
        int r, g, b;
    };


    struct ClusteredImage {
        std::vector<Pixel> centroids;
        std::vector<int> assignments;
    };

}

