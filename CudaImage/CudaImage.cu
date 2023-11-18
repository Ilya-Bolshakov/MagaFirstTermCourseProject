#include "CudaImage.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../MagaFirstTermCourseProject.FormsApp/ClusteredImage.h"

using namespace CommonTypes;




__global__ void kmeans_kernel(float* d_data, float* d_centroids, int* d_labels, int k, int num_pixels, int num_channels) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < num_pixels) {
		float min_dist = INFINITY;
		int label = 0;

		for (int i = 0; i < k; i++) {
			float dist = 0.0f;
			/*for (int j = 0; j < num_channels; j++) {
				float diff = d_data[idx * num_channels + j] - d_centroids[i * num_channels + j];
				dist += diff * diff;
			}*/

			double dist = distance(pixels[i], centroids[j]);

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
	std::vector<Pixel> centroids(k);
	for (int i = 0; i < k; i++) {
		centroids[i] = pixels[rand() % pixels.size()];
	}


	ClusteredImage c;

	Pixel p;

	p.b = 5;
	p.r = 10;
	p.g = 50;

	c.centroids.push_back(p);

	//unsigned* dev_srcImage;
	//size_t size = sizeof(unsigned) * width * height;
	//if (cudaMalloc((void**)&dev_srcImage, size) !=
	//	cudaError::cudaSuccess) return c;
	//if (cudaMemcpy(dev_srcImage, srcImage, size,
	//	cudaMemcpyHostToDevice) != cudaError::cudaSuccess)
	//	return c;
	//// ћаксимальное количество нитей на блок может
	//	dim3 threads(128, 128);
	//dim3 blocks((width + threads.x - 1) / threads.x,
	//	(height + threads.y - 1) / threads.y);
	//kernel << <threads, blocks >> > (dev_srcImage, width,
	//	height);
	//cudaError error = cudaMemcpy(srcImage, dev_srcImage,
	//	size,
	//	cudaMemcpyDeviceToHost);
	//if (error != cudaError::cudaSuccess) return c;
	//cudaFree(dev_srcImage);




	return c;
}