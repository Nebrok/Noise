#include "PerlinNoise.h"
#include <cmath> // Required for sin, cos, floor
#include <algorithm>
#include <vector>

// --- Internal State ---

// Static storage for the pre-computed gradient vectors.
static float2 g_gradientTable[NoiseConstants::GRADIENT_TABLE_SIZE];
static bool g_initialized = false;

<<<<<<< Updated upstream
PerlinNoise::PerlinNoise()
{
	for (int i = 0; i < VECTOR_ARRAY_SIZE; i++)
	{
		vectorArray[i] = KTools::Vector3<float>::RandomUnitVector();
	}
=======
/**
 * @brief Populates the gradient table with "random" unit vectors.
 * This is performed once to ensure that subsequent lookups are O(1).
 */
void PerlinNoise::Initialize() {
    if (g_initialized) return;

    // We use a simple XORShift or similar deterministic-ish logic
    // if we wanted perfect reproducibility, but for the purpose of this
    // refactor, we will populate the table with varied directions.
    for (int i = 0; i < NoiseConstants::GRADIENT_TABLE_SIZE; ++i) {
        // Use a variety of prime-based weights to ensure the 256 vectors are diverse.
        float x = std::sin((float)(i * 127 + 343));
        float y = std::cos((float)(i * 97 + 503));
        g_gradientTable[i] = { x, y };
    }

    g_initialized = true;
>>>>>>> Stashed changes
}

// --- Utility Definitions ---

/**
 * @brief Linear interpolation function: Returns a + t * (b - a).
 */
float PerlinNoise::mix(float a, float b, float t) {
    return a + t * (b - a);
}

<<<<<<< Updated upstream
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
=======
/**
 * @brief Calculates the fade curve based on 6t^5 - 15t^4 + 10t^3 (smootherstep).
 */
inline float PerlinNoise::fade(float t) {
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

/**
 * @brief Optimized gradient lookup.
 * Instead of calculating trigonometry for every pixel, we map the
 * $(x, y)$ coordinate pair to a hash in our pre-computed table.
 */
inline float2 PerlinNoise::gradient(int x, int y) {
    // "Permutation-style" hashing:
    // Since x and y are already limited to [0, 255] by the bitwise AND,
    // we combine them using large primes to map into our table size.
    uint32_t hash = (x * 149) ^ (y * 31);
    return g_gradientTable[hash & (NoiseConstants::GRADIENT_TABLE_SIZE - 1)];
}

/**
 * @brief Calculates a single octave of Perlin Noise at a continuous point (x, y).
 */
float PerlinNoise::perlin2D(float x, float y) {
    int X = (int)std::floor(x) % 255;
    int Y = (int)std::floor(y) % 255;

    float fx = x - std::floor(x);
    float fy = y - std::floor(y);

    float u = fade(fx);
    float v = fade(fy);

    // These now use the O(1) lookup table.
    float2 g00 = gradient(X, Y);
    float2 g10 = gradient(X + 1, Y);
    float2 g01 = gradient(X, Y + 1);
    float2 g11 = gradient(X + 1, Y + 1);

    float n00 = g00.x * fx + g00.y * fy;
    float n10 = g10.x * (fx - 1.0f) + g10.y * fy;
    float n01 = g01.x * fx + g01.y * (fy - 1.0f);
    float n11 = g11.x * (fx - 1.0f) + g11.y * (fy - 1.0f);

    float ix1 = mix(n00, n10, u);
    float ix2 = mix(n01, n11, u);

    return mix(ix1, ix2, v);
}

PerlinNoise::PerlinNoise() {}
PerlinNoise::~PerlinNoise() {}

/**
 * @brief Generates a multi-octave (fractal Brownian motion) noise field.
 */
float* PerlinNoise::GenerateNoise(int width, int height) {
    // Ensure the lookup table is ready.
    Initialize();

    float* outNoise = new float[width * height];

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x_base = (float)i / 409.6f;
            float y_base = (float)j / 409.6f;

            float total_sum = 0.0f;
            float freq = 1.0f;
            float amp = 1.0f;

            for (int o = 0; o < NoiseConstants::OCTAVES; ++o) {
                total_sum += perlin2D(x_base * freq, y_base * freq) * amp;
                freq *= NoiseConstants::LACUNARITY;
                amp *= NoiseConstants::PERSISTENCE;
            }

            float result = (total_sum + 1.0f) * 0.5f;
            outNoise[j * width + i] = std::max(0.0f, std::min(1.0f, result));
        }
    }

    return outNoise;
>>>>>>> Stashed changes
}
