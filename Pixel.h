#ifndef IMAGEINIMAGE_PIXEL_H
#define IMAGEINIMAGE_PIXEL_H

#include "iostream"

class Pixel {

private:
    int32_t color;

public:
    Pixel():color(0){}

    Pixel(uint8_t red, uint8_t green, uint8_t blue): color(0){
        setColor(red, green, blue);
    }

    void setColor(uint8_t red, uint8_t green, uint8_t blue) {
        color = red;
        color <<= 8u;
        color = color | green;
        color <<= 8u;
        color = color | blue;
        color <<= 8u;

        color += 0xFF; // alpha
    }

    void setColor(Pixel &pColor) {
        setColor(pColor.color >> 24u,  pColor.color >> 16u, pColor.color >> 8u);
    }

    uint32_t getColor() const{
        return color;
    }

    uint8_t getRed() const{
        return color >> 24u;
    }

    uint8_t getGreen() const{
        return color >> 16u;
    }

    uint8_t getBlue() const{
        return color >> 8u;
    }
};


#endif //IMAGEINIMAGE_PIXEL_H
