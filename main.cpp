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


    //----------------------------------------------------------------------------------------------------------------------

    cout << "searching with divide and conquer..." << endl;
    DivideAndConquer searcher = DivideAndConquer();
    auto t0d = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
    int resd = searcher.search(list);
    auto t1d = duration_cast <milliseconds> (system_clock::now().time_since_epoch());

    cout << "Result of divide and conquer: " << resd << endl<< endl<< endl;

    auto durationd = t1d - t0d;
    cout << "\nTime probabilistic:\t" << durationd.count() << "\t\tmicroseconds" << endl;

    //----------------------------------------------------------------------------------------------------------------------
    /*
    cout << "searching with backtracking..." << endl;
    BackTracking backTracking = BackTracking();
    auto t0b = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
    int  resb = backTracking.search(list);
    auto t1b = duration_cast <milliseconds> (system_clock::now().time_since_epoch());

    cout << "Result of backtracking: " << resb << endl;

    auto durationb = t1b - t0b;
    cout << "\nTime probabilistic:\t" << durationb.count() << "\t\tmicroseconds" << endl;
*/
    //----------------------------------------------------------------------------------------------------------------------
/*
    cout << "searching with probabilistic..." << endl;
    Probabilistic probabilistic = Probabilistic();

    auto t0p = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
    int  resp = probabilistic.search(list);
    auto t1p = duration_cast <milliseconds> (system_clock::now().time_since_epoch());

    cout << "Result of probabilistic: " << resp << endl;

    auto durationp = t1p - t0p;
    cout << "\nTime probabilistic:\t" << durationp.count() << "\t\tmicroseconds" << endl;
*/

    delete image1;
    delete image0;

    return 0;
}
