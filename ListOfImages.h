#ifndef IMAGEINIMAGE_LISTOFIMAGES_H
#define IMAGEINIMAGE_LISTOFIMAGES_H

#include "Histogram.h"
#include "iostream"

struct ListOfImages {

    Histogram* image;
    int length;

    unsigned long sumOfColorR;
    unsigned long sumOfColorG;
    unsigned long sumOfColorB;


    ~ListOfImages(){
        delete[] image;
    }


public:
    void printColors() {

        std::cout << "R:\t" << sumOfColorR << std::endl;
        std::cout << "G:\t" << sumOfColorG << std::endl;
        std::cout << "B:\t" << sumOfColorB << std::endl;

    }


};


#endif //IMAGEINIMAGE_LISTOFIMAGES_H
