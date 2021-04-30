#include <unordered_set>
#include "ImageFileManager.h"
#include "ListOfPairs.h"
#include "DivideAndConquer.h"
#include <cmath>

using namespace std;

int main() {
    
    ListOfImages* image0 = ImageFileManager::getImage("/Users/danielbejarano/Desktop/ProyectoImages/d0.jpg", "cero-");

    ListOfImages* image1 = ImageFileManager::getImage("/Users/danielbejarano/Desktop/ProyectoImages/d1.jpg","uno-");

    ListPairs list;
   
    
    int pivote = abs(long(image0->sumOfColors/image0->length  - image1->sumOfColors/image1->length)) * 0.22;
    
    
    for(int i = 0; i < image1->length; i++)
        for(int j = 0; j < image0->length; j++)
            list.addPair( (image1->image+i), (image0->image+j), pivote);
    
    list.pivote = pivote;
    
    cout << "Pivote: " << pivote << endl;
    cout << "size of list: " << list.list.size() << endl;
    
    DivideAndConquer searcher = DivideAndConquer();
    int res = searcher.search(list);
    
    cout << "Result: " << res << endl;
    
    delete image1;
    delete image0;

    return 0;
}
