#include "PerlinNoise.h"


#include <random>

PerlinNoise::PerlinNoise()
{
	for (int i = 0; i < VECTOR_ARRAY_SIZE; i++)
	{
		vectorArray[i] = KTools::Vector3<float>::RandomUnitVector();
	}
}

PerlinNoise::~PerlinNoise()
{
}

float* PerlinNoise::GenerateNoise(int width)
{
	float* outNoise = new float[width * width];
	int grid_size = width;
	float cell_size = (float)(grid_size / GRID_WIDTH);


	int gridWidth = 16;
	int vectorIndexArray[GRID_WIDTH * GRID_WIDTH];

	for (int j = 0; j < gridWidth; j++)
	{
		for (int i = 0; i < gridWidth; i++)
		{
			vectorIndexArray[i] = rand() % VECTOR_ARRAY_SIZE;
		}
	}

	int cornerX = 0;
	int cornerY = 0;




	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < width; i++)
		{

			for (int c = 0; c < 4; c++)
			{
				if (c == 0) //top left
				{
					cornerX = int(i / cell_size);
					cornerY = int(j / cell_size);
				}
				else if (c == 1) //top right
				{
					cornerX = int((i / cell_size) + 1);
					cornerY = int(j / cell_size);
				}
				else if (c == 2) //bottom left
				{
					cornerX = int(i / cell_size);
					cornerY = int((j / cell_size) + 1);
				}
				else if (c == 3) //bottom right
				{
					cornerX = int((i / cell_size) + 1);
					cornerY = int((j / cell_size) + 1);
				}

			outNoise[j * width + i] = float(rand()) / RAND_MAX;
		}
	}

	return outNoise;
}
