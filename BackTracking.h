#ifndef Backtracking_h
#define Backtracking_h
#include "ImageSearcher.h"
#include <queue>


class BackTracking : ImageSearcher {

public:

    int search(ListPairs pList) override {

        priority_queue<Pair,  vector<Pair>, ComparePairs> priorityQueue0;
        priority_queue<Pair,  vector<Pair>, ComparePairs> priorityQueue1;

        auto *currentQueue = &priorityQueue0;
        auto *auxQueue = currentQueue;
        auto *nextQueue = &priorityQueue1;

        int counter = 0;
        double poda, prioritySum;

        for(auto & current: pList.list) // n
            priorityQueue0.push(current);

        while (!currentQueue->empty()) {

            Pair current = currentQueue->top();
            currentQueue->pop();

            incrementIfMatch(&counter, current);

            poda = 1;
            while (!currentQueue->empty()) {
                Pair pairToMove = currentQueue->top();
                currentQueue->pop();

                prioritySum = pairToMove.getPriority();

                if(poda <= prioritySum * 3) {
                    nextQueue->push(pairToMove);
                    poda = prioritySum;
                } else {
                    *currentQueue = priority_queue<Pair,  vector<Pair>, ComparePairs>(); // clean
                }

            }

            auxQueue = nextQueue;
            nextQueue = currentQueue;
            currentQueue = auxQueue;

        }

        return counter;
    }

    void incrementIfMatch(int *counter, Pair &toCompare) const {

        if(isMatch(toCompare)) {
            cout << "Image0: " << toCompare.histogram0->numberImage << "  Image1: " << toCompare.histogram1->numberImage << " Value: " << toCompare.cosineSimilarity << endl;
            (*counter)++;
            toCompare.histogram1->priority *= 1.1;
            toCompare.histogram0->priority *= 1.1;
        }else {
            toCompare.histogram1->priority *= 0.9;
            toCompare.histogram0->priority *= 0.9;
        }

    }

    bool isMatch(Pair &current) const {
        return current.cosineSimilarity < 60;
    }

};

#endif /* Backtracking_h */
