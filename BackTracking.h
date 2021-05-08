#ifndef Backtracking_h
#define Backtracking_h
#include "ImageSearcher.h"
#include <queue>


class BackTracking : ImageSearcher {

public:

    int search(ListPairs pList) override {
        
        int counter = 0;

        int loopCounter = 0;
        unsigned long maxLoop = pList.list.size();
        cout << maxLoop << endl;

        Pair lastMaxPair;
        auto currentMaxPair = pList.list.begin();

        do {

            lastMaxPair = *currentMaxPair;
            pList.list.erase(currentMaxPair);

            incrementIfMatch(&counter, lastMaxPair);

            
            for(auto currentPair = pList.list.begin(), currentMaxPair = pList.list.begin(); currentPair != pList.list.end(); currentPair++)
                if(currentPair->getPriority() > currentMaxPair->getPriority())
                    currentMaxPair = currentPair;

        } while( ++loopCounter < maxLoop && isValidNextMax(&lastMaxPair, currentMaxPair));

        cout << loopCounter << endl;

        return counter;
    }

    bool isValidNextMax(const Pair *pLastMaxPair, const vector<Pair>::iterator &pCurrentMaxPair) const {
        return pLastMaxPair->getPriority() - pCurrentMaxPair->getPriority() <= 0.3;
    }

    void incrementIfMatch(int *counter, Pair &toCompare) const {

        if(isMatch(toCompare)) {
            cout << "Image0: " << toCompare.histogram0->numberImage << "  Image1: " << toCompare.histogram1->numberImage << " Value: " << toCompare.cosineSimilarity  << " priority: " << toCompare.getPriority() << endl;
            (*counter)++;
            toCompare.histogram1->priority *= 1.3;
            toCompare.histogram0->priority *= 1.3;
        } else {
            toCompare.histogram1->priority *= 0.99;
            toCompare.histogram0->priority *= 0.99;
        }
    }

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < 25;
    }
    
    
};

#endif /* Backtracking_h */
