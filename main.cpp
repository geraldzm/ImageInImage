#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"

using namespace std;

int main() {

    ListOfImages* space = ImageFileManager::getImage("/home/geraldzm/Pictures/space.jpg","space-");
    ListOfImages* mountain = ImageFileManager::getImage("/home/geraldzm/Pictures/montana.jpg", "montana-");

    ListPairs list;

    for(int i = 0; i < space->length; i++)
        for(int j = 0; j < mountain->length; j++)
            list.addPair( (space->image+i), (mountain->image+j));
    
    DivideAndConquer searcher = DivideAndConquer();
    int res = searcher.search(list);
    
    cout << "Result: " << res << endl;
    
    delete[] space;
    delete[] mountain;

    return 0;
}
