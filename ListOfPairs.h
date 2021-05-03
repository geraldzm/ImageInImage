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

    double getPriority() const{
        return histogram0->priority + histogram1->priority;
    }

};

struct ComparePairs {

    bool operator()(Pair const& p1, Pair const& p2) {
        return p1.getPriority() < p2.getPriority();
    }

};

class ListPairs {

public:
    vector <Pair> list;
    int pivote;

    ListPairs(ListOfImages *pImage0, ListOfImages *pImage1) {

        cout << "Sum0: " << endl;
        pImage0->printColors();

        cout << "Sum1: " << endl;
        pImage1->printColors();
        
        pivote =  abs(int((pImage0->sumOfUniqueColors / pImage0->length) - (pImage1->sumOfUniqueColors / pImage1->length))) *0.22; //valor alambrado que se modifica

        for(int i = 0; i < pImage0->length; i++)
            for(int j = 0; j < pImage1->length; j++)
                addPair((pImage0->image + i), (pImage1->image + j));

        cout << "PivoteUniqueColors: " << pivote << endl;
        cout << "size of list: " << list.size() << endl;
    }

private:

    void addPair(Histogram* pHisto0, Histogram* pHisto1) {
        
        if(abs(int(pHisto0->pixelHash.size() - pHisto1->pixelHash.size())) <= pivote)
            list.emplace_back(Pair(pHisto0, pHisto1));

    }
    
   void printPairs() {
        for(auto & current : list){
            cout << "Value 1: " << current.histogram0->pixelHash.size() << "\tValue 2: " << current.histogram1->pixelHash.size() << endl;
        }
        cout << "AMOUNT OF PAIRS: " << list.size() << endl;
    }

};



#endif /* ListOfPairs_h */
