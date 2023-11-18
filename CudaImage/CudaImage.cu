#include "CudaImage.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../MagaFirstTermCourseProject.FormsApp/ClusteredImage.h"
#include <thrust/device_vector.h>

using namespace CommonTypes;

/*
* DOCS
* d_labels == assignments
*/


__global__ void kmeans_kernel(std::vector<Pixel> centroids, int* assignments, int k, std::vector<Pixel> pixels) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < pixels.size()) {
		float minDist = INFINITY;
		int label = 0;

		for (int i = 0; i < k; i++) {
			float dist = 0.0f;
			
			dist = sqrt(pow(pixels[idx].r - centroids[i].r, 2) + pow(pixels[idx].g - centroids[i].g, 2) + pow(pixels[idx].b - centroids[i].b, 2));

			if (dist < minDist) {
				minDist = dist;
				label = i;
			}
		}

		assignments[idx] = label;
	}
}




ClusteredImage calc(std::vector<Pixel>& pixels, int k)
{
	std::vector<Pixel> centroids(k);
	thrust::device_vector<int> assignments;

	for (int i = 0; i < k; i++) {
		centroids[i] = pixels[rand() % pixels.size()];
	}

	//cudaMalloc((void**)&d_pixels, sizeof(Pixel) * pixels.size());
	//cudaMalloc((void**)&centroids, sizeof(Pixel) * centroids.size());
	cudaMalloc((void**)&assignments, sizeof(int) * pixels.size());

	thrust::device_vector<Pixel> d_pixels(pixels);
	thrust::device_vector<Pixel> d_centroids(centroids);

	int block_size = 256;
	int grid_size = (pixels.size() + block_size - 1) / block_size;

	kmeans_kernel <<<grid_size, block_size >>> (d_pixels, d_centroids, assignments, k);


	std::vector<Pixel> sums(k);
	std::vector<int> counts(k, 0);
	for (int i = 0; i < pixels.size(); i++) {
		sums[assignments[i]].r += pixels[i].r;
		sums[assignments[i]].g += pixels[i].g;
		sums[assignments[i]].b += pixels[i].b;
		counts[assignments[i]]++;
	}
	for (int i = 0; i < k; i++) {
		if (counts[i] == 0) counts[i]++;
		centroids[i].r = sums[i].r / counts[i];
		centroids[i].g = sums[i].g / counts[i];
		centroids[i].b = sums[i].b / counts[i];
	}

	ClusteredImage image;

	std::vector<int> a;

	for (size_t i = 0; i < assignments.size(); i++)
	{
		a.push_back(assignments[i]);
	}

	image.assignments = a;
	image.centroids = centroids;

	return image;
}