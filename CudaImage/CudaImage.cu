#include "CudaImage.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../MagaFirstTermCourseProject.FormsApp/ClusteredImage.h"
#include <iostream>

using namespace CommonTypes;

/*
* DOCS
* d_labels == assignments
*/


__global__ void kmeans_kernel(float* d_data, float* d_centroids, int* d_labels, int k, int countPixels) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < countPixels) {
		float min_dist = sqrt((d_data[idx * 3] - d_centroids[0]) * (d_data[idx * 3] - d_centroids[0])
							   + (d_data[idx * 3 + 1] - d_centroids[1]) * (d_data[idx * 3 + 1] - d_centroids[1])
								   + (d_data[idx * 3 + 2] - d_centroids[2]) * (d_data[idx * 3 + 2] - d_centroids[2]));
		int label = 0;

		for (int i = 0; i < k; i++) {
			float dist = 0.0f;

			dist = sqrt((d_data[idx * 3] - d_centroids[k * 3]) * (d_data[idx * 3] - d_centroids[k * 3])
				+ (d_data[idx * 3 + 1] - d_centroids[k * 3 + 1]) * (d_data[idx * 3 + 1] - d_centroids[k * 3 + 1])
				+ (d_data[idx * 3 + 2] - d_centroids[k * 3 + 2]) * (d_data[idx * 3 + 2] - d_centroids[k * 3 + 2]));

			if (dist < min_dist) {
				min_dist = dist;
				label = i;
			}
		}

		d_labels[idx] = label;
	}
}



ClusteredImage calc(std::vector<Pixel>& pixels, int k)
{
	float* device_data;
	float* device_centroids;
	int* device_assignments;

	float* pixelsInPtr = new float[pixels.size() * 3];

	for (int i = 0; i < pixels.size(); i++) {
		for (int j = 0; j < 3; j++) {
			pixelsInPtr[3 * i] = pixels[i].r;
			pixelsInPtr[3 * i + 1] = pixels[i].g;
			pixelsInPtr[3 * i + 2] = pixels[i].b;
		}
	}

	float* centroidsPtr = new float[k * 3];
	for (int i = 0; i < k; i++) {
		auto rndPixel = pixels[rand() % pixels.size()];
		centroidsPtr[3 * i] = rndPixel.r;
		centroidsPtr[3 * i + 1] = rndPixel.g;
		centroidsPtr[3 * i + 2] = rndPixel.b;
	}

	cudaMalloc((void**)&device_data, sizeof(float) * pixels.size() * 3);
	cudaMalloc((void**)&device_centroids, sizeof(float) * k * 3);
	cudaMalloc((void**)&device_assignments, sizeof(int) * pixels.size());

	cudaMemcpy(device_data, pixelsInPtr, sizeof(float) * pixels.size() * 3, cudaMemcpyHostToDevice);
	cudaMemcpy(device_centroids, centroidsPtr, sizeof(float) * k * 3, cudaMemcpyHostToDevice);
	cudaMemcpy(device_assignments, centroidsPtr, sizeof(float) * k * 3, cudaMemcpyHostToDevice);


	dim3 block_size = 256;
	dim3 grid_size = (pixels.size() + 256 - 1) / 256;

	kmeans_kernel <<<grid_size, block_size >>> (device_data, device_centroids, device_assignments, k, pixels.size());

	int* assignmentsPtr = new int[pixels.size()];
    cudaMemcpy(assignmentsPtr, device_assignments, sizeof(int) * pixels.size(), cudaMemcpyDeviceToHost);

	


	std::vector<Pixel> sums(k);
	std::vector<int> counts(k, 0);

	for (int i = 0; i < pixels.size(); i++) {
		auto a = assignmentsPtr[i];
		sums[a].r += pixels[i].r;
		sums[a].g += pixels[i].g;
		sums[a].b += pixels[i].b;
		counts[a]++;
	}

	std::vector<Pixel> centroids(k);
	for (int i = 0; i < k; i++) {
		if (counts[i] == 0) counts[i]++;
		centroids[i].r = sums[i].r / counts[i];
		centroids[i].g = sums[i].g / counts[i];
		centroids[i].b = sums[i].b / counts[i];
	}

	ClusteredImage image;

	//image.assignments = assignments;
	image.centroids = centroids;

	cudaFree(device_data);
	cudaFree(device_assignments);
	cudaFree(device_assignments);

	return image;
}