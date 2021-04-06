#include "ImageFileManager.h"

int main() {

    Image *img = ImageFileManager::getImage("/home/gerald/Pictures/img.jpg");

    // ------------------- test --------------------------------------------
    std::cout << "Sizes: " << img->getRows() << " x " << img->getColumns() << std::endl;

    for(int row = 0; row < img->getRows(); row++) {
        for (int column = 0; column < img->getColumns(); column++) {
            Pixel *p = img->getPixel(row, column);
            std::cout << "row: " << row << "\tcolumn: " << column << "\tred: " << (int) p->getRed() << " green: " << (int) p->getGreen() << " blue: " << (int) p->getBlue() << std::endl;
        }
    }

    // ---------------------------------------------------------------


    delete img;

    return 0;
}
