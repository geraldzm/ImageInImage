#ifndef Backtracking_h
#define Backtracking_h
#include "ImageSearcher.h"

class BackTracking : ImageSearcher {

public:

    int search(ListPairs pList) override {

        Pair* found = nullptr; //
        Pair* found0 = nullptr; //

        int counter = 0;

        for(auto & current: pList.list) {

            if(found == nullptr) {

                if(incrementIfMatch(&counter, current, current)) {
                    if(found0 == nullptr)
                        found0 = &current;
                    else
                        found = found0->cosineSimilarity < current.cosineSimilarity ? found0 : &current;
                }

            } else if(found->histogram1 == current.histogram1) {

                Pair toCompare(current.histogram0, found->histogram1);
                incrementIfMatch(&counter, current, toCompare);

            }

        }

        return counter;
    }

    bool incrementIfMatch(int *counter, const Pair &pCurrentPair, Pair &toCompare) const {

        if(isMatch(toCompare)) {
            cout << "Image0: " << pCurrentPair.histogram0->numberImage << "  Image1: " << pCurrentPair.histogram1->numberImage << " Value: " << pCurrentPair.cosineSimilarity << endl;
            (*counter)++;
            return true;
        }

        return false;
    }

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < 50;
    }

};

#endif /* Backtracking_h */
