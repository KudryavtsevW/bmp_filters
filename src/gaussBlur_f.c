#include "../headers/Filters.h"
#include "../mylib/listLib.h"

uint8_t x,y;
BGRTriple **GaussBlur(BGRTriple** bgr, BITMAPINFOHEADER bitmapInfoHeader, uint8_t coreSize, double sigma)
{
    unsigned int i,j;    
    printf("size kernel gauss = %d\n", coreSize);
    BGRTriple **bgrGauss = NULL;
    //create bgrSobel
    bgrGauss = (BGRTriple **)calloc(bitmapInfoHeader.biHeight, sizeof(BGRTriple *));
    if(bgrGauss == NULL)
        printf("calloc error Sobel\n");
    for(i = 0; i< bitmapInfoHeader.biHeight;i++)
    {
        bgrGauss[i] = (BGRTriple *)calloc(bitmapInfoHeader.biWidth, sizeof(BGRTriple));
    }

    double **coreGauss = NULL;
    coreGauss = (double **)calloc(coreSize, sizeof(double *));
    if(coreGauss == NULL)
        printf("calloc core Error\n");
    for(i = 0;i<coreSize;i++)
    {
        coreGauss[i] = (double *)calloc(coreSize, sizeof(double));
    }

    CoreGauss(coreGauss,sigma, coreSize);

    for(i = 0;i<coreSize;i++)
    {
        for(j = 0;j<coreSize;j++)
        {
            printf("%lf ", coreGauss[i][j]);
        }
        printf("\n");
    }

    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0; j<bitmapInfoHeader.biWidth;j++)
        {
            bgrGauss[i][j].Blue = GetGaussPixelB(bgr, bitmapInfoHeader, coreGauss, coreSize, i, j);
            bgrGauss[i][j].Red = bgrGauss[i][j].Blue;
            bgrGauss[i][j].Green = bgrGauss[i][j].Blue;
        }
    }
    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgr[i][j].Blue = bgrGauss[i][j].Blue;
            bgr[i][j].Red = bgr[i][j].Blue;
            bgr[i][j].Green = bgr[i][j].Blue;
        }
    }

    for(i = 0;i<coreSize;i++)
    {
        free(coreGauss[i]);
    }
    free(coreGauss);

    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        free(bgrGauss[i]);
    }
    free(bgrGauss);
    return bgr;
}

void CoreGauss(double **coreGauss, double sigma, uint8_t coreSize)
{
	int r;
    unsigned int i,j; 
	double twoSigmaSqw = 2 * sigma * sigma;
	const double PI = 3.1415926535;
	double twoPiSigmSqw = 2 * PI * sigma * sigma;
	int indexKern = -(coreSize - 1) / 2;
	double sum = 0;
	for (i = 0; i < coreSize; i++)
	{
		for (j = 0; j < coreSize; j++)
		{
			r = (i + indexKern) * (i + indexKern) + (j + indexKern) * (j + indexKern);
			//r = i * i + j * j; - так не работает
			coreGauss[i][j] = (1 / twoPiSigmSqw) * exp(-(r / twoSigmaSqw));
			sum += coreGauss[i][j];
		}
	}
	for (i = 0; i < coreSize; i++)
	{
		for (j = 0; j < coreSize; j++)
		{
			coreGauss[i][j] /= sum;
		}
	}
}


int **FillPixelCoreB(BGRTriple** bgr, BITMAPINFOHEADER bitmapInfoHeader, int **pixelCore, uint8_t coreSize, unsigned int i, unsigned int j)
{
    List *lVec = (List *)malloc(sizeof(List));
    lVec->next = NULL;
    lVec->val = 0;
	for (y = 0; y < coreSize; y++)
	{
		for (x = 0; x < coreSize; x++)
		{
			if (((i - coreSize / 2 + y) >= 0) && ((j - coreSize / 2 + x) >= 0) && ((i - coreSize / 2 + y) < bitmapInfoHeader.biHeight) && ((j - coreSize / 2 + x) < bitmapInfoHeader.biWidth))
				pushBack(lVec, bgr[i - coreSize / 2 + y][j - coreSize / 2 + x].Blue);
		}
	}
	while (sizeList(lVec) != coreSize * coreSize)
	{
		int rnd = rand() % sizeList(lVec);
		pushBack(lVec, getVal(lVec, rnd));
	}
    //printf("i = %d\tj = %d\n", i, j);
    
	int tmp = 0;
	toCore(pixelCore, lVec, coreSize);
    deleteList2(lVec);
	return pixelCore;
}



int** MultiplicateCores(int** pixelCore, double** coreGauss, uint8_t coreSize)
{
    unsigned int i,j; 
	for (i = 0; i < coreSize; i++)
	{
		for (j = 0; j < coreSize; j++)
		{
			pixelCore[i][j] = round(pixelCore[i][j]*coreGauss[i][j]);
		}
	}

	return pixelCore;
}

int GetGaussPixelB(BGRTriple **bgr, BITMAPINFOHEADER bitmapInfoHeader, double** coreGauss, uint8_t coreSize, unsigned int i, unsigned int j)
{
    uint8_t k = 0;
    int **pixelCoreB = NULL;
    pixelCoreB = (int **)calloc(coreSize, sizeof(int *));
    if(pixelCoreB == NULL)
        printf("calloc pixelCore Error\n");
    for(k = 0;k<coreSize;k++)
    {
        pixelCoreB[k] = (int *)calloc(coreSize, sizeof(int));
    }
	int resultPixB = 0;
	pixelCoreB = FillPixelCoreB(bgr, bitmapInfoHeader, pixelCoreB, coreSize, i, j);
	pixelCoreB = MultiplicateCores(pixelCoreB, coreGauss, coreSize);
	resultPixB = GetCorePixel(pixelCoreB, coreSize);
	
    for(k = 0;k<coreSize;k++)
    {
        free(pixelCoreB[k]);
    }

	if (resultPixB > 255)
		resultPixB = 255;
	if (resultPixB < 0)
		resultPixB = 0;

	return resultPixB;
}

int GetCorePixel(int** pixelCore, uint8_t coreSize)
{
    unsigned int i,j; 
	double sum = 0;
	for (i = 0; i < coreSize; i++)
	{
		for (j = 0; j < coreSize; j++)
		{
			sum += pixelCore[i][j];
		}
	}
	//printf("%lf \n", sum);
	return (int)sum;
}
