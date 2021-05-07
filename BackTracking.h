#ifndef Backtracking_h
#define Backtracking_h
#include "ImageSearcher.h"
#include <queue>


class BackTracking : ImageSearcher {

public:

    int search(ListPairs pList) override {
        
        Pair* listPairs = nullptr;
        int counter = 0;
        auto iteratorMax = pList.list.begin();
        auto currentPair = pList.list.begin();
        auto currentMaxPair = pList.list.begin();
        
        do{
            listPairs = &(*(iteratorMax));
            pList.list.erase(iteratorMax);
            currentPair = pList.list.begin();
            incrementIfMatch(&counter, *listPairs);
            currentMaxPair = currentPair;
            while(currentPair != pList.list.end()){
                if(currentPair->getPriority() > currentMaxPair->getPriority())
                    currentMaxPair = currentPair;
                currentPair++;
            }
            
            iteratorMax = currentMaxPair;
            
        }while(currentMaxPair != pList.list.end() && (abs(int(listPairs->getPriority() - currentMaxPair->getPriority())) < 2)) ;
        
        return counter;
    }

    void incrementIfMatch(int *counter, Pair &toCompare) const {

        if(isMatch(toCompare)) {
            cout << "Image0: " << toCompare.histogram0->numberImage << "  Image1: " << toCompare.histogram1->numberImage << " Value: " << toCompare.cosineSimilarity << endl;
            (*counter)++;
            toCompare.histogram1->priority *= 1.2;
            toCompare.histogram0->priority *= 1.2;
        }else {
            toCompare.histogram1->priority *= 0.9;
            toCompare.histogram0->priority *= 0.9;
        }

    }

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < 44;
    }

};

#endif /* Backtracking_h */
