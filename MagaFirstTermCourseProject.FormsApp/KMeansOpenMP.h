#pragma once

#pragma once
#include <omp.h>
#include <iostream>
#include <cmath>
#include "ClusteredImage.h"

using namespace CommonTypes;

namespace KMeansOpenMP {

	using namespace System;

	public ref class ImageHelper
	{
	public:
		double distance(Pixel p1, Pixel p2) {
			return sqrt(pow(p1.r - p2.r, 2) + pow(p1.g - p2.g, 2) + pow(p1.b - p2.b, 2));
		}


		ClusteredImage kMeansClustering(std::vector<Pixel>& pixels, int k) {
			auto a = omp_get_max_threads();
			omp_set_num_threads(2);
			std::vector<Pixel> centroids(k);
			for (int i = 0; i < k; i++) {
				centroids[i] = pixels[rand() % pixels.size()];
			}

			std::vector<int> assignments(pixels.size());
			int o = 0;
#pragma omp parallel
			{
#pragma omp for 
				for (int i = 0; i < pixels.size(); i++) {
					double minDist = distance(pixels[i], centroids[0]);
					//o++;
					int minIndex = 0;
					for (int j = 1; j < k; j++) {
						double dist = distance(pixels[i], centroids[j]);
						//o++;
						if (dist < minDist) {
							minDist = dist;
							//o++;
							minIndex = j;
							//o++;
						}
					}
					if (assignments[i] != minIndex) {
						assignments[i] = minIndex;
						//o++;
					}
				}
			}


			std::vector<Pixel> sums(k);
			std::vector<int> counts(k, 0);
#pragma omp parallel
			{
#pragma omp for 
				for (int i = 0; i < pixels.size(); i++) {
					sums[assignments[i]].r += pixels[i].r;
					sums[assignments[i]].g += pixels[i].g;
					sums[assignments[i]].b += pixels[i].b;
					counts[assignments[i]]++;
				}

			}

#pragma omp parallel
			{
#pragma omp for 
				for (int i = 0; i < k; i++) {
					if (counts[i] == 0) counts[i]++;
					centroids[i].r = sums[i].r / counts[i];
					centroids[i].g = sums[i].g / counts[i];
					centroids[i].b = sums[i].b / counts[i];
				}
			}


			ClusteredImage image;

			image.assignments = assignments;
			image.centroids = centroids;

			return image;
		}
	};





}
