#ifndef IMAGEINIMAGE_IMAGEFILEMANAGER_H
#define IMAGEINIMAGE_IMAGEFILEMANAGER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "Image.h"

#define RESIZE_WIDTH 3840 // 640
#define RESIZE_HEIGHT 2160 //360

#define SQUARES_WIDTH 160
#define SQUARES_HEIGHT 90

#define AMOUNT_SQUARES (RESIZE_HEIGHT/SQUARES_HEIGHT) * (RESIZE_WIDTH/SQUARES_WIDTH)

static int squares = 0;

class ImageFileManager {

public:

    static void loadHistogram(Histogram &pHistogram, cv::Mat &pImageMatrix, const int &pXSquare,const int &pYSquare, std::string imageName) {

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

    static Image* getImage(std::string pPath, std::string imageName) {

        cv::Mat fullSizeImage = cv::imread(pPath, cv::IMREAD_COLOR);
       // cv::Mat resizedImage = cv::Mat::zeros(RESIZE_WIDTH, RESIZE_HEIGHT, cv::IMREAD_COLOR);

       // cv::resize(fullSizeImage, resizedImage, cv::Size(RESIZE_WIDTH, RESIZE_HEIGHT), 0, 0);

        //cv::imwrite("./images/fullImage.jpg", resizedImage);

        Image* image = new Image[AMOUNT_SQUARES];
        image->length = AMOUNT_SQUARES;
        Image *currentImage = image;

        for( int ySquare = 0; ySquare < RESIZE_HEIGHT; ySquare += SQUARES_HEIGHT)

            for (int xSquare = 0; xSquare < RESIZE_WIDTH; xSquare += SQUARES_WIDTH) {

                loadHistogram(currentImage->histogram, fullSizeImage, xSquare, ySquare, imageName);
                currentImage++;
            }

        return image;
    }

};

#endif //IMAGEINIMAGE_IMAGEFILEMANAGER_H
