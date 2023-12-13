#include "CudaImage.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../MagaFirstTermCourseProject.FormsApp/ClusteredImage.h"
#include <iostream>

using namespace CommonTypes;


__global__ void kmeans_kernel(float* d_data, float* d_centroids, int* d_labels, int* k, int* countPixels) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < *countPixels) {
		double min_dist = sqrt((d_data[idx * 3] - d_centroids[0]) * (d_data[idx * 3] - d_centroids[0])
							   + (d_data[idx * 3 + 1] - d_centroids[1]) * (d_data[idx * 3 + 1] - d_centroids[1])
								   + (d_data[idx * 3 + 2] - d_centroids[2]) * (d_data[idx * 3 + 2] - d_centroids[2]));
		int minIndex = 0;

		for (int j = 1; j < *k; j++) {
			//float dist = 0.0f;

			double dist = sqrt((d_data[idx * 3] - d_centroids[j * 3]) * (d_data[idx * 3] - d_centroids[j * 3])
				+ (d_data[idx * 3 + 1] - d_centroids[j * 3 + 1]) * (d_data[idx * 3 + 1] - d_centroids[j * 3 + 1])
				+ (d_data[idx * 3 + 2] - d_centroids[j * 3 + 2]) * (d_data[idx * 3 + 2] - d_centroids[j * 3 + 2]));

			if (dist < min_dist) {
				min_dist = dist;
				minIndex = j;
			}
		}

		if (d_labels[idx] != minIndex) {
			d_labels[idx] = minIndex;
		}
	}
}



ClusteredImage calc(std::vector<Pixel>& pixels, int k)
{
	float* device_data;
	float* device_centroids;
	int* device_assignments;
	int* device_k;
	int* device_countPixels;

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

	int countPixels = pixels.size();

	cudaMalloc((void**)&device_data, sizeof(float) * pixels.size() * 3);
	cudaMalloc((void**)&device_centroids, sizeof(float) * k * 3);
	cudaMalloc((void**)&device_assignments, sizeof(int) * pixels.size());
	cudaMalloc((void**)&device_k, sizeof(int));
	cudaMalloc((void**)&device_countPixels, sizeof(int));

	cudaMemcpy(device_data, pixelsInPtr, sizeof(float) * pixels.size() * 3, cudaMemcpyHostToDevice);
	cudaMemcpy(device_centroids, centroidsPtr, sizeof(float) * k * 3, cudaMemcpyHostToDevice);
	cudaMemcpy(device_assignments, centroidsPtr, sizeof(float) * k * 3, cudaMemcpyHostToDevice);
	cudaMemcpy(device_k, &k, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(device_countPixels, &countPixels, sizeof(int), cudaMemcpyHostToDevice);


	dim3 block_size = 256;
	dim3 grid_size = (pixels.size() + 256 - 1) / 256;


	kmeans_kernel << <grid_size, block_size >> > (device_data, device_centroids, device_assignments, device_k, device_countPixels);
	
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

	auto vectorAssignments = std::vector<int>(pixels.size());

	for (size_t i = 0; i < pixels.size(); i++)
	{
		vectorAssignments[i] = assignmentsPtr[i];
	}

	image.assignments = vectorAssignments;
	image.centroids = centroids;

	cudaFree(device_data);
	cudaFree(device_assignments);
	cudaFree(device_assignments);
	cudaFree(device_countPixels);
	cudaFree(device_k);

	return image;
}


__global__ void kernel_hc(bool* hc)
{
	*hc = true;
}


bool healthCheck()
{
	try
	{
		bool* hc = new bool;
		*hc = false;

		bool* device_hc;

		cudaMalloc((void**)&device_hc, sizeof(bool));
		cudaMemcpy(device_hc, &hc, sizeof(bool), cudaMemcpyHostToDevice);


		kernel_hc << <1, 1 >> > (device_hc);
		cudaMemcpy(hc, device_hc, sizeof(bool), cudaMemcpyDeviceToHost);
		cudaFree(device_hc);
		return *hc;
	}
	catch (const std::exception&)
	{
		return false;
	}
	

	
}


