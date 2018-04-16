#pragma once
#include <iostream>
#include "Color.h"

class Bitmap
{
private:
	const char* _filename;
	// Data read from the header of the BMP file
	unsigned char _header[54];			// Each BMP file begins by a 54-bytes header
	unsigned int _dataPos;				// Position in the file where the actual data begins

	//Dimensions
	unsigned int _width;
	unsigned int _height;

	//Data
	int _stride;
	unsigned int _bitsPerPixel;
	unsigned int _pixelArrayImageSize;	// = width*height*3
	unsigned char* _pixelData;			// Actual RGB data

	Bitmap(const Bitmap &bitmap);
public:
	Bitmap(const char * filename);
	//Bitmap(Bitmap* bitmap);
	~Bitmap();

	//gets
	unsigned int GetWidth() { return _width; }
	unsigned int GetHeight() { return _height; }
	unsigned char* GetPixelData() { return _pixelData; }
	unsigned int GetPixelArraySize() { return _pixelArrayImageSize; }
	unsigned int GetStride() { return _stride; }

	//functions
	void SetPixelData(unsigned char* data)
	{
		memcpy_s(this->_pixelData, this->_pixelArrayImageSize, data, this->_pixelArrayImageSize);
	}
	// Gets the color of the specified pixel in this Bitmap.
	Color GetPixel(int x, int y);
	void SetPixel(int x, int y, Color color);
	void SetPixel(int x, int y, int R, int G, int B);
	// Saves this Bitmap to the specified file image.
	void Save(const char * imagepath);
	Bitmap* Clone();
};
