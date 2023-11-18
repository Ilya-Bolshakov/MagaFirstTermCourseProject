#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>
#include "KMeansSequential.h"
#include "KMeansOpenMP.h"


using namespace CommonTypes;
using namespace KMeansSequential;
using namespace KMeansOpenMP;


ref class Method
{
public: String^ name;


		 Method()
		 {
			 this->name = "";
		 }


public: virtual ClusteredImage KMeans(std::vector<Pixel>& pixels, int k) = 0;  
};


ref class SequenceMethod : public Method
{

public: SequenceMethod()
{
	this->name = "ѕоследовательный метод";
}
public: ClusteredImage KMeans(std::vector<Pixel>& pixels, int k) override
{
	return kMeansClustering(pixels, k);
}
};


ref class OpenMPMethod : public Method
{

public: OpenMPMethod()
{
	this->name = "OpenMP метод";
}
public: ClusteredImage KMeans(std::vector<Pixel>& pixels, int k) override
{
	auto worker = gcnew ImageHelper();
	return worker->kMeansClustering(pixels, k);
}
};

ref class CudaMethod : public Method
{

public: CudaMethod()
{
	this->name = "Cuda метод";
}
public: ClusteredImage KMeans(std::vector<Pixel>& pixels, int k) override
{
	ClusteredImage c;
	return  c;
}
};




ref class MethodSimpleFactory 
{
public: Method^ GetMethod(int type)
{
	switch (type)
	{
	case 0: return gcnew SequenceMethod();
	case 1: return gcnew OpenMPMethod();
	default:
		break;
	}
}
};