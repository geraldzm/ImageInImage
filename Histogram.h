#ifndef IMAGEINIMAGE_IMAGE_H
#define IMAGEINIMAGE_IMAGE_H

#include <cmath>
#include <unordered_map>
#include "Pixel.h"

namespace std {
    template<>
    struct hash<Pixel*> {
        size_t operator()(const Pixel* pixel) const {
            return hash<uint32_t>()(pixel->getColor());
        }
    };
}

class Histogram {

private:
    std::unordered_map<Pixel*, int> pixelHash;
    unsigned int norm;

public:

    Histogram():norm(0){
        pixelHash = {};
    }

    ~Histogram() {

        for(auto & current : pixelHash)
            delete current.first;

     //   pixelHash.clear();
    }


    void addPixel(uint8_t red, uint8_t green, uint8_t blue) {

        auto* pixel = new Pixel(red, green, blue);

        auto ptr = pixelHash.find(pixel);

        if(ptr != pixelHash.end()) {
            ptr->second += 1;
            delete pixel;
        } else{
            pixelHash[pixel] = 1;
        }
    }


    double calculateCosineSimilarity(Histogram &histogram) {

        printHistogram();
        // (A*B) / (||A|| * ||B||)

        uint32_t quotient = 0;
        int appearances;

        for(auto & current : pixelHash) {
            appearances = histogram.pixelHash[current.first];

            if(appearances != 0)
                quotient += appearances * current.second;
        }

        double rs = quotient / ((double) (getNorm() * histogram.getNorm()));

        std::cout << "Size Hash 1: " << pixelHash.size() << std::endl;
        std::cout << "Size Hash 2: " << histogram.pixelHash.size() << std::endl;

        std::cout << "Norm Hash 1: " << getNorm() << std::endl;
        std::cout << "Norm Hash 2: " << histogram.getNorm() << std::endl;

        std::cout << "rs: " << rs << std::endl;

        return cos(rs);
    }

    unsigned int getNorm() {
        if(norm != 0)
            return norm;

        calculateNorm();

        return norm;
    }

    void printHistogram() {
        for(auto & current : pixelHash)
            std::cout << "Red: " << current.first->getRed() << " Green: " << current.first->getGreen() << " Blue: "<< current.first->getBlue() << std::endl;
    }

private:
    void calculateNorm() {
        for(auto & current : pixelHash)
            norm += current.second * current.second;
    }

};


#endif //IMAGEINIMAGE_IMAGE_H
