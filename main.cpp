#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"
#include "BackTracking.h"

#include <queue>

using namespace std;

int main() {

    cout << "Loading images..." << endl;
    ListOfImages* image0 = ImageFileManager::getImage("/Users/danielbejarano/Desktop/Análisis de Algoritmos/Projects/Proyecto1/ImageProject1/pru/c0.jpg", "cero-", false);
    ListOfImages* image1 = ImageFileManager::getImage("/Users/danielbejarano/Desktop/Análisis de Algoritmos/Projects/Proyecto1/ImageProject1/pru/c1.jpg","uno-", true);
    cout << "Images loaded" << endl;
    
    cout << "Creating pairs..." << endl;
    ListPairs list(image0, image1);
    cout << "Pairs created" << endl;
/*
    cout << "searching with divide and conquer..." << endl;
    DivideAndConquer searcher = DivideAndConquer();
    int res = searcher.search(list);
    cout << "Result of divide and conquer: " << res << endl<< endl<< endl;
*/
    cout << "searching with backtracking..." << endl;
    BackTracking backTracking = BackTracking();
   int  res = backTracking.search(list);
    cout << "Result of backtracking: " << res << endl;

    delete image1;
    delete image0;

    return 0;
}
