#include <unordered_set>
#include "ImageFileManager.h"

//#include "Histogram.h"


using namespace std;

int main() {

   // std::cout << (int) (74.65 + 0.5) << std::endl;

    Image* image = ImageFileManager::getImage("/home/gerald/Pictures/img1.jpg");
    Image* image0 = ImageFileManager::getImage("/home/gerald/Pictures/img4.jpg");

    struct less{
        int i = 0, j = 0;
        double val = 500;
    } myLess;

    int amount = 0;


    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){

             double rs = (image+i)->histogram.calculateCosineSimilarity((image0 + j)->histogram);

             if(rs <= 60) {
                 std::cout << "Less than 60 : " << j << std::endl;
                 amount++;
             }

             if(rs <= myLess.val) {
                 myLess.i = i;
                 myLess.j = j;
                 myLess.val = rs;
             }

        }

    }

    std::cout << "Less:\t i " << myLess.i << " \tj" << myLess.j << "\t val" << myLess.val << std::endl;
    std::cout << "amount: " << amount << std::endl;


    delete[] image;
    delete[] image0;

    return 0;
}
