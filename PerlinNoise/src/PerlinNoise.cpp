#include "PerlinNoise.h"


#include <random>

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::~PerlinNoise()
{
}

float* PerlinNoise::GenerateNoise(int width, int height)
{
	float* outNoise = new float[width * height];

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			outNoise[j * height + i] = float(rand()) / RAND_MAX;
		}
	}

	return outNoise;
}
