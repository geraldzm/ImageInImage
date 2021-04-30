#ifndef DivideAndConquer_h
#define DivideAndConquer_h
#include "ImageSearcher.h"


class DivideAndConquer : ImageSearcher {
    
public:
    
    int divideAndConquer(vector<Pair>::iterator begin, vector<Pair>::iterator end){
        if(begin + 1 == end){
            if(begin->histogram1->calculateCosineSimilarity(*(begin->histogram2)) < 50){
                std::cout << "Image0: " << begin->histogram1->numberImage << "  Image1: " << begin->histogram2->numberImage << " Value: " <<  begin->histogram1->calculateCosineSimilarity(*(begin->histogram2)) << std::endl;
                return 1;
            }
            return 0;
        }

        vector<Pair>::iterator mid = begin + (end - begin) / 2;
        return divideAndConquer(begin, mid) + divideAndConquer(mid , end);
    }
    
    int search(ListPairs pList) override{
        return divideAndConquer(pList.list.begin(), pList.list.end());
    }
   
};

#endif /* DivideAndConquer_h */

