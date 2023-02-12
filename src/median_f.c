#include "../headers/Filters.h"

BGRTriple** MedianFilter(BGRTriple** bgr, BITMAPINFOHEADER bitmapInfoHeader, uint8_t coreSize)
{
	BGRTriple** bgrMed = NULL;
    bgrMed = (BGRTriple **)calloc(bitmapInfoHeader.biHeight, sizeof(BGRTriple *));
    for(unsigned int k = 0;k<bitmapInfoHeader.biHeight;k++)
    {
        bgrMed[k] = (BGRTriple *)calloc(bitmapInfoHeader.biWidth, sizeof(BGRTriple));
    }

	int **pixelCoreB = NULL;
	pixelCoreB = (int **)calloc(coreSize, sizeof(int *));
	for(unsigned int k = 0;k<coreSize;k++)
	{
		pixelCoreB[k] = (int *)calloc(coreSize, sizeof(int));
	}

	int i;
	int j;
	int k;
	
	for (i = 0; i < bitmapInfoHeader.biHeight; i++)
	{
		for (j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			pixelCoreB = FillPixelCoreB(bgr, bitmapInfoHeader, pixelCoreB, coreSize, i, j);
			pixelCoreB = ShakeCore(pixelCoreB, coreSize);
			bgrMed[i][j].Blue = pixelCoreB[coreSize / 2][coreSize / 2];
			bgrMed[i][j].Green = pixelCoreB[coreSize / 2][coreSize / 2];
			bgrMed[i][j].Red = pixelCoreB[coreSize / 2][coreSize / 2];
		}
	}

	for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgr[i][j].Blue = bgrMed[i][j].Blue;
            bgr[i][j].Red = bgr[i][j].Blue;
            bgr[i][j].Green = bgr[i][j].Blue;
        }
    }

	for(unsigned int k = 0;k<coreSize;k++)
	{
		free(pixelCoreB[k]);
	}
	free(pixelCoreB);
    for(unsigned int k = 0;k<bitmapInfoHeader.biHeight;k++)
    {
        free(bgrMed[k]);
    }
    free(bgrMed);
	return bgr;
}

int **ShakeCore(int** pixelCore, uint8_t coreSize)
{
	int buf;
	for (int k = 0; k < coreSize; k++)
	{
		for (int i = 0; i < coreSize; i++)
		{
			for (int j = 0; j < coreSize -1; j++)
			{
				if (pixelCore[i][j] > pixelCore[i][j + 1])
				{
					buf = pixelCore[i][j];
					pixelCore[i][j] = pixelCore[i][j + 1];
					pixelCore[i][j + 1] = buf;
				}
			}
		}

		for (int j = 0; j < coreSize; j++)
		{
			for (int i = 0; i < coreSize -1; i++)
			{
				if (pixelCore[i][j] > pixelCore[i + 1][j])
				{
					buf = pixelCore[i][j];
					pixelCore[i][j] = pixelCore[i + 1][j];
					pixelCore[i + 1][j] = buf;
				}
			}
		}
	}

	return pixelCore;
}
