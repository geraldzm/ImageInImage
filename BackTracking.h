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

                if(incrementIfMatch(&counter, current)) {
                    if(found0 == nullptr)
                        found0 = &current;
                    else {
                        if(found0->histogram1 == current.histogram1) {
                            found = found0;
                        }else{
                            found = found0->cosineSimilarity < current.cosineSimilarity ? found0 : &current;
                            counter--;
                        }

                    }
                }

            } else if(found->histogram1 == current.histogram1) {

                Pair toCompare(current.histogram0, found->histogram1);
                incrementIfMatch(&counter, toCompare);

            }

        }

        return counter;
    }

    bool incrementIfMatch(int *counter, Pair &toCompare) const {

        if(isMatch(toCompare)) {
            cout << "Image0: " << toCompare.histogram0->numberImage << "  Image1: " << toCompare.histogram1->numberImage << " Value: " << toCompare.cosineSimilarity << endl;
            (*counter)++;
            return true;
        }

        return false;
    }

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < 60;
    }

};

#endif /* Backtracking_h */
