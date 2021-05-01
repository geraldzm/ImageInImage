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
    int numberImage;

public:

    Histogram():norm(0), numberImage(0){
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

        return acos(rs)*180/3.141592654;
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
