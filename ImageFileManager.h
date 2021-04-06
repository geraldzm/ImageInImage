#ifndef IMAGEINIMAGE_IMAGEFILEMANAGER_H
#define IMAGEINIMAGE_IMAGEFILEMANAGER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "Image.h"

class ImageFileManager {

public:
    static Image* getImage(std::string pPath) {

        cv::Mat m = cv::imread(pPath, cv::IMREAD_COLOR);

        auto *pixels = new Pixel[m.rows * m.cols];
        Pixel *currentPixel = pixels;

        for(int row = 0; row < m.rows; row++) {
            for (int column = 0; column < m.cols; column++) {

                uint8_t *blue = m.ptr(row, column);
               // uint8_t *green = blue + 1;
                //uint8_t *red = blue + 2;

                *currentPixel = Pixel(*(blue + 2), *(blue + 1), *blue);

                currentPixel++;
            }
        }

        return new Image(pixels, m.rows, m.cols);
    }
};

#endif //IMAGEINIMAGE_IMAGEFILEMANAGER_H
