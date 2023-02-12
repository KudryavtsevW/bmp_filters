#include "../headers/ReadWriteBmp.h"
BGRTriple** readBmp(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, int in, uint8_t padding)
{
    unsigned int i, j;
    char c;    
     for (i = 0; i < bitmapInfoHeader.biHeight; i++)
    {
        for (j = 0; j < bitmapInfoHeader.biWidth; j++)
        {
            read(in, &bgr[i][j], sizeof(BGRTriple));
        }
        for (uint8_t p = 0; p < padding; p++)
        {
            read(in, &c, sizeof(uint8_t));
        }
    }
    return bgr;
}

void saveBmp(int out, uint16_t signature, BITMAPFILEHEADER bitmapFileHeadr, BITMAPINFOHEADER bitmapInfoHeader, BGRTriple **bgr, uint8_t padding)
{
    unsigned int i,j;
    write(out, &signature, sizeof(signature));
    write(out, &bitmapFileHeadr, sizeof(bitmapFileHeadr));
    write(out, &bitmapInfoHeader, sizeof(bitmapInfoHeader));
    for (i = 0; i < bitmapInfoHeader.biHeight; i++)
    {
        for (j = 0; j < bitmapInfoHeader.biWidth; j++)
        {
            write(out, &bgr[i][j], sizeof(BGRTriple));
        }
        for (uint8_t p = 0; p < padding; p++)
        {
            write(out, "0", sizeof(uint8_t));
        }
    }
}

void showInf(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader)
{
    printf("Size = %x", bitmapFileHeader.bfSize);
    printf("\t %d bytes\n", bitmapFileHeader.bfSize);
    printf("Reserved words must be 0: %d\n", bitmapFileHeader.bfReserved1);
    printf("Reserved words must be 0: %d\n", bitmapFileHeader.bfReserved2);
    printf("Offset bytes of actual bitmap data: %d\n", bitmapFileHeader.bfOffBits);
    printf("Bitmap Information Header:\n");
    printf("The size of the message header: %d bytes\n", bitmapInfoHeader.biSize);
    printf("Bitmap width: %d\n", bitmapInfoHeader.biWidth);
    printf("Bitmap height: %d\n", bitmapInfoHeader.biHeight);
    printf("The number of planes of the image (the number of planes is the number of palettes, the default is 1 palette): %d\n", bitmapInfoHeader.biPlanes);
    printf("Number of bits per pixel: %d\n", bitmapInfoHeader.biBitCount);
    printf("Compression method:%d\n", bitmapInfoHeader.biCompression);
    printf("Image size: %d\n", bitmapInfoHeader.biSizeImage);
    printf("Horizontal resolution: %d\n", bitmapInfoHeader.biXPelsPerMeter);
    printf("Vertical resolution: %d\n", bitmapInfoHeader.biYPelsPerMeter);
    printf("Number of colors used: %d\n", bitmapInfoHeader.biClrUsed);
    printf("Number of important colors: %d\n", bitmapInfoHeader.biClrImportant);
}

 