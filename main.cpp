#include <unordered_set>
#include "ImageFileManager.h"

int main() {

    Image* image = ImageFileManager::getImage("/home/gerald/Pictures/img1.jpg");

    std::cout << image->histogram.calculateCosineSimilarity(image->histogram) << std::endl;

    delete[] image;

    return 0;
}
