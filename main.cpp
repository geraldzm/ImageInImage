#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"
#include "BackTracking.h"

using namespace std;

int main() {
    
    ListOfImages* image0 = ImageFileManager::getImage("/home/geraldzm/Pictures/b0.jpg", "cero-");
    ListOfImages* image1 = ImageFileManager::getImage("/home/geraldzm/Pictures/b1.jpg","uno-");

    ListPairs list(image0, image1);


 //   DivideAndConquer searcher = DivideAndConquer();
   // int res = searcher.search(list);

    BackTracking backTracking = BackTracking();
    int res = backTracking.search(list);
    
    cout << "Result: " << res << endl;
    
    delete image1;
    delete image0;

    return 0;
}
