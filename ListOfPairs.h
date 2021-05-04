#ifndef ListOfPairs_h
#define ListOfPairs_h

#include <cmath>
#include <iostream>
#include "vector"
#include "ListOfImages.h"
#include <algorithm>

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
    bool operator()(Pair const* p1, Pair const* p2) {
        return p1->getPriority() < p2->getPriority();
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

        // 1. join vectors
        vector<Histogram *> joined(pImage0->images);
        joined.insert(joined.end(), pImage1->images.begin(), pImage1->images.end());

        // 2. sort
        sort(joined.begin(), joined.end(), CompareHistograms());

        // 3. pairs
        vector<Histogram*> priorityImage0;
        vector<Histogram*> priorityImage1;

        for(auto &current: joined) {

            if(current->imageOwner){ // is from image 1
                addPair(priorityImage1, priorityImage0, current);
            } else { // is from image 0
                addPair(priorityImage0, priorityImage1, current);
            }

        }

        cout << "PivoteUniqueColors: " << pivote << endl;
        cout << "size of list: " << list.size() << endl;
    }

    Pair createPair(Histogram* &pHistogram0, Histogram* &pHistogram1) {

        if(pHistogram0->imageOwner == pHistogram1->imageOwner)
            cout << "Error creating pairs, pairs from the same image are being match: " << endl;

        if(pHistogram0->imageOwner) // if this histogram is from image 1
            return Pair(pHistogram1, pHistogram0);

        return Pair(pHistogram0, pHistogram1);
    }

    void addPair(vector<Histogram*> &pSortedImages, vector<Histogram*> &pSortedImagesToMatch, Histogram* pCurrentHistogram) {

        if(!pSortedImagesToMatch.empty()) {

            int cutOff = 0;

            for(auto & possibleMatch: pSortedImagesToMatch) {

                if(abs(int(possibleMatch->pixelHash.size() - pCurrentHistogram->pixelHash.size())) <= pivote) {
                    list.emplace_back(createPair(possibleMatch, pCurrentHistogram));
                }else if(possibleMatch->pixelHash.size() < pCurrentHistogram->pixelHash.size()) {
                    break;
                }

                cutOff++;
            }

            pSortedImagesToMatch.resize(cutOff);
        }

        insertSorted(pSortedImages, pCurrentHistogram);
    }

    void insertSorted(vector<Histogram*> &pHistograms, Histogram* pToInsert) {
        auto it = upper_bound(pHistograms.cbegin(), pHistograms.cend(), pToInsert, CompareHistograms());
        pHistograms.insert(it, pToInsert);
    }

private:

   void printPairs() {
        for(auto & current : list){
            cout << "Value 1: " << current.histogram0->pixelHash.size() << "\tValue 2: " << current.histogram1->pixelHash.size() << endl;
        }
        cout << "AMOUNT OF PAIRS: " << list.size() << endl;
    }

};



#endif /* ListOfPairs_h */
