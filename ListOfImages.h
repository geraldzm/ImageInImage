#ifndef IMAGEINIMAGE_LISTOFIMAGES_H
#define IMAGEINIMAGE_LISTOFIMAGES_H

#include "Histogram.h"
#include "iostream"

struct ListOfImages {

    Histogram* image;
    int length;
    unsigned long sumOfUniqueColors;


    ~ListOfImages(){
        delete[] image;
    }


public:
    void printColors() {

        std::cout << "ALL:\t" << sumOfUniqueColors << std::endl;

    }


};


#endif //IMAGEINIMAGE_LISTOFIMAGES_H
