#ifndef Probabilistic_h
#define Probabilistic_h
#include "ImageSearcher.h"

class Probabilistic : ImageSearcher {
    
public:
    
    int probabilistic(ListPairs pList){

    }
    
    int search(ListPairs pList) override{
        return probabilistic(pList);
    }
   
};




#endif /* Probabilistic_h */
