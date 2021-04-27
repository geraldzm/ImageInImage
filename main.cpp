#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"
//#include "Histogram.h"


using namespace std;

int main() {

    Image* diego = ImageFileManager::getImage("/Users/danielbejarano/Desktop/diegoEditado.jpg", "diego-");
    Image* tuanis = ImageFileManager::getImage("/Users/danielbejarano/Desktop/tuanis.jpg", "tuanis-");

    listPairs lista;

    for(int i = 0; i < diego->length; i++)
        for(int j = 0; j < tuanis->length; j++)
            lista.addPair(&(diego+i)->histogram, &(tuanis+j)->histogram);

    lista.printPairs();
    
    DivideAndConquer searcher = DivideAndConquer();
    int res = searcher.search(lista);
    
    cout << "Result: " << res << endl;
    
    delete[] diego;
    delete[] tuanis;

    return 0;
}
