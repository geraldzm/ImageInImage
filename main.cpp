#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"
#include "BackTracking.h"
#include "Probabilistic.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main() {

    cout << "Loading images..." << endl;
    ListOfImages* image0 = ImageFileManager::getImage("./pru/c0.jpg", "cero-", false);
    ListOfImages* image1 = ImageFileManager::getImage("./pru/c1.jpg","uno-", true);
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
/*
    cout << "searching with backtracking..." << endl;
    BackTracking backTracking = BackTracking();
   int  res = backTracking.search(list);
    cout << "Result of backtracking: " << res << endl;
*/


    cout << "searching with probabilistic..." << endl;
    Probabilistic probabilistic = Probabilistic();

    auto t0 = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
    int  res = probabilistic.search(list);
    auto t1 = duration_cast <milliseconds> (system_clock::now().time_since_epoch());

    cout << "Result of probabilistic: " << res << endl;

    auto duration = t1 - t0;
    cout << "\nTime:\t" << duration.count() << "\t\tmicroseconds" << endl;

    delete image1;
    delete image0;

    return 0;
}
