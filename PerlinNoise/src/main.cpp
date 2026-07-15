// PerlinNoise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>

#include "Image.h"
#include "PerlinNoise.h"

int main()
{
    
    int squareSize = 2048;
    
    Image testImage(squareSize, squareSize, ImageType::PPM, PixelFormat::R8_8);
    testImage.CopyBuffer(PerlinNoise::GenerateNoise(squareSize, squareSize));
    std::cout << std::filesystem::current_path().string().c_str() << '\n';
    testImage.SaveImage("testImage.ppm", std::filesystem::path(std::filesystem::current_path().string() + "/PerlinNoise/Images/"));

}