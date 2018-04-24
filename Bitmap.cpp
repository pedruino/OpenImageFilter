#include "Bitmap.h"

Bitmap::Bitmap(const char* filename)
{
	this->_filename = filename;
	// Open the file
	FILE * file;
	fopen_s(&file, filename, "rb");

	if (!file)
		printf("Image could not be opened\n");

	if (fread(this->_header, 1, 54, file) != 54) // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");

	if (this->_header[0] != 'B' || this->_header[1] != 'M')
		printf("Not a correct BMP file\n");

	this->_bitsPerPixel = this->_header[0x1C];
	if (_bitsPerPixel != 24)
		printf("This program is for 24bpp files. Your bmp is not that\n");

	// Read ints from the byte array
	this->_dataPos = *(int*)&(this->_header[0x0A]);
	this->_pixelArrayImageSize = *(int*)&(this->_header[0x22]);
	this->_width = *(int*)&(this->_header[0x12]);
	this->_height = *(int*)&(this->_header[0x16]);

	// width = width in pixels
	// bpp = BITS per pixel.  Ex:  bpp=24 would be 3 bytes per pixel
	this->_stride = this->_width * _bitsPerPixel;	// bits per row
	this->_stride += 31;							// round up to next 32-bit boundary
	this->_stride /= 32;							// DWORDs per row
	this->_stride *= 4;							// bytes per row

	// Some BMP files are misformatted, guess missing information
	if (this->_pixelArrayImageSize == 0)
	{
		//this->_pixelArrayImageSize = this->_width * this->_height * 3; // 3 : one byte for each Red, Green and Blue component //simple
		this->_pixelArrayImageSize = this->_stride * this->_height;
	}

	if (this->_dataPos == 0)
		this->_dataPos = 54; // The BMP header is done that way

	// Create a buffer
	_pixelData = new unsigned char[this->_pixelArrayImageSize];

	// Read the actual data from the file into the buffer
	fread(this->_pixelData, 1, this->_pixelArrayImageSize, file);

	// Everything is in memory now, the file can be closed
	fclose(file);
}

Bitmap::Bitmap(const Bitmap &self)
{
	this->_filename = self._filename;
	memcpy_s(this->_header, sizeof(this->_header), self._header, sizeof(self._header));

	this->_dataPos = self._dataPos;

	this->_width = self._width;
	this->_height = self._height;

	this->_stride = self._stride;
	this->_bitsPerPixel = self._bitsPerPixel;
	this->_pixelArrayImageSize = self._pixelArrayImageSize;

	this->_pixelData = new unsigned char[this->_pixelArrayImageSize];
	memcpy_s(this->_pixelData, this->_pixelArrayImageSize, self._pixelData, this->_pixelArrayImageSize);
}

Bitmap* Bitmap::Clone()
{
	Bitmap* teste = new Bitmap(*this);
	return teste;
}

Bitmap::~Bitmap()
{
	delete[] this->_pixelData;
}

// Output in RGB color
Color Bitmap::GetPixel(int x, int y)
{
	if (x < this->_width && y < this->_height)
	{
		y = this->_height - 1 - y;	//to flip things
		// std::cout << "y: " << y << " x: " << x << "\n";

		unsigned int pixel = this->_stride*y + 3 * x;

		unsigned char red = (this->_pixelData[pixel + 2]);		//[R]ed
		unsigned char green = (this->_pixelData[pixel + 1]);		//[G]reed
		unsigned char blue = (this->_pixelData[pixel + 0]);		//[B]lue

		return Color(red, green, blue);
	}
	else { std::cerr << "BAD INDEX\n"; std::cerr << "X: " << x << " Y: " << y << "\n"; }
}

void Bitmap::SetPixel(int x, int y, Color color)
{
	SetPixel(x, y, color.red(), color.green(), color.blue());
}

void Bitmap::SetPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
	if (x < this->_width && y < this->_height)
	{
		y = this->_height - 1 - y;	//to flip things
									// std::cout << "y: " << y << " x: " << x << "\n";

		unsigned int pixel = this->_stride*y + 3 * x;

		this->_pixelData[pixel + 2] = red;		//[R]ed
		this->_pixelData[pixel + 1] = green;	//[G]reed
		this->_pixelData[pixel + 0] = blue;		//[B]lue
	}
	else { std::cerr << "BAD INDEX\n"; std::cerr << "X: " << x << " Y: " << y << "\n"; }
}

// Write the bitmap object to file
void Bitmap::Save(const char* filename)
{
	//int realwidth = 3 * this->_width + (4 - ((3 * this->_width) % 4)) % 4; TODO: delete
	int volume = this->_height * this->_stride;

	FILE* w;
	fopen_s(&w, filename, "wb");
	fwrite(this->_header, sizeof(unsigned char), 54, w);
	fwrite(this->_pixelData, sizeof(unsigned char), volume, w);
	fclose(w);
}