//
// Created by pedruino on 5/1/18.
//

#include <cstring>
#include <cmath>
#include "Filter.h"
#include "Bitmap.h"
#include "Kernels.h"

Filter::Filter() {}
Filter::~Filter() {}

void Filter::Negative(Bitmap &image)
{
    unsigned int width = image.GetWidth();
    unsigned int height = image.GetHeight();

    int x, y;
#pragma omp parallel for schedule(dynamic) private(x, y)
    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            Color color = image.GetPixel(x, y);
            unsigned char r, g, b;

            r = 255 - color.red();
            g = 255 - color.green();
            b = 255 - color.blue();

            image.SetPixel(x, y, Color(r, g, b));
        }
    }
}

void Filter::Grayscale(Bitmap &image)
{
    unsigned int width = image.GetWidth();
    unsigned int height = image.GetHeight();

    int x, y;
    #pragma omp parallel
    {
    #pragma omp for schedule(dynamic) private(x, y)
        for (x = 0; x < width; x++)
        {
            for (y = 0; y < height; y++)
            {
                Color color = image.GetPixel(x, y);

                unsigned char grayed = 0;
                grayed += color.red() * 0.114;
                grayed += color.green() * 0.587;
                grayed += color.blue() * 0.299;

                image.SetPixel(x, y, Color(grayed, grayed, grayed));
            }
        }
    }
}

void ConvolutionFilter(Bitmap &sourceImage, const double xkernel[][3], const double ykernel[][3], double factor, int bias, bool grayscale)
{
    // Image dimensions stored in variables for convenience
    int width = sourceImage.GetWidth();
    int height = sourceImage.GetHeight();

    // Lock source image bits into system memory
    //unsigned char* srcData = sourceImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

    // Get the total number of bytes in your image - 32 bytes per pixel x image width x image height -> for 32bpp images
    int srcDataStride = sourceImage.GetStride();
    int bytes = srcDataStride * sourceImage.GetHeight();

    // Create byte arrays to hold pixel information of your image
    unsigned char* pixelBuffer = new unsigned char[bytes];
    unsigned char* resultBuffer = new unsigned char[bytes];

    memcpy(pixelBuffer, sourceImage.GetPixelData(), bytes);
    int stepBytes = 3;

    //Convert your image to grayscale if necessary
    if (grayscale == true)
    {
        float rgb = 0;
        for (int i = 0; i < sourceImage.GetPixelArraySize(); i += stepBytes)
        {
            rgb = pixelBuffer[i] * .21f;
            rgb += pixelBuffer[i + 1] * .71f;
            rgb += pixelBuffer[i + 2] * .071f;
            pixelBuffer[i] = rgb;
            pixelBuffer[i + 1] = pixelBuffer[i];
            pixelBuffer[i + 2] = pixelBuffer[i];
        }
    }

    //Create variable for pixel data for each kernel
    double xr = 0.0;
    double xg = 0.0;
    double xb = 0.0;
    double yr = 0.0;
    double yg = 0.0;
    double yb = 0.0;
    double rt = 0.0;
    double gt = 0.0;
    double bt = 0.0;

    //This is how much your center pixel is offset from the border of your kernel
    //Sobel is 3x3, so center is 1 pixel from the kernel border
    int filterOffset = 1;
    int calcOffset = 0;
    int byteOffset = 0;

    //Start with the pixel that is offset 1 from top and 1 from the left side
    //this is so entire kernel is on your image
    int OffsetY, OffsetX;

    for (OffsetY = filterOffset; OffsetY < height - filterOffset; OffsetY++)
    {
        for (OffsetX = filterOffset; OffsetX < width - filterOffset; OffsetX++)
        {
            //reset rgb values to 0
            xr = xg = xb = yr = yg = yb = 0;
            rt = gt = bt = 0.0;

            //position of the kernel center pixel
            byteOffset = OffsetY * srcDataStride + OffsetX * stepBytes;

            //kernel calculations
            for (int filterY = -filterOffset; filterY <= filterOffset; filterY++)
            {
                for (int filterX = -filterOffset; filterX <= filterOffset; filterX++)
                {
                    calcOffset = byteOffset + filterX * 4 + filterY * srcDataStride;

                    xb += (double)(pixelBuffer[calcOffset])     * xkernel[filterY + filterOffset][filterX + filterOffset];
                    xg += (double)(pixelBuffer[calcOffset + 1]) * xkernel[filterY + filterOffset][filterX + filterOffset];
                    xr += (double)(pixelBuffer[calcOffset + 2]) * xkernel[filterY + filterOffset][filterX + filterOffset];

                    yb += (double)(pixelBuffer[calcOffset])     * ykernel[filterY + filterOffset][filterX + filterOffset];
                    yg += (double)(pixelBuffer[calcOffset + 1]) * ykernel[filterY + filterOffset][filterX + filterOffset];
                    yr += (double)(pixelBuffer[calcOffset + 2]) * ykernel[filterY + filterOffset][filterX + filterOffset];
                }
            }

            //total rgb values for this pixel
            bt = sqrt((xb * xb) + (yb * yb));
            gt = sqrt((xg * xg) + (yg * yg));
            rt = sqrt((xr * xr) + (yr * yr));

            //set limits, bytes can hold values from 0 up to 255;
            if (bt > 255) bt = 255;
            else if (bt < 0) bt = 0;
            if (gt > 255) gt = 255;
            else if (gt < 0) gt = 0;
            if (rt > 255) rt = 255;
            else if (rt < 0) rt = 0;

            //set new data in the other byte array for your image data
            resultBuffer[byteOffset] = (bt);
            resultBuffer[byteOffset + 1] = (gt);
            resultBuffer[byteOffset + 2] = (rt);
        }
    }
    sourceImage.SetPixelData(resultBuffer);
}

void ConvolutionFilter(Bitmap &sourceImage, const double filterMatrix[][5], double factor, int bias, bool grayscale)
{
    // Image dimensions stored in variables for convenience
    int width = sourceImage.GetWidth();
    int height = sourceImage.GetHeight();

    // Get the total number of bytes in your image - 24 bytes per pixel x image width x image height -> for 24bpp images
    int srcDataStride = sourceImage.GetStride();
    int bytes = srcDataStride * sourceImage.GetHeight();

    // Create byte arrays to hold pixel information of your image
    unsigned char* pixelBuffer = new unsigned char[bytes];
    unsigned char* resultBuffer = new unsigned char[bytes];

    std::memcpy(pixelBuffer, sourceImage.GetPixelData(), bytes);
    int stepBytes = 3;

    //Convert your image to grayscale if necessary
    if (grayscale == true)
    {
        float rgb = 0;
        for (int i = 0; i < sourceImage.GetPixelArraySize(); i += stepBytes)
        {
            rgb = pixelBuffer[i] * .21f;
            rgb += pixelBuffer[i + 1] * .71f;
            rgb += pixelBuffer[i + 2] * .071f;
            pixelBuffer[i] = rgb;
            pixelBuffer[i + 1] = pixelBuffer[i];
            pixelBuffer[i + 2] = pixelBuffer[i];
        }
    }

    double red, green, blue;

    int filterWidth = 5;
    int filterHeight = 5;

    int filterOffset = (filterWidth - 1) / 2;
    int calcOffset = 0;

    int byteOffset = 0;

    for (int offsetY = filterOffset; offsetY < height - filterOffset; offsetY++)
    {
        for (int offsetX = filterOffset; offsetX < width - filterOffset; offsetX++)
        {
            blue = 0;
            green = 0;
            red = 0;

            byteOffset = offsetY * srcDataStride + offsetX * stepBytes;

            for (int filterY = -filterOffset; filterY <= filterOffset; filterY++)
            {
                for (int filterX = -filterOffset; filterX <= filterOffset; filterX++)
                {
                    calcOffset = byteOffset + (filterX * 4) + (filterY * srcDataStride);

                    blue += (double)(pixelBuffer[calcOffset]) * filterMatrix[filterY + filterOffset][filterX + filterOffset];
                    green += (double)(pixelBuffer[calcOffset + 1]) * filterMatrix[filterY + filterOffset][filterX + filterOffset];
                    red += (double)(pixelBuffer[calcOffset + 2]) * filterMatrix[filterY + filterOffset][filterX + filterOffset];
                }
            }

            blue = factor * blue + bias;
            green = factor * green + bias;
            red = factor * red + bias;

            // Make SURE rgb is in range
            if (blue > 255) blue = 255;
            else if (blue < 0) blue = 0;

            if (green > 255) green = 255;
            else if (green < 0) green = 0;

            if (red > 255) red = 255;
            else if (red < 0) red = 0;

            resultBuffer[byteOffset] = (blue);
            resultBuffer[byteOffset + 1] = (green);
            resultBuffer[byteOffset + 2] = (red);
        }
    }

    sourceImage.SetPixelData(resultBuffer);
}

void Filter::Blur(Bitmap & image)
{
    // Gaussian blur 5x5
    ConvolutionFilter(image, gaussian5x5, 1 / 256.f, 0, false);
}

void Filter::Convolve(Bitmap & image, const double xkernel[][3], const double ykernel[][3], double factor, int bias, bool grayscale)
{
    ConvolutionFilter(image, xkernel, ykernel, 1, 0, grayscale);
}

void Filter::Convolve(Bitmap & image, const double kernel[][5], double factor, int bias, bool grayscale)
{
    ConvolutionFilter(image, kernel, factor, bias, grayscale);
}