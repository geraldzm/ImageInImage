#ifndef IMAGEINIMAGE_LISTOFIMAGES_H
#define IMAGEINIMAGE_LISTOFIMAGES_H

#include "Histogram.h"

struct ListOfImages {

    Histogram* image;
    int length;
    unsigned long sumOfColors;
    
    ~ListOfImages(){
        delete[] image;
    }

};


#endif //IMAGEINIMAGE_LISTOFIMAGES_H
