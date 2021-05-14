#ifndef ImageSearcher_h
#define ImageSearcher_h

#include "ListOfPairs.h"

class ImageSearcher {

public:
    virtual int search(ListPairs pList) = 0;

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < 25;
    }

};


#endif /* ImageSearcher_h */
