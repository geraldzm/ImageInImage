#ifndef Backtracking_h
#define Backtracking_h
#include "ImageSearcher.h"
#include <queue>


class BackTracking : ImageSearcher {

public:

    int search(ListPairs pList) override {

        priority_queue<Pair*,  vector<Pair*>, ComparePairs> priorityQueue0;
        priority_queue<Pair*,  vector<Pair*>, ComparePairs> priorityQueue1;

        auto *currentQueue = &priorityQueue0;
        auto *auxQueue = currentQueue;
        auto *nextQueue = &priorityQueue1;

        int counter = 0, loopCount = 0;
        double poda, prioritySum;

        for(auto & current: pList.list) // n
            priorityQueue0.push(&current);

        Pair* current;
        Pair* pairToMove;
        while (!currentQueue->empty()) {
            loopCount++;
            current = currentQueue->top();
            currentQueue->pop();

            incrementIfMatch(&counter, *current);

            poda = current->getPriority();
            while (!currentQueue->empty()) {

                pairToMove = currentQueue->top();
                currentQueue->pop();

                prioritySum = pairToMove->getPriority();

                if(poda <= prioritySum * 2) {
                    nextQueue->push(pairToMove);
                    poda = prioritySum;
                } else {
                    *currentQueue = priority_queue<Pair*,  vector<Pair*>, ComparePairs>(); // clean
                    cout << "Hi" << endl;
                }

            }

            auxQueue = nextQueue;
            nextQueue = currentQueue;
            currentQueue = auxQueue;

        }

        cout << loopCount<< endl;

        return counter;
    }

    void incrementIfMatch(int *counter, Pair &toCompare) const {

        if(isMatch(toCompare)) {
            cout << "Image0: " << toCompare.histogram0->numberImage << "  Image1: " << toCompare.histogram1->numberImage << " Value: " << toCompare.cosineSimilarity << endl;
            (*counter)++;
            toCompare.histogram1->priority *= 1.5;
            toCompare.histogram0->priority *= 1.5;
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
