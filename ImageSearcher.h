#ifndef ImageSearcher_h
#define ImageSearcher_h

#include "ListOfPairs.h"

#define COSINEVALUE 25    // valor alambrado para los matches

#define PRIORITYINCREASE 1.3
#define PRIORITYDECREASE 0.99

class ImageSearcher {

public:
    virtual int search(ListPairs pList) = 0;

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < COSINEVALUE;
    }

};


#endif /* ImageSearcher_h */
