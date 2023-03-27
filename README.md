
## Build
```
mkdir build
cd build
cmake ..
make
```

Файл file.bmp  должен находиться в директории /bmp
## Commands
```
Sobel > ./bmp_filters file.bmp sobel <1, 2, 3> (horizontal/vertical/vertical+horizontal)

Gauss > ./bmp_filters file.bmp gauss <3, 5, 7, 9, 11> (gauss core size) <0...> (dispersion (float))

Median > ./bmp_filters file.bmp median <3, 5, 7, 9, 11> median core size

Otsu > ./bmp_filters file.bmp otsu 

Info > ./bmp_filters file.bmp info 
```
