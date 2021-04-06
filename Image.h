#ifndef IMAGEINIMAGE_IMAGE_H
#define IMAGEINIMAGE_IMAGE_H

#include "Pixel.h"

class Image {

private:
    Pixel *pixels;
    int columns, rows;

public:

    Image(Pixel *pPixels, int pColumns, int pRows) {
        pixels = pPixels;
        this->columns = pColumns;
        this->rows = pRows;
    }

    ~Image() {
        delete[] pixels;
    }

    Pixel* getPixel(int pRow, int pColumn) {
        return (pixels + (pRow * columns) + pColumn);
    }

    Image getSubImage(int pStartRow, int pStartColumn, int pEndRow, int pEndColumn);

    int getColumns() const {
        return columns;
    }

    int getRows() const {
        return rows;
    }
};


#endif //IMAGEINIMAGE_IMAGE_H
