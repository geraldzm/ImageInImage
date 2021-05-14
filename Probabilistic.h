#ifndef Probabilistic_h
#define Probabilistic_h
#include "ImageSearcher.h"
#include <stdlib.h>

class Probabilistic : ImageSearcher {
    
public:

    int search(ListPairs pList) override {

        srand (time(NULL));

        double percentageOfList = 0.25;
        int times = 5;
        int counterMax = 0;

        for(int i = 0; i < times; i++) {

            vector <Pair> listCopy;

            for (int copying = 0; copying < pList.list.size(); copying++) {
                listCopy.push_back(pList.list[copying]);
                listCopy[copying].histogram0->resetAppearances();
                listCopy[copying].histogram1->resetAppearances();

                listCopy[copying].histogram0->priority = 0.5;
                listCopy[copying].histogram1->priority = 0.5;
                
            } //n

            unsigned long  maxLoop = listCopy.size() * percentageOfList;
            int counter = 0;
            double sum = listCopy.size();

            for(unsigned long loopCounter = 0; loopCounter < maxLoop; loopCounter++) {

                double random = (rand() % 101) / 100.0;
                double percentageSum = 0, pairPercentage;
                int index = -1;

                for(auto pair: listCopy) {

                    index++;
                    pairPercentage = (pair.getPriority() / sum) + percentageSum;

                    if(pairPercentage >= random) {
                        break;
                    }

                    percentageSum = pairPercentage;
                }

                auto pairSelected = listCopy.begin() + index;

                incrementIfMatchUpdateSum(&counter, &sum, *pairSelected);

                sum -= pairSelected->getPriority();
                pairSelected->histogram0->decrementAppearances();
                pairSelected->histogram1->decrementAppearances();
                listCopy.erase(pairSelected);
            }

            if(counter > counterMax) counterMax = counter;
            listCopy.clear();
        }

        return counterMax;
    }

    void updatePriority(Histogram *pH0, Histogram *pH1, double *sum, double pPercentage) const {

        *sum -= pH0->priority * pH0->getAppearancesInPairs() + pH1->priority * pH1->getAppearancesInPairs();
        pH0->priority *= pPercentage;
        pH1->priority *= pPercentage;
        *sum += pH0->priority * pH0->getAppearancesInPairs() + pH1->priority * pH1->getAppearancesInPairs();

    }

    void incrementIfMatchUpdateSum(int *counter, double *sum, Pair &toCompare) const {

        Histogram *h1 = toCompare.histogram1;
        Histogram *h0 = toCompare.histogram0;

        if(isMatch(toCompare)) {

            cout << "Image0: " << h0->numberImage << "  Image1: " << h1->numberImage << " Value: " << toCompare.cosineSimilarity << " priority: " << toCompare.getPriority() << endl;
            (*counter)++;

            updatePriority(h0, h1, sum, PRIORITYINCREASE);

        } else {
            updatePriority(h0, h1, sum, PRIORITYDECREASE);
        }
        
    }



};




#endif /* Probabilistic_h */
