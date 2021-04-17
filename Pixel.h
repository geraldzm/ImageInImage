#ifndef IMAGEINIMAGE_PIXEL_H
#define IMAGEINIMAGE_PIXEL_H

#include "iostream"

class Pixel {

private:
    uint32_t color;

public:
    Pixel():color(0){}

    explicit Pixel(uint32_t color):color(color){}

    Pixel(uint8_t red, uint8_t green, uint8_t blue): color(0){
        setColor(red, green, blue);
    }

    void setColor(uint8_t red, uint8_t green, uint8_t blue) {

        int numbersRounders[5] {0, -1, -2, 2, 1};

        red += *(numbersRounders + (red % 5));

        color = red;
        color <<= 8u;

        green += *(numbersRounders + (green % 5));

        color = color | green;
        color <<= 8u;

        blue += *(numbersRounders + (blue % 5));

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

    bool operator==(const Pixel &pixel) const {
        return pixel.color == color;
    }

    bool operator==(const Pixel *pixel) const {
        return pixel->color == color;
    }

    bool operator() (const Pixel& pPixel) const {
        return color == pPixel.color;
    }

    bool operator() (const Pixel* pPixel) const {
        return color == pPixel->color;
    }

};


#endif //IMAGEINIMAGE_PIXEL_H
