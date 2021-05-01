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

#define SQUARES_WIDTH_HALF 40
#define SQUARES_HEIGHT_HALF 22

#define AMOUNT_SQUARES (RESIZE_HEIGHT/SQUARES_HEIGHT) * (RESIZE_WIDTH/SQUARES_WIDTH)

static int squares = 0;

class ImageFileManager {

public:

    static void loadHistogram(Histogram &pHistogram, cv::Mat &pImageMatrix, const int &pXSquare,const int &pYSquare, std::string imageName) {
        
        int x = pXSquare;
        int y = pYSquare;
        int width = SQUARES_WIDTH;
        int height = SQUARES_HEIGHT;
        
        if(pXSquare > 0 ){
            x -= SQUARES_WIDTH_HALF;
            width += SQUARES_WIDTH_HALF;
        }

        if(pYSquare > 0){
            y -= SQUARES_HEIGHT_HALF;
            height += SQUARES_HEIGHT_HALF;
        }
        
        if(pXSquare < RESIZE_WIDTH - SQUARES_WIDTH){
            width += SQUARES_WIDTH_HALF;
        }
        
        if(pYSquare < RESIZE_HEIGHT - SQUARES_HEIGHT){
            height += SQUARES_HEIGHT_HALF;
        }
            
        
        cv::Mat square = cv::Mat::zeros(width, height, cv::IMREAD_COLOR);
        square = pImageMatrix(cv::Rect(x, y, width, height)).clone();
        
        for(int row = y, yMax = height+ y; row < yMax; row++)
            for (int column = x, xMax = width+ x; column < xMax; column++) {

                uint8_t *blue = pImageMatrix.ptr(row, column);
                pHistogram.addPixel(*(blue + 2), *(blue + 1), *blue);

            }

        pHistogram.numberImage = squares;
        std::string name = "./images/" + imageName + std::to_string(squares++) + ".jpg";
        cv::imwrite(name, square);

    }

    static ListOfImages* getImage(std::string pPath, std::string imageName) {


        cv::Mat fullSizeImage = cv::imread(pPath, cv::IMREAD_COLOR);

        auto *list = new ListOfImages;
        list->image = new Histogram[AMOUNT_SQUARES];
        list->length = AMOUNT_SQUARES;
        list->sumOfColorR = 0;
        list->sumOfColorG = 0;
        list->sumOfColorB = 0;

        Histogram *currentHistogram = list->image;

        for( int ySquare = 0; ySquare < RESIZE_HEIGHT; ySquare += SQUARES_HEIGHT)

            for (int xSquare = 0; xSquare < RESIZE_WIDTH; xSquare += SQUARES_WIDTH) {

                loadHistogram(*currentHistogram, fullSizeImage, xSquare, ySquare, imageName);

                list->sumOfColorR += currentHistogram->colorR;
                list->sumOfColorG += currentHistogram->colorG;
                list->sumOfColorB += currentHistogram->colorB;

                currentHistogram++;

            }

        squares = 0;

        return list;
    }

};

#endif //IMAGEINIMAGE_IMAGEFILEMANAGER_H
