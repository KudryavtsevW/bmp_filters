 #ifndef ReadWritebmp
 #define ReadWritebmp

 #include "BGRTriple.h"

BGRTriple** readBmp(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, int in, uint8_t padding);
void saveBmp(int out, uint16_t signature, BITMAPFILEHEADER bitmapFileHeadr, BITMAPINFOHEADER bitmapInfoHeader, BGRTriple **bgr, uint8_t padding);
void showInf(BITMAPFILEHEADER bitmapFileHeader, BITMAPINFOHEADER bitmapInfoHeader);
 #endif