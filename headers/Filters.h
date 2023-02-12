#ifndef Filters
#define Filters
#include "BGRTriple.h"

void grayFilter(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader);

BGRTriple **SobelFilter(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, uint8_t mode);
    void SobelFilterX(BGRTriple **bgrSobel, BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader);
    void SobelFilterY(BGRTriple **bgrSobel, BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader);
    void SobelFilterXY(BGRTriple **bgrSobel, BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader);

BGRTriple **GaussBlur(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, uint8_t coreSize, double sigma);
    void CoreGauss(double **coreGauss, double sigma, uint8_t coreSize);
    int **FillPixelCoreB(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, int **pixelCore, uint8_t sizeCore, unsigned int i, unsigned int j);
    int GetGaussPixelB(BGRTriple **bgr, BITMAPINFOHEADER infoheader, double **coreGauss, uint8_t sizeCore, unsigned int i, unsigned int j);
    int **MultiplicateCores(int **pixelCore, double **coreGauss, uint8_t coreSize);
    int GetCorePixel(int **pixelCore, uint8_t coreSize);

BGRTriple **MedianFilter(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, uint8_t coreSize);
    int **ShakeCore(int **pixelCore, uint8_t coreSize);

BGRTriple** OtsuThreshold(BGRTriple** bgr, BITMAPINFOHEADER bitmapInfoHeader);

#endif