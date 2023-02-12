#include "../headers/Filters.h"
void grayFilter(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader)
{
    uint8_t result = 0;
    for (uint32_t k = 0; k < bitmapInfoHeader.biHeight; k++)
    {
        for (uint32_t m = 0; m < bitmapInfoHeader.biWidth; m++)
        {
            result = 0;
            result += bgr[k][m].Blue * 0.114 + bgr[k][m].Green * 0.587 + bgr[k][m].Red * 0.299;          
            bgr[k][m].Blue = (uint8_t)result;
            bgr[k][m].Green = (uint8_t)result;
            bgr[k][m].Red = (uint8_t)result;
        }
    }
}