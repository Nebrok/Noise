#pragma once
#include "vec3.h"

// Constants for Fractal Brownian Motion (fBm)
namespace NoiseConstants {
    const int OCTAVES = 10;
    const float PERSISTENCE = 0.4f;
    const float LACUNARITY = 2.3f;

    // Size of the pre-calculated gradient look-up table.
    const int GRADIENT_TABLE_SIZE = 256;
}

// Utility structure to represent a 2D vector used for gradient calculations
struct float2 {
    float x, y;
};

class PerlinNoise
{
public:
    PerlinNoise();
    ~PerlinNoise();

    /**
     * @brief Generates a raw array of multi-octave (fractal Brownian motion)
     * noise values for the given dimensions.
     * The result is normalized to [0, 1].
     * The returned pointer must be freed by the caller using delete[].
     */
    static float* GenerateNoise(int Width, int Height);

private:
    // --- Math Helpers (Declared and Defined in Header for Single Definition Point) ---
    friend struct float2;

    // 1. Initialization of the Gradient Table.
    static void Initialize();

    // 2. Interpolation Mix function: Calculates a linear interpolation between 'a' and 'b' using factor 't'.
    static inline float mix(float a, float b, float t);

    // 3. Fade curve helper: The smootherstep function (6t^5 - 15t^4 + 10t^3).
    static inline float fade(float t);

    // 4. Gradient vector lookup. Uses a hash of $(x, y)$ to sample from the pre-computed table.
    static inline float2 gradient(int x, int y);

    // 5. Core Perlin Noise function: Calculates a single octave of noise at (x, y).
    // Returns a value in the range [-1, 1].
    static float perlin2D(float x, float y);
};
