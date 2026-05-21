// PerlinNoise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>

#include "Image.h"
#include "PerlinNoise.h"

int main()
{
    std::cout << "Hello World!\n";

    int squareSize = 256;

    Image testImage(squareSize, squareSize, ImageType::PPM, PixelFormat::R8_8);
    testImage.CopyBuffer(PerlinNoise::GenerateNoise(squareSize, squareSize));
    testImage.SaveImage("testImage.ppm", std::filesystem::path(std::filesystem::current_path().string() + "/Images/"));

}