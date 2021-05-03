#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"
#include "BackTracking.h"

using namespace std;

int main() {
    
    
    ListOfImages* image0 = ImageFileManager::getImage("/Users/danielbejarano/Desktop/Análisis de Algoritmos/Projects/Proyecto1/ImageProject1/pru/c0.jpg", "cero-");
    ListOfImages* image1 = ImageFileManager::getImage("/Users/danielbejarano/Desktop/Análisis de Algoritmos/Projects/Proyecto1/ImageProject1/pru/c1.jpg","uno-");

    ListPairs list(image0, image1);

    DivideAndConquer searcher = DivideAndConquer();
    int res = searcher.search(list);

    cout << "Result divide: " << res << endl<< endl<< endl;

    BackTracking backTracking = BackTracking();
    res = backTracking.search(list);
    
    cout << "Result backtracking: " << res << endl;


    delete image1;
    delete image0;

    return 0;
}
