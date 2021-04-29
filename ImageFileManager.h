#ifndef IMAGEINIMAGE_IMAGEFILEMANAGER_H
#define IMAGEINIMAGE_IMAGEFILEMANAGER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "ListOfImages.h"

#define RESIZE_WIDTH 3840 // 640
#define RESIZE_HEIGHT 2160 //360

#define SQUARES_WIDTH 160
#define SQUARES_HEIGHT 90

#define AMOUNT_SQUARES (RESIZE_HEIGHT/SQUARES_HEIGHT) * (RESIZE_WIDTH/SQUARES_WIDTH)

static int squares = 0;

class ImageFileManager {

public:

    static void loadHistogram(Histogram &pHistogram, cv::Mat &pImageMatrix, const int &pXSquare,const int &pYSquare, std::string &imageName) {

        cv::Mat square = cv::Mat::zeros(SQUARES_WIDTH, SQUARES_HEIGHT, cv::IMREAD_COLOR);

        square = pImageMatrix(cv::Rect(pXSquare, pYSquare, SQUARES_WIDTH, SQUARES_HEIGHT)).clone();


        for(int row = pYSquare, yMax = SQUARES_HEIGHT + pYSquare; row < yMax; row++)
            for (int column = pXSquare, xMax = SQUARES_WIDTH + pXSquare; column < xMax; column++) {

                uint8_t *blue = pImageMatrix.ptr(row, column);
                pHistogram.addPixel(*(blue + 2), *(blue + 1), *blue);

            }

        std::string name = "./images/" + imageName + std::to_string(squares++) + ".jpg";
        cv::imwrite(name, square);

    }

    static ListOfImages* getImage(std::string pPath, std::string imageName) {


        cv::Mat fullSizeImage = cv::imread(pPath, cv::IMREAD_COLOR);


        auto *list = new ListOfImages;
        list->image = new Histogram[AMOUNT_SQUARES];
        list->length = AMOUNT_SQUARES;

        Histogram *currentHistogram = list->image;

        for( int ySquare = 0; ySquare < RESIZE_HEIGHT; ySquare += SQUARES_HEIGHT)

            for (int xSquare = 0; xSquare < RESIZE_WIDTH; xSquare += SQUARES_WIDTH) {

                loadHistogram(*currentHistogram, fullSizeImage, xSquare, ySquare, imageName);
                list->sumOfColors += currentHistogram->pixelHash.size();
                currentHistogram++;

            }

        squares = 0;

        return list;
    }

};

#endif //IMAGEINIMAGE_IMAGEFILEMANAGER_H
