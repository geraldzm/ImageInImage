#ifndef IMAGEINIMAGE_LISTOFIMAGES_H
#define IMAGEINIMAGE_LISTOFIMAGES_H

#include "Histogram.h"

struct ListOfImages {

    Histogram* image;
    int length;
    unsigned long sumOfColors;

};


#endif //IMAGEINIMAGE_LISTOFIMAGES_H
