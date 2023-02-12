#include "../headers/Filters.h"

BGRTriple** OtsuThreshold(BGRTriple** bgr, BITMAPINFOHEADER bitmapInfoHeader)
{
    unsigned int i,j;
    uint8_t lum;
	BGRTriple **bgrOtsu = NULL;
    bgrOtsu = (BGRTriple **)calloc(bitmapInfoHeader.biHeight, sizeof(BGRTriple*));
    for(i = 0; i<bitmapInfoHeader.biHeight; i++)
    {
        bgrOtsu[i] = (BGRTriple*)calloc(bitmapInfoHeader.biWidth, sizeof(BGRTriple));
    }
	unsigned int histogram[256];
	for (i = 0; i < 256; i++)
		histogram[i] = 0;

	for (i = 0; i < bitmapInfoHeader.biHeight; i++)
	{
		for (j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			lum = bgr[i][j].Blue;
			histogram[bgr[i][j].Blue]++;
		}
	}

	unsigned int sumOfLuminance = 0;
	for (i = 0; i < bitmapInfoHeader.biHeight; i++)
	{
		for (j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			sumOfLuminance += bgr[i][j].Blue;
		}
	}
	unsigned int sum = 0;
	for (i = 0; i < 256; i++)
	{
		
		sum += histogram[i];

	}
	unsigned int allPixels = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight;
	// оптимальный порог
	uint8_t optimalThreshold = 0;
	// количество полезных пикселей(пикселей первого класса)
	unsigned int firstClassPixelCount = 0;
	// суммарная яркость полезных пикселей(суммарная яркость пикселей первого ккласса)
	unsigned int firstClassLuminanceSum = 0;

	// оптимальный разброс яркостей
	double optimalSigma = 0.0;
	double global_disp = 0;
    uint8_t threshold;
	for (threshold = 0; threshold < 256; threshold++)
	{
		firstClassPixelCount += histogram[threshold];//
		firstClassLuminanceSum += threshold * histogram[threshold]; // доля полезных пикселей(Текущая суммарная яркость пикселей первого класса) Накопленная сумма до уровня яркости threshold

		double P1 = ((double)firstClassPixelCount) / allPixels; // доля фоновых пикселей(вероятность того то некоторый пиксель будет пикселем первого класса) 
		double P2 = 1.0 - P1; // средняя доля полезных пикселей(вероятность того что некоторый пиксель будет второго класса) 

		double M1 = (firstClassPixelCount == 0) ? 0 : ((double)firstClassLuminanceSum) / firstClassPixelCount; // средняя доля фоновых пикселей(средняя яркость первого класса) 
		if ((allPixels - firstClassPixelCount) == 0)//если перебраны все пиксели
		{
			break;
		}
		double M2 = ((double)(sumOfLuminance - firstClassLuminanceSum)) / (allPixels - firstClassPixelCount); // величина разброса(Разница между яркостью первого класса и яркостью всего изображения делится на разность в количестве пикселей всего изображения и пикселей первого класса) 
		double mDelta = M1 - M2; // общий разброс (разница между средней яркостью первого класса и второго класса)
		double sigma = P1 * P2 * mDelta * mDelta; // находим оптимальный разброс 
		
		if (sigma > optimalSigma)
		{
			optimalSigma = sigma;
			optimalThreshold = threshold;
		}
		global_disp += (((double)threshold - (double)(sumOfLuminance) / (double)(sum)) * ((double)threshold - (double)(sumOfLuminance) / (double)(sum))) * (double)histogram[threshold] / (double)allPixels;
	}
	printf("optimalThreshold = %d \n", optimalThreshold);
	for (int i = 0; i < bitmapInfoHeader.biHeight; i++)
	{
		for (int j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			if (bgr[i][j].Blue > optimalThreshold)
			{
				bgrOtsu[i][j].Blue = 255;
				bgrOtsu[i][j].Green = 255;
				bgrOtsu[i][j].Red = 255;
			}
			else
			{
				bgrOtsu[i][j].Blue = 0;
				bgrOtsu[i][j].Green = 0;
				bgrOtsu[i][j].Red = 0;
			}
		}
	}

    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        for(j = 0;j<bitmapInfoHeader.biWidth;j++)
        {
            bgr[i][j].Blue = bgrOtsu[i][j].Blue;
            bgr[i][j].Green = bgr[i][j].Blue;
            bgr[i][j].Red = bgr[i][j].Blue;
        }
    }
    for(i = 0;i<bitmapInfoHeader.biHeight;i++)
    {
        free(bgrOtsu[i]);
    }
    free(bgrOtsu);

	return bgr;
}