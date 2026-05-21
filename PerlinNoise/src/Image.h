#pragma once
#include <string>
#include <filesystem>


enum class ImageType
{
	NONE = 0,
	PPM = 1,
	PNG = 2,
	JPEG = 3
};

enum class PixelFormat
{
	NONE = 0,
	R8_8 = 1,
	R8G8B8_24 = 2,
	R8G8B8A8_32 = 3
};


class Image
{
public:
	int Width = 0;
	int Height = 0;

	ImageType Type;
	PixelFormat Format;

private:
	int _count = 0;
	int _size = 0;

	float* _data;


public: 
	Image(int width, int height, ImageType imageType, PixelFormat format);
	~Image();

	void CopyBuffer(float* inBuffer);

	void SaveImage(std::string fileName, std::filesystem::path filepath);
	void SavePPMImage(std::fstream& file);

private:


};