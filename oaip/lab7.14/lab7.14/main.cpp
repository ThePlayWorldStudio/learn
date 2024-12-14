#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct Stud
{
    int id;
    char fio[50];
    int group;
    int grades[3];
    float grade;
};


void cr1(int num, FILE *fiel){
    char fio[50];
    int group, gradem, gradef, gradei;
    float grade;
    
    for(int i = 0; i < num; i++){
        cout << "Введите ФИО студента: ";
        cin >> fio;

        cout << "введите номер группы: ";
        cin >> group;
        
        cout << "введите оценку по физике: ";
        cin >> gradef;
        
        cout << "введите оценку по математике: ";
        cin >> gradem;
        
        cout << "введите оценку по информатике: ";
        cin >> gradei;
        
        grade = (gradef + gradem + gradei)/3.;
        
        fprintf(fiel, "%d %s %6d %d %d %d %.1f\n", i, fio, group, gradef, gradem, gradei, grade);
    }

}

void read(FILE *fiel){

    cout << fiel;
}

int main() {
    int req;
    
    cout << "Выберите пункт: \n 1. Создание \n 2. Просмотр \n 3. Добавление \n 4. студенты-отличники \n 5. Редактирование \n 6. Удаление \n Сортировка:\n";
    cin >> req;
    switch (req) {
        case 1:{
            FILE *fiel = fopen("stud.txt", "w");
            int num;
            
            cout << "Введите количество студентов: ";
            cin >> num;

            cr1(num, fiel);

            fclose(fiel);
            break;
        }
        case 2:{
            FILE *fiel = fopen("stud.txt", "r");

            vector <Stud> studs;
            Stud time;
            char fio[50];
            int group, id;
            int grades[3];
            float grade;
            
            int ret = fscanf(fiel, "%d %s %6d %d %d %d %.1f", id, fio, group, grades[0], grades[1], grades[2], grade);

            cout << ret;
            read(fiel);

            fclose(fiel);
            break;
        }
        default:
            break;
    }
    return 0;
}
