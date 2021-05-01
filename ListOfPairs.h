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
    long pivoteR;
    long pivoteG;
    long pivoteB;

    ListPairs(ListOfImages *pImage0, ListOfImages *pImage1) {

        cout << "Sum0 " << endl;
        pImage0->printColors();

        cout << "Sum1: " << endl;
        pImage1->printColors();

        pivoteR = abs(long(pImage0->sumOfColorR / pImage0->length - pImage1->sumOfColorR / pImage1->length));
        pivoteG = abs(long(pImage0->sumOfColorG / pImage0->length - pImage1->sumOfColorG / pImage1->length));
        pivoteB = abs(long(pImage0->sumOfColorB / pImage0->length - pImage1->sumOfColorB / pImage1->length));

        for(int i = 0; i < pImage0->length; i++)
            for(int j = 0; j < pImage1->length; j++)
                addPair((pImage0->image + i), (pImage1->image + j));

        cout << "PivoteR: " << pivoteR << endl;
        cout << "PivoteG: " << pivoteG << endl;
        cout << "PivoteB: " << pivoteB << endl;
        cout << "size of list: " << list.size() << endl;
    }

private:

    void addPair(Histogram* pHisto0, Histogram* pHisto1) {

        char count = 0;

        if(abs(int(pHisto0->colorR - pHisto1->colorR)) <= pivoteR)
            count++;

        if(abs(int(pHisto0->colorG - pHisto1->colorG)) <= pivoteG)
            count++;

        if(abs(int(pHisto0->colorB - pHisto1->colorB)) <= pivoteB)
            count++;

        if(count >= 2)
            list.emplace_back(pHisto0, pHisto1);
    }
    
   void printPairs() {
        for(auto & current : list){
            cout << "Value 1: " << current.histogram0->pixelHash.size() << "\tValue 2: " << current.histogram1->pixelHash.size() << endl;
        }
        cout << "AMOUNT OF PAIRS: " << list.size() << endl;
    }

};



#endif /* ListOfPairs_h */
