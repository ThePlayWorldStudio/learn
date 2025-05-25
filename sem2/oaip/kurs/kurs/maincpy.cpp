#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct Recipe{
    // 1 - первое 2 - второе 3 - десерт 4 - напиток
    char type[18];
    int typenum;
    char name[100];
    int kall;
    int time;
    char description[200];
};

void openFile(FILE *file, char fileName[100], char *mode){
    file = fopen(fileName, mode);
    if(!file){
        cout << "Open file error!\n";
        return;
    }
}

int comp(char str1[100], char str2[100]){
    for(int i = 0; i<strlen(str2); i++){
        if(str1[i]!=str2[i]){
            return 0;
        }
    }
    return 1;
}

int countStructs(FILE *file){
    fseek(file, 0, SEEK_END);
    int num = (int)(ftell(file)/sizeof(Recipe));
    fseek(file, 0, SEEK_SET);
    return num;
}

void structRead(FILE *file, Recipe *dishes, int num){
    for(int i = 0; i<num; i++){
        fread(&dishes[i], sizeof(Recipe), 1, file);
    }

    fseek(file, 0, SEEK_SET);
}

void structWrite(FILE *file, Recipe *dishes, int num){
    for(int i = 0; i < num; i++)
        fwrite(&dishes[i], sizeof(Recipe), 1, file);

        fseek(file, 0, SEEK_SET);
}

void printTitle(FILE *file){
    fprintf(stdout, "%-15s%-20s%-20s%-20s%-100s\n", "Name:", "type", "time", "kallories", "description");
    fprintf(file, "%-15s%-20s%-20s%-20s%-100s\n", "Name:", "type", "time", "kallories", "description");
}

int IsExistsFile(FILE* file, char fileName[100]){
    file = fopen(fileName, "rb");
    return !file? 1: 0;
}

void create(FILE *file, char fileName[100]){
    file = fopen(fileName, "wb");
    if(!file){
        cout << "Create file error!\n";
        return;
    }
    
    fclose(file);

}

void openNewFile(FILE *file, char *fileName){
    if(IsExistsFile(file, fileName)){
        cout << "file " << fileName << " was created\n";
        create(file, fileName);
    }
}

int checkIsEmpty(FILE *file){
    int num = countStructs(file);
    return num>0?1 :0;
}

void add(FILE *file, char fileName[100]){
    Recipe dish;
    int n;
    int iche;
    bool problem = true;
    file = fopen(fileName, "ab");
    if(!file){
        cout << "Open file error!\n";
        return;
    }
    cout << "Введите количество рецептов: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    for(int i = 0; i < n; i++){
        cout << "Введите название рецепта: ";
        cin.getline(dish.name, 90);
        cout << "Введите тип рецепта (1 - первое, 2 - второе, 3 - десерт, 4 - напиток): ";
        problem = true;
        cin >> iche;
        while(problem){
            switch (iche) {
                case 1:
                    strcpy(dish.type, "первое");
                    dish.typenum = 1;
                    problem = false;
                    break;
                case 2:
                    strcpy(dish.type, "второе");
                    dish.typenum = 2;
                    problem = false;
                    break;
                case 3:
                    strcpy(dish.type, "десерт");
                    dish.typenum = 3;
                    problem = false;
                    break;
                case 4:
                    strcpy(dish.type, "напиток");
                    problem = false;
                    dish.typenum = 4;
                    break;
                default:
                    cout << "no\n";
                    cin >> iche;
                    break;
            }
            
        }
        cout << "Введите калории рецепта: ";
        cin >> dish.kall;
        cout << "Введите время приготовления рецепта: ";
        cin >> dish.time;
        cout << "Введите описание рецепта: ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin.getline(dish.description, 190);
        
        fwrite(&dish, sizeof(Recipe), 1, file);
    }
    
    fclose(file);
}

void sort_for_print(Recipe *dishes, int num){
    for (int i = 0; i < num - 1; ++i) {
        for (int j = 0; j < num - i - 1; ++j) {
            if (dishes[j].typenum > dishes[j + 1].typenum) {
                Recipe temp = dishes[j];
                dishes[j] = dishes[j + 1];
                dishes[j + 1] = temp;
            }
            }
        }
    
    for(int i = 0; i<num-1; i++){
        for(int j = 0; j<num-i-1; j++){
            if((dishes[j].typenum == dishes[j+1].typenum)&&(strcmp(dishes[j].name, dishes[j+1].name)>0)){
                Recipe temp = dishes[j];
                dishes[j] = dishes[j + 1];
                dishes[j + 1] = temp;
                break;
            }
        }
    }
}

void bubblesort(Recipe *dishes, int num){
    for(int i = 0; i < num-1; i++){
        for(int j = 0; j < num-i-1; j++){
            if(strcmp(dishes[j].name, dishes[j+1].name)>0){
                Recipe temp = dishes[j];
                dishes[j] = dishes[j+1];
                dishes[j+1] = temp;
            }
        }
    }
}

int partition(Recipe *dishes, int start, int end)
{
    // Выбираем крайний правый элемент в качестве опорного элемента массива
    int pivot = dishes[end].kall;
    int pIndex = start;
 
    for (int i = start; i < end; i++)
    {
        if (dishes[i].kall <= pivot)
        {
            Recipe temp = dishes[i];
            dishes[i] = dishes[pIndex];
            dishes[pIndex] = temp;
            pIndex++;
        }
    }
 
    Recipe temp = dishes[pIndex];
    dishes[pIndex] = dishes[end];
    dishes[end] = temp;
 
    return pIndex;
}
 
void quicksort(Recipe *dishes, int start, int end)
{
    if (start >= end) {
        return;
    }

    int pivot = partition(dishes, start, end);

    quicksort(dishes, start, pivot - 1);

    quicksort(dishes, pivot + 1, end);
}

void selectionSort(Recipe *dishes, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (dishes[j].time < dishes[minIndex].time) {
                minIndex = j;
            }
        }
        // Обмениваем текущий элемент и минимальный элемент
        int temp = dishes[minIndex].time;
        dishes[minIndex].time = dishes[i].time;
        dishes[i].time = temp;
    }
}

void delEl(FILE *file, char fileName[100]){
    char name[100];

    file = fopen(fileName, "rb");
    if(!file){
        cout << "Open file error!\n";
        return;
    }
    
    int num = countStructs(file);
    
    Recipe *dishes = new Recipe[num];
    
    structRead(file, dishes, num);
    fclose(file);


    file = fopen(fileName, "wb");
    cout << "Введите название рецепта: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(name, 100);
    
    bool delele = false;
    for(int i = 0; i<num; i++){
        if(strcmp(dishes[i].name, name)==0){
            num--;
            dishes[i] = dishes[i+1];
            delele = true;
        }
        if(delele)
            dishes[i]=dishes[i+1];
    }
        
    structWrite(file, dishes, num);
    
    fclose(file);
    delete [] dishes;
}

void edit(FILE *file, char fileName[100]){
    char name[100];

    openFile(file, fileName, "rb");
    
    int num = countStructs(file);
    
    Recipe *dishes = new Recipe[num];
    
    structRead(file, dishes, num);
    
    fclose(file);

    openFile(file, fileName, "wb");
    cout << "Введите название рецепта: ";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.getline(name, 100);
    
    int iche;
    
    for(int i = 0; i<num; i++){
        if(strcmp(dishes[i].name, name)==0){
            cout << "Введите название рецепта: ";
            cin.getline(dishes[i].name, 100);
            cout << "Введите тип рецепта (1 - первое, 2 - второе, 3 - десерт, 4 - напиток): ";
            cin >> iche;
            bool problem = true;
            while(problem){
                switch (iche) {
                    case 1:
                        strcpy(dishes[i].type, "первое");
                        dishes[i].typenum = 1;
                        problem = false;
                        break;
                    case 2:
                        strcpy(dishes[i].type, "второе");
                        dishes[i].typenum = 2;
                        problem = false;
                        break;
                    case 3:
                        strcpy(dishes[i].type, "десерт");
                        dishes[i].typenum = 3;
                        problem = false;
                        break;
                    case 4:
                        strcpy(dishes[i].type, "напиток");
                        problem = false;
                        dishes[i].typenum = 4;
                        break;
                    default:
                        cout << "no\n";
                        cin >> iche;
                        break;
                }
            }
            cout << "Введите калории рецепта: ";
            cin >> dishes[i].kall;
            cout << "Введите время приготовления рецепта: ";
            cin >> dishes[i].time;
            cout << "Введите описание рецепта: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(dishes[i].description, 190);
            
        }
    }
        
    structWrite(file, dishes, num);
    
    fclose(file);
    delete [] dishes;
}

void interpolationSearch(Recipe *dishes, int n, int x, FILE *log) {
    int low = 0, high = n - 1;
    bool problem = true;

    while (low <= high && x >= dishes[low].kall && x <= dishes[high].kall) {

        int pos = low + ((x - dishes[low].kall) * (high - low)) / (dishes[high].kall - dishes[low].kall);

        if (dishes[pos].kall == x) {
            printTitle(log);
            fprintf(stdout, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[pos].name, dishes[pos].type, dishes[pos].time, dishes[pos].kall,dishes[pos].description);
            fprintf(log, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[pos].name, dishes[pos].type, dishes[pos].time, dishes[pos].kall, dishes[pos].description);
            problem = false;
        }

        if (dishes[pos].kall < x) {
            low = pos + 1;
        }

        else {
            high = pos - 1;
        }
    }
    if(problem){
        printTitle(log);
        cout << "not found";
    }
}

void dietprint(FILE* log, FILE *file, char fileName[100]){
    int kal;

    openFile(log, "log.txt", "w");
    openFile(file, fileName, "rb");
    
    int num = countStructs(file);
    
    Recipe *dishes = new Recipe[num];
    
    structRead(file, dishes, num);

    fclose(file);

    cout << "Введите калории: ";
    cin >> kal;
    quicksort(dishes, 0, num-1);
    
    for(int i = 0; i < num; i++) {
        if(dishes[i].kall < kal){
            fprintf(stdout, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[i].name, dishes[i].type, dishes[i].time, dishes[i].kall, dishes[i].description);
            fprintf(log, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[i].name, dishes[i].type, dishes[i].time, dishes[i].kall, dishes[i].description);
        }
    }
    
    delete [] dishes;
}

void linearSearch(FILE *file, FILE* log, Recipe *dishes, int num){
    char name[100];

            cout << "Введите название рецепта: ";
            cin.ignore();
            cin.getline(name, 90);

            printTitle(log);
            for(int i = 0; i<num; i++){
                if(strcmp(dishes[i].name, name)==0){
                    fprintf(stdout, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[i].name, dishes[i].type, dishes[i].time, dishes[i].kall,dishes[i].description);
                    fprintf(file, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[i].name, dishes[i].type, dishes[i].time, dishes[i].kall, dishes[i].description);
                    return;
                }
            }
            cout << "not found";
}

void printForSort(FILE *file, int num, Recipe *dishes){
    for(int i = 0; i < num; i++) {
        fprintf(stdout, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[i].name, dishes[i].type, dishes[i].time, dishes[i].kall, dishes[i].description);
        fprintf(file, "%-15s|\t%-20s\t|%-20d|\t%-10d|\t%-100s\n", dishes[i].name, dishes[i].type, dishes[i].time, dishes[i].kall, dishes[i].description);
    }
}

void printMessage(){
    cout << "\n 1 - добавить рецепт(ы).\n 2 - редактирование записей в файле.\n 3 - Удаление записей из файла.\n\n "
            "4 - сортировки: \n\t4.1 - сортировка и категоризация \n\t4.2 - сортировка пузырьком \n\t4.3 - быстрая сортировка \n\t4.4 - сортировка выбором\n\n"
            "5 - поиски: \n\t5.1 - линейный \n\t5.2 - интерполяционный\n\n"
            "6 - поиск диетического рецепта.\n"
            "7 - вывод меню\n"
            "8 - выйти из программы\n"
            "9 - вывести меню\n";
}

void printop(FILE* log, FILE* file, char fileName[100], int WhatToDo){
    bool isSort = false;

    openFile(file, fileName, "rb");
    openFile(log, "log.txt", "w");

    int num = countStructs(file);
    
    Recipe *dishes = new Recipe[num];
    structRead(file, dishes, num);

    fclose(file);

    switch (WhatToDo)
    {
        case 4:
            sort_for_print(dishes, num);
            isSort = true;
            break;

        case 5:
            bubblesort(dishes, num);
            isSort = true;
            break;

        case 6:
            quicksort(dishes, 0, num-1);
            isSort = true;
            break;

        case 7:
            selectionSort(dishes, num);
            isSort = true;
            break;

        case 8:
            linearSearch(file, log,  dishes, num);
            break;

        case 9:
            int kal;

            cout << "Введите калории рецепта: ";
            cin >> kal;
            quicksort(dishes, 0, num-1);
            interpolationSearch(dishes, num, kal, log);
        }

        if(isSort){
            printTitle(log);
            printForSort(log, num, dishes); 
        }
        fclose(log);
        delete [] dishes;
    
}

int main() {
    int operation;
    int WhatToDo;
    bool isWork = true;
    FILE* file = nullptr;
    FILE* log = nullptr;
    char fileName[100];

    cout << "Enter filename: ";
    cin.getline(fileName, 100);

    openNewFile(file, fileName);
    printMessage();

    while(isWork){
        cin >> operation;
        switch (operation) {
            case 1:
                add(file, fileName);
                break;

            case 2:
                edit(file, fileName);
                break;

            case 3:
                delEl(file, fileName);
                break;

            case 4:
                cin >> WhatToDo;
                switch(WhatToDo){
                case 1:
                //sort for print
                    printop(log, file, fileName, 4);
                    break;

                case 2:
                //bubble sort
                    printop(log, file, fileName, 5);
                    break;
                    
                case 3:
                //quicksort
                    printop(log, file, fileName, 6);
                    break;

                case 4:
                //selection sort
                    printop(log, file, fileName, 7);
                    break;
            }
            break;
                
            case 5:
                cin >> WhatToDo;
                switch (WhatToDo){
                    case 1:
                    //linear search
                        printop(log, file, fileName, 8);
                        break;
                
                    case 2:
                    //interpolated sort
                        printop(log, file, fileName, 9);
                        break;
                }
                break;

            case 6:
                dietprint(log, file, fileName);
                break;
            
            case 7:
                printMessage();
                break;

            case 8:
                isWork = false;
                break;

            default:
                printMessage();
                break;
            
        }
    }
    return 0;
}
