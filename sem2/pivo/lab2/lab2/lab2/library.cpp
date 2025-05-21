#define _CRT_SECURE_NO_WARNINGS
#include "library.h"         

string readSets(const char* filename) {       // делит строку на элементы вектора через ,
    FILE* file = std::fopen(filename, "r"); 
    
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    string content;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        content += buffer;
    }

    fclose(file);
    return content;

}

int checkSets(string sets){
    int size = sets.length();
    int openF, closeF, openS, closeS = 0;

    for(int i = 0; i<size; i++){
        if(sets[i] == '{')      openF++;
        if(sets[i] == '}')      closeF++;
        if(sets[i] == '<')      openS++;
        if(sets[i] == '>')      closeS++;

        if(sets[i]==' ')        return 1;
    }

    if(openF!=closeF || openS!=closeS)  return 1;

    return 0;
}
