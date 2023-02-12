#include "headers/Filters.h"
#include "list/listLib.h"
#include "headers/ReadWriteBmp.h"
enum State
{
    SOBEL,
    GAUSS,
    MEDIAN,
    OTSU,
    INFO,
    END
};
int main(int argc, char *argv[])
{
    unsigned int i, j;
    char pathIn[256] = "../bmp/";
    uint16_t signature;
    int in, out;
    i = 0;
    BITMAPFILEHEADER bitmapFileHeadr;
    BITMAPINFOHEADER bitmapInfoHeader;

    uint8_t sobelMode;
    uint8_t coreGaussSize;
    double disp;
    char *nstr;
    char *tstr;
    uint8_t coreMedSize;
    enum State st = END;
    if (argc >= 3)
    {
        while ((argv[1][i]) != 0)
        {
            pathIn[7 + i] = argv[1][i];
            i++;
        }
        if (strcmp(argv[2], "sobel") == 0)
        {
            if (argc == 4)
            {
                sobelMode = atoi(argv[3]);
                if (sobelMode != 0)
                {
                    printf("sobelMode == %d\n", sobelMode);
                }
                else
                {
                    printf("invalid sobel mode\n");
                    return -21;
                }
                if (sobelMode > 3 || sobelMode < 1)
                {
                    printf("invalid sobel mode %d\n", sobelMode);
                    return -22;
                }
            }
            else
            {
                printf("invalid number of arguments (sobel filter): %d\n", argc);
                return -20;
            }
            st = SOBEL;
        }
        if (strcmp(argv[2], "gauss") == 0)
        {
            if (argc == 5)
            {
                coreGaussSize = atoi(argv[3]);
                if (coreGaussSize != 0)
                {
                    printf("coreGaussSize == %d\n", coreGaussSize);
                }
                else
                {
                    printf("invalid core size\n");
                    return -31;
                }
                if (coreGaussSize < 0)
                {
                    printf("invalid core gauss size %d\n", coreGaussSize);
                    return -32;
                }
                if (coreGaussSize % 2 != 1)
                {
                    printf("invalid core gauss size %d\n", coreGaussSize);
                    return -33;
                }
                if (coreGaussSize > 11)
                {
                    printf("take pity on the computer)\n");
                    return -34;
                }
                nstr = argv[4];
                tstr = nstr;
                disp = strtod(nstr, &tstr);
                if (disp == 0 && tstr == nstr)
                {
                    printf("invalid gauss dispersion\n");
                    return -35;
                }
                if (disp <= 0)
                {
                    printf("invalid gauss dispersion (value <= 0): %lf\n", disp);
                    return -36;
                }
            }
            else
            {
                printf("invalid number of arguments (gauss filter): %d\n", argc);
                return -30;
            }
            st = GAUSS;
        }
        if (strcmp(argv[2], "median") == 0)
        {
            if (argc == 4)
            {
                coreMedSize = atoi(argv[3]);
                if (coreMedSize != 0)
                {
                    printf("coreMedSize == %d\n", coreMedSize);
                }
                else
                {
                    printf("invalid coreMedSize\n");
                    return -41;
                }
                if (coreMedSize <= 0)
                {
                    printf("invalid coreMedSize %d\n", coreMedSize);
                    return -42;
                }
                if (coreMedSize % 2 != 1)
                {
                    printf("invalid coreMedSize %d\n", coreMedSize);
                    return -43;
                }
                if (coreMedSize > 11)
                {
                    printf("take pity on the computer)\n");
                    return -44;
                }
            }
            else
            {
                printf("invalid number of arguments (median filter): %d\n", argc);
                return -40;
            }
            st = MEDIAN;
        }
        if (strcmp(argv[2], "otsu") == 0)
        {
            if (argc == 3)
            {
            }
            else
            {
                printf("invalid number of arguments (otsu): %d\n", argc);
                return -50;
            }
            st = OTSU;
        }
        if (strcmp(argv[2], "info") == 0)
        {
            if (argc == 3)
            {
            }
            else
            {
                printf("invalid number of arguments (info): %d\n", argc);
                return -60;
            }
            st = INFO;
        }
    }
    else
    {
        printf("few main arguments\n");
        return -10;
    }
    if(st == END)
    {
        printf("some error\n");
        return -11;
    }
    in = open(pathIn, O_RDONLY);
    if (in == -1)
    {
        perror("file pathIn");
        return -1;
    }
    out = open("../out.bmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    read(in, &signature, sizeof(signature));
    printf("%x \n", signature);
    if (signature == 0x4d42)
    {
        read(in, &bitmapFileHeadr, sizeof(bitmapFileHeadr));
        read(in, &bitmapInfoHeader, sizeof(bitmapInfoHeader));
        if (st != INFO)
        {
            uint8_t padding = bitmapInfoHeader.biWidth % 4;
            BGRTriple **bgr = NULL;
            // create
            bgr = (BGRTriple **)calloc(bitmapInfoHeader.biHeight, sizeof(BGRTriple *));
            if (bgr == NULL)
                printf("calloc error\n");
            for (i = 0; i < bitmapInfoHeader.biHeight; i++)
            {

                bgr[i] = (BGRTriple *)calloc(bitmapInfoHeader.biWidth, sizeof(BGRTriple));
            }
            // read
            bgr = readBmp(bgr, bitmapInfoHeader, in, padding);
            grayFilter(bgr, bitmapInfoHeader);
            printf("gray_f ok\n");
            switch (st)
            {
            case SOBEL:
                SobelFilter(bgr, bitmapInfoHeader, sobelMode);
                break;
            case GAUSS:
                GaussBlur(bgr, bitmapInfoHeader, coreGaussSize, disp);
                break;
            case MEDIAN:
                MedianFilter(bgr, bitmapInfoHeader, coreMedSize);
                break;
            case OTSU:
                OtsuThreshold(bgr, bitmapInfoHeader);
                break;
            default:
                break;
            }

            // write
            saveBmp(out, signature, bitmapFileHeadr, bitmapInfoHeader, bgr, padding);
            for (i = 0; i < bitmapInfoHeader.biHeight; i++)
            {
                free(bgr[i]);
            }
            free(bgr);
        }
        else
            showInf(bitmapFileHeadr, bitmapInfoHeader);
        close(in);
        close(out);
    }
    else
        printf("signature != 0x4d42\n");
    return 0;
}
