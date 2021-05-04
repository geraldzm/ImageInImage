#ifndef IMAGEINIMAGE_LISTOFIMAGES_H
#define IMAGEINIMAGE_LISTOFIMAGES_H

#include "Histogram.h"
#include "iostream"

using namespace std;

struct ListOfImages {

    vector<Histogram*> images;

    int length;
    unsigned long sumOfUniqueColors;

    ~ListOfImages(){
        for (auto ptr : images)
            delete ptr;
    }

public:

    explicit ListOfImages(int length){
        this->length = length;
        this->sumOfUniqueColors = 0;
        images = vector<Histogram*>(this->length);
    }

    void printColors() const {
        std::cout << "ALL:\t" << sumOfUniqueColors << std::endl;
    }


};


#endif //IMAGEINIMAGE_LISTOFIMAGES_H
