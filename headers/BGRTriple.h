 #ifndef BGRStruct
 #define BGRStruct
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
typedef struct tagBitmapFileHeader
{
    uint32_t    bfSize;        // File size in bytes (2-5 bytes)
    uint16_t    bfReserved1;   // Reserved, must be set to 0 (6-7 bytes)
    uint16_t    bfReserved2;   // Reserved, must be set to 0 (8-9 bytes)
    uint32_t    bfOffBits;     // Offset from file header to pixel data (10-13 bytes)
} BITMAPFILEHEADER;

typedef struct tagBitmapInfoHeager
{
    uint32_t        biSize;          // The size of this structure (14-17 bytes)
    uint32_t        biWidth;         // The width of the image (18-21 bytes)
    uint32_t        biHeight;        // The height of the image (22-25 bytes)
    uint16_t        biPlanes;        // Indicates the plane attribute of the bmp picture, obviously the display has only one plane, so it is always equal to 1 (26-27 bytes)
    uint16_t        biBitCount;      // The number of bits occupied by a pixel, generally 24 (28-29 bytes)
    uint32_t        biCompression;   // Describe the type of image data compression, 0 means no compression. (30-33 bytes)
    uint32_t        biSizeImage;     // The size of pixel data, this value should be equal to bfSize-bfOffBits (34-37 bytes) in the file header structure above
    uint32_t        biXPelsPerMeter; // Describe the horizontal resolution, expressed in pixels/meter. Generally 0 (38-41 bytes)
    uint32_t        biYPelsPerMeter; // Describe the vertical resolution, expressed in pixels/meter. Generally 0 (42-45 bytes)
    uint32_t        biClrUsed;       // Describe the number of color indexes in the color table actually used by the bitmap (if set to 0, all palette items are used). (46-49 bytes)
    uint32_t        biClrImportant;  // Explain the number of color indexes that have an important influence on the image display. If it is 0, it means all are important. (50-53 bytes)
} BITMAPINFOHEADER;

typedef struct tagBGRTriple
{
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
} BGRTriple;

#endif