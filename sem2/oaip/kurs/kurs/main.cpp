#include <iostream>



struct Recipe{
    // 1 - первое 2 - второе 3 - десерт 4 - напиток
    int type;
    char name[100];
    int kall;
    int time;
    char description[200];
};

void printMessage(){
    std::cout << "Меню\n 1 - Проверка файла.\n 2 - Просмотр записей из файла.\n 3 - Добавление записей в файл.\n 4 - Редактирование записей в файле.\n 5 - Удаление записей в файле.\n 13 - Выход.\n";
}

int comp(char str1[500], char str2[500]){
    for(int i = 0; i<strlen(str2); i++){
        if(str1[i]!=str2[i]){
            return -1;
        }
    }
    return 0;
}
void checkWork(FILE* file){
    file = fopen("recipes.bin", "r+b");
    if (file == nullptr) {
        std::cout << "Ошибка при открытии файла!\n";
        return;
    }
    fclose(file);
}

void print(FILE* file) {
    file = fopen("recipes.bin", "rb");
    char TYPES[4][15] = {"первое", "второе", "десерт", "напиток"};
    printf("%-20s%-10s%-20s%-20s%-30s\n", "Name", "type", "kal", "time", "description");
    Recipe dish;
    while (fread(&dish, sizeof(Recipe), 1, file)){
        printf("%-10s%-10s%-10d%-10d%-30s\n", dish.name, TYPES[dish.type-1], dish.kall, dish.time, dish.description);
    }
    fclose(file);
}

void write(FILE* file) {
    file = fopen("recipes.bin", "a+b");
    int count;
    std::cout << "Введите количество рецептов: ";
    std::cin >> count;
    Recipe dish;
    for (int i = 0; i < count; i++) {
        std::cout << "Заполните данные " << i + 1 << "-го рецепта:\n";
        
        std::cin.ignore();
        std::cout << "Введите Название: ";
        std::cin.getline(dish.name, 99);
        std::cout << "Введите тип блюда (1 - первое, 2 - второе, 3 - десерт, 4 - напиток): ";
        std::cin >> dish.type;
        std::cout << "Введите время приготовления: ";
        std::cin >> dish.time;
        std::cout << "Введите калорийность: ";
        std::cin >> dish.kall;
        std::cout << "Введите описание: ";
        std::cin.getline(dish.description, 199);
        std::cin.ignore();
    
        fwrite(&dish, sizeof(Recipe), 1, file);
    }
 
    fclose(file);
}


void Edit(FILE* file) {
    file = fopen("recipes.bin", "r+b");
    char find[50];
    std::cin.ignore();
    std::cin.getline(find, 50);
 
    
    
    printf("%-20s%-10s%-10s%-10s%-30s\n", "Название", "тип", "Калорийность", "Время приготовления", "описание");
    Recipe dish;
    while (fread(&dish, sizeof(Recipe), 1, file)) {
        if (comp(dish.name, find) == 0) {
            char TYPES[4][15] = {"первое", "второе", "десерт", "напиток"};
            printf("%-20s%-10s%-10d%-10d%-30s\n", dish.name, TYPES[dish.type-1], dish.kall, dish.time, dish.description);
            // Recipe dish;
            
            std::cin.ignore();
            std::cout << "Введите Название: ";
            std::cin.getline(dish.name, 100);
            std::cout << "Введите тип блюда (1 - первое, 2 - второе, 3 - десерт, 4 - напиток): ";
            std::cin >> dish.type;
            std::cout << "Введите время приготовления: ";
            std::cin >> dish.time;
            std::cout << "Введите калорийность: ";
            std::cin >> dish.kall;
            std::cout << "Введите описание: ";
            std::cin.getline(dish.description, 200);
            std::cin.ignore();
        
            fwrite(&dish, sizeof(Recipe), 1, file);
            fseek(file, -static_cast<long>(sizeof(Recipe)), SEEK_CUR);
            fwrite(&dish, sizeof(Recipe), 1, file);
            break;
        }
    }
    fclose(file);
}


int main() {
    int iChe;
    bool isWork = true;
    FILE* file;
    checkWork(file);
    while(isWork){
        std::cin >> iChe;
        switch (iChe) {
            case 1:{
                checkWork(file);
                break;
            }
            case 2:{
                print(file);
                break;
            }
            case 3:{
                write(file);
                break;
            }
            case 4:{
                Edit(file);
                break;
            }
            case 13:{
                isWork = false;
                break;
            }
            default:{
                // std::cout << "Чё?\n";
                printMessage();
                break;
            }
        }
    }
//    delete file;
    return 0;
}
