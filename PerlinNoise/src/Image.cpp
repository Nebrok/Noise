#include "Image.h"

#include <fstream>
#include <stdexcept>



Image::Image(int width, int height, ImageType imageType, PixelFormat format)
	: Width(width), Height(height), Type(imageType), Format(format)
{
	switch (Format)
	{
	case PixelFormat::R8_8: 
		_count = Width * Height;
		_size = _count * sizeof(float);
		_data = new float[_count];
		break;
	case PixelFormat::R8G8B8_24:
		_count = Width * Height * 3;
		_size = _count * sizeof(float);
		_data = new float[_count];
		break;
	case PixelFormat::R8G8B8A8_32:
		_count = Width * Height * 4;
		_size = _count * sizeof(float);
		_data = new float[_count];
		break;
	default:
		throw std::runtime_error("Invalid PíxelFormat entered");
		return;
	}
	std::fill(_data, _data + _count, 0.0f);
}

Image::~Image()
{
	delete(_data);
}

//So much can go wrong here but for the time being...
void Image::CopyBuffer(float* inBuffer)
{
	std::copy(inBuffer, inBuffer + _count, _data);
}

void Image::SaveImage(std::string fileName, std::filesystem::path filepath)
{
	std::fstream f(filepath.string() + fileName, std::fstream::out);
	
	switch (Type)
	{
	case ImageType::PPM:
		SavePPMImage(f);
		break;
	default:
		throw std::runtime_error("Trying to save unsupported image type");
		break;
	}
}

void Image::SavePPMImage(std::fstream& file)
{
	file << "P3\n" << Width << ' ' << Height << "\n255\n";
	switch (Format)
	{
	case PixelFormat::R8_8:
		for (int j = 0; j < Height; j++)
		{
			for (int i = 0; i < Width; i++)
			{
				file << _data[j * Height + i] * 255 << ' ' << _data[j * Height + i] * 255 << ' ' << _data[j * Height + i] * 255 << '\n';
			}
		}

		break;
	default:
		throw std::runtime_error("Trying to save PPM image with unsupported pixel format");
		break;
	}

}
