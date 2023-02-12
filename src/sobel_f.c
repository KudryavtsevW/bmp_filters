#include "../headers/Filters.h"
    const int GX[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	const int GY[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
    int sumX;
    int sumY;
    int sumXY;
    unsigned int i, j;
BGRTriple** SobelFilter(BGRTriple** bgr, BITMAPINFOHEADER bitmapInfoHeader, uint8_t mode)
{
    BGRTriple **bgrSobel = NULL;
    //create bgrSobel
    bgrSobel = (BGRTriple **)calloc(bitmapInfoHeader.biHeight, sizeof(BGRTriple *));
    if(bgrSobel == NULL)
        printf("calloc error Sobel\n");
    for(i = 0; i< bitmapInfoHeader.biHeight;i++)
    {
        bgrSobel[i] = (BGRTriple *)calloc(bitmapInfoHeader.biWidth, sizeof(BGRTriple));
    }

    switch (mode)
    {
    case 1:
        SobelFilterX(bgrSobel, bgr, bitmapInfoHeader);
        break;
    case 2:
        SobelFilterY(bgrSobel, bgr, bitmapInfoHeader);
        break;
    case 3:
        SobelFilterXY(bgrSobel, bgr, bitmapInfoHeader);
        break;    
    default:
        printf("not correct mode (sobel_f.c)\n");
        break;
    }

    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgrSobel[i][j] = bgr[i][j];
        }
    } 
    
    //delete    bgrSobel
    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        free(bgrSobel[i]);
    }
    free(bgrSobel);


    return bgr;
}

void SobelFilterX(BGRTriple **bgrSobel, BGRTriple **bgr,  BITMAPINFOHEADER bitmapInfoHeader)
{
    for (i = 1; i < bitmapInfoHeader.biHeight - 1; i++)
	{
		for (j = 1; j < bitmapInfoHeader.biWidth - 1; j++)
		{
			sumX = 0;
			sumX += bgr[i - 1][j - 1].Green * GX[0][0] +
				bgr[i - 1][j].Green * GX[0][1] +
				bgr[i - 1][j + 1].Green * GX[0][2] +

				bgr[i][j - 1].Green * GX[1][0] +
				bgr[i][j].Green * GX[1][1] +
				bgr[i][j + 1].Green * GX[1][2] +

				bgr[i + 1][j - 1].Green * GX[2][0] +
				bgr[i + 1][j].Green * GX[2][1] +
				bgr[i + 1][j + 1].Green * GX[2][2];


			if (sumX > 255)
			{
				sumX = 255;
			}
			if (sumX < 0)
			{
				sumX = 0;
			}
			bgrSobel[i][j].Blue = sumX;
			bgrSobel[i][j].Green = sumX;
			bgrSobel[i][j].Red = sumX;
        }
    }
    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgr[i][j] = bgrSobel[i][j];
        }
    }
}

void SobelFilterY(BGRTriple **bgrSobel, BGRTriple **bgr,  BITMAPINFOHEADER bitmapInfoHeader)
{
    for (i = 1; i < bitmapInfoHeader.biHeight - 1; i++)
	{
		for (j = 1; j < bitmapInfoHeader.biWidth - 1; j++)
		{
			sumY = 0;
			sumY += bgr[i - 1][j - 1].Green * GY[0][0] +
				bgr[i - 1][j].Green * GY[0][1] +
				bgr[i - 1][j + 1].Green * GY[0][2] +

				bgr[i][j - 1].Green * GY[1][0] +
				bgr[i][j].Green * GY[1][1] +
				bgr[i][j + 1].Green * GY[1][2] +

				bgr[i + 1][j - 1].Green * GY[2][0] +
				bgr[i + 1][j].Green * GY[2][1] +
				bgr[i + 1][j + 1].Green * GY[2][2];


			if (sumY > 255)
			{
				sumY = 255;
			}
			if (sumY < 0)
			{
				sumY = 0;
			}
			bgrSobel[i][j].Blue = sumY;
			bgrSobel[i][j].Green = sumY;
			bgrSobel[i][j].Red = sumY;
        }
    }
    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgr[i][j] = bgrSobel[i][j];
        }
    }
}

void SobelFilterXY(BGRTriple **bgrSobel, BGRTriple **bgr,  BITMAPINFOHEADER bitmapInfoHeader)
{
    int8_t fl = 0;
    for (i = 1; i < bitmapInfoHeader.biHeight - 1; i++)
	{
		for (j = 1; j < bitmapInfoHeader.biWidth - 1; j++)
		{
			sumX = 0;
			sumX += bgr[i - 1][j - 1].Green * GX[0][0] +
				bgr[i - 1][j].Green * GX[0][1] +
				bgr[i - 1][j + 1].Green * GX[0][2] +

				bgr[i][j - 1].Green * GX[1][0] +
				bgr[i][j].Green * GX[1][1] +
				bgr[i][j + 1].Green * GX[1][2] +

				bgr[i + 1][j - 1].Green * GX[2][0] +
				bgr[i + 1][j].Green * GX[2][1] +
				bgr[i + 1][j + 1].Green * GX[2][2];

            sumY = 0;
			sumY += bgr[i - 1][j - 1].Green * GY[0][0] +
				bgr[i - 1][j].Green * GY[0][1] +
				bgr[i - 1][j + 1].Green * GY[0][2] +

				bgr[i][j - 1].Green * GY[1][0] +
				bgr[i][j].Green * GY[1][1] +
				bgr[i][j + 1].Green * GY[1][2] +

				bgr[i + 1][j - 1].Green * GY[2][0] +
				bgr[i + 1][j].Green * GY[2][1] +
				bgr[i + 1][j + 1].Green * GY[2][2];

            sumXY = (sumX + sumY)/2;
			if (sumXY > 255)
			{
				sumXY = 255;
			}
			if (sumXY < 0)
			{
				sumXY = 0;
			}
			bgrSobel[i][j].Blue = sumXY;
			bgrSobel[i][j].Green = sumXY;
			bgrSobel[i][j].Red = sumXY;
        }
    }
    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgr[i][j].Blue = bgrSobel[i][j].Blue;
            bgr[i][j].Green = bgrSobel[i][j].Green;
            bgr[i][j].Red = bgrSobel[i][j].Red;
        }
    }
}