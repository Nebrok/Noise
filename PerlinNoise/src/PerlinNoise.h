#pragma once
#include "vec3.h"



class PerlinNoise
{
public:
	const static size_t VECTOR_ARRAY_SIZE = 64;
	const static size_t GRID_WIDTH = 16;

private:
	KTools::Vector3<float> vectorArray[64];

public:
	PerlinNoise();
	~PerlinNoise();

	static float* GenerateNoise(int Width, int Height);


private:

};