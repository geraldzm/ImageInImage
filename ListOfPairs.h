#ifndef ListOfPairs_h
#define ListOfPairs_h
#include <cmath>
#include <cstdlib>
using namespace std;

struct Pair {
    Histogram* histogram1;
    Histogram* histogram2;
    
    Pair(Histogram* pHisto1, Histogram* pHisto2){
        histogram1 = pHisto1;
        histogram2 = pHisto2;
    }
};

class listPairs {

    
public:
    vector <Pair> list;
    
    void addPair(Histogram* pHisto1, Histogram* pHisto2){
        if(abs(int(pHisto1->pixelHash.size() - pHisto2->pixelHash.size())) <= 300)
            list.push_back(Pair(pHisto1,pHisto2));
    }
    
    void printPairs(){
        for(auto & current : list){
            cout << "Value 1: " << current.histogram1->pixelHash.size() << "\tValue 2: " << current.histogram2->pixelHash.size() << endl;
        }
        cout << "AMOUNT OF PAIRS: " << list.size() << endl;
    }
};



#endif /* ListOfPairs_h */
