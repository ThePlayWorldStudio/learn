#include "library.h"

int main(){
    const char* filename = "input.txt"; 
    
    string sets = readSets(filename);

    checkSets(sets);

    return 0;
}
