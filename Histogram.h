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
    double norm, priority;
    int numberImage;
    bool imageOwner; // false = image0, true = image1

public:

    Histogram():norm(0), numberImage(0), priority(0.5), imageOwner(false){
        pixelHash = {};
    }

    
    void addPixel(uint8_t red, uint8_t green, uint8_t blue) {

        Pixel pixel(red, green, blue);
        pixelHash[pixel]++;

    }

    double calculateCosineSimilarity(Histogram &histogram) {

        // (A*B) / (||A|| * ||B||)
        unsigned int quotient = 0;
        int equal = 0;
        int appearances;

        for(auto & current : pixelHash) {

           // auto ptr = histogram.pixelHash.find(current.first);
            
            if(histogram.pixelHash.find(current.first) == histogram.pixelHash.end())
                continue;
            
            appearances = histogram.pixelHash[current.first];
            quotient += appearances * current.second;
            equal++;
            /*
            if(ptr != histogram.pixelHash.end()) {
                quotient += ptr->second * current.second;
                equal ++;
            }
             */
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

    bool operator()(Histogram const* h1, Histogram const* h2) {
        return h1->pixelHash.size() < h2->pixelHash.size();
    }

private:
    void calculateNorm() {
        for(auto & current : pixelHash)
            norm += current.second * current.second;
        norm = sqrt(norm);
    }

};

struct CompareHistograms {
    bool operator()(Histogram* h1, Histogram* h2) {
        return h1->pixelHash.size() > h2->pixelHash.size();
        //return h1->priority > h2->priority;
    }
};

#endif //IMAGEINIMAGE_IMAGE_H
