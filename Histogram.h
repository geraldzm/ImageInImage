#ifndef IMAGEINIMAGE_IMAGE_H
#define IMAGEINIMAGE_IMAGE_H

#include <cmath>
#include <unordered_map>
#include "Pixel.h"

namespace std {
    template<>
    struct hash<Pixel> {
        size_t operator()(const Pixel pixel) const {
            return hash<uint32_t>()(pixel.getColor());
        }
    };
}

class Histogram {

public:
    std::unordered_map<Pixel, int> pixelHash;
    double norm;

public:

    Histogram():norm(0){
        pixelHash = {};
    }

    void addPixel(uint8_t red, uint8_t green, uint8_t blue) {

        Pixel pixel(red, green, blue);
        pixelHash[pixel]++;

    }


    double calculateCosineSimilarity(Histogram &histogram) {

        // (A*B) / (||A|| * ||B||)

        unsigned int quotient = 0;
        int appearances;
        int equal = 0;

        for(auto & current : pixelHash) {
            appearances = histogram.pixelHash[current.first];

            if(appearances != 0) {
                quotient += appearances * current.second;
                equal ++;
            }
        }

        double rs = quotient / ((double) (getNorm() * histogram.getNorm()));
/*
        std::cout << "Equals: " << equal << std::endl;
        std::cout << "quotient: " << quotient << std::endl;
        std::cout << "Size Hash 1: " << pixelHash.size() << std::endl;
        std::cout << "Size Hash 2: " << histogram.pixelHash.size() << std::endl;

        std::cout << "Norm Hash 1: " << getNorm() << std::endl;
        std::cout << "Norm Hash 2: " << histogram.getNorm() << std::endl;

        std::cout << "rs: " << rs << std::endl;
*/
        // round 4 digits precision to avoid decimal trash i.e 1.0000000000000002
      //  vectorDistance = (double)Math.round(vectorDistance * 10000d) / 10000d;


        return acos(rs)*180/3.141592654;
       // return acos(rs);
    }

    double getNorm() {
        if(norm != 0)
            return norm;

        calculateNorm();

        return norm;
    }

    void printHistogram() {
        for(auto & current : pixelHash)
            std::cout << "Red: " << (int)current.first.getRed() << " Green: " << (int)current.first.getGreen() << " Blue: "<< (int)current.first.getBlue() << "\tColor: " << (int)current.first.getColor() << "\t" << "times: " << current.second<<std::endl;
    }

private:
    void calculateNorm() {
        for(auto & current : pixelHash)
            norm += current.second * current.second;
        norm = sqrt(norm);
    }

};


#endif //IMAGEINIMAGE_IMAGE_H
