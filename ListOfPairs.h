#ifndef ListOfPairs_h
#define ListOfPairs_h

#include <cmath>
#include <iostream>
#include "vector"
#include "ListOfImages.h"

using namespace std;

struct Pair {

    Histogram* histogram0;
    Histogram* histogram1;
    double cosineSimilarity;

    Pair(Histogram* pHisto0, Histogram* pHisto1){
        histogram0 = pHisto0;
        histogram1 = pHisto1;

        cosineSimilarity = pHisto0->calculateCosineSimilarity(*pHisto1);
    }
    
};

class ListPairs {

public:
    vector <Pair> list;
    int pivote;

    ListPairs(ListOfImages *pImage0, ListOfImages *pImage1) {

        cout << "Sum0: " << pImage0->sumOfColors << endl;
        cout << "Sum1: " << pImage1->sumOfColors << endl;

        pivote = abs(long(pImage0->sumOfColors / pImage0->length - pImage1->sumOfColors / pImage1->length)) * 0.22;

        for(int i = 0; i < pImage1->length; i++)
            for(int j = 0; j < pImage0->length; j++)
                addPair((pImage1->image + i), (pImage0->image + j));

        cout << "Pivote: " << pivote << endl;
        cout << "size of list: " << list.size() << endl;
    }

private:

    void addPair(Histogram* pHisto0, Histogram* pHisto1) {

        int difference = abs(int(pHisto0->pixelHash.size() - pHisto1->pixelHash.size()));

        if(difference <= pivote)
            list.push_back(Pair(pHisto0, pHisto1));

    }
    
   void printPairs() {
        for(auto & current : list){
            cout << "Value 1: " << current.histogram0->pixelHash.size() << "\tValue 2: " << current.histogram1->pixelHash.size() << endl;
        }
        cout << "AMOUNT OF PAIRS: " << list.size() << endl;
    }

};



#endif /* ListOfPairs_h */
