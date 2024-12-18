#include <iostream>
#include <stdio.h>
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


void bub(vector<Stud> &list, int num)
{
    Stud num1, num2;

	while(num--)
	{
		bool swapped = false;
		
		for(int i = 0; i < num; i++)
		{
			if(list[i].grade > list[i + 1].grade)
			{
				num1 = list[i];
                num2 = list[i+1];
                list[i+1] = num1;
                list[i] = num2;
                swapped = true;
			}
		}
		
		if(swapped == false)
			break;
	}
}

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

void remove(std::vector<Stud>& v, size_t index) {
    v.erase(v.begin() + index);
}

int main() {
    int req;
    
    cout << "Выберите пункт: \n 1. Создание \n 2. Просмотр \n 3. Добавление \n 4. студенты-отличники \n 5. Редактирование \n 6. Удаление \n 7. Сортировка \n 8. Выйти:\n";
    cin >> req;
    switch (req) {
        case 1:{
            FILE *fiel = fopen("stud.txt", "w");
            cout << fiel;
            int num;

            cout << "Введите количество студентов: ";
            cin >> num;
            fprintf(fiel, "%d\n", num);

            cr1(num, fiel);

            fclose(fiel);
            break;
        }
        case 2:{
            FILE *fiel = fopen("stud.txt", "r");
            vector <Stud> studs;
            char fio[50], gr[10], charId[10], phys[3], math[3], inf[3], average[5];
            char numy[10]; 
            fscanf(fiel, "%s", numy);
            int num = atoi(numy);
            for (int i = 0; i < num; i++){
                Stud time;
                fscanf(fiel, "%s %s %s %s %s %s %s", charId, time.fio, gr, phys, math, inf, average);
                time.id = atoi(charId);
                time.group = atoi(gr);
                time.grades[0] = atoi(phys);
                time.grades[1] = atoi(math);
                time.grades[2] = atoi(inf);
                time.grade = atof(average);

                studs.push_back(time);
            }
            
            for(int i = 0; i < num; i++){
                cout << studs[i].id << " " << studs[i].fio << " " << studs[i].group << " phys: " << studs[i].grades[0] << " math: " << studs[i].grades[1] << " inf: " << studs[i].grades[2] << " average: " << studs[i].grade << endl;
            }

            fclose(fiel);
            break;
        }
        case 3:{
            FILE *fiel = fopen("stud.txt", "r");
            vector <Stud> studs;
            char fio[50], gr[10], charId[10], phys[3], math[3], inf[3], average[5];
            char numy[10]; 
            fscanf(fiel, "%s", numy);
            int num1;
            num1 = atoi(numy);
            for (int i = 0; i < num1; i++){
                Stud time;
                fscanf(fiel, "%s %s %s %s %s %s %s", charId, time.fio, gr, phys, math, inf, average);
                time.id = atoi(charId);
                time.group = atoi(gr);
                time.grades[0] = atoi(phys);
                time.grades[1] = atoi(math);
                time.grades[2] = atoi(inf);
                time.grade = atof(average);

                studs.push_back(time);
            }
            fclose(fiel);
            FILE *fiel2 = fopen("stud.txt", "w");
            int num2;
            cout << "Введите количество студентов: ";
            cin >> num2;

            for(int i = 0; i < num2; i++){
                char fio[50];
                int group, gradem, gradef, gradei;
                float grade;

                Stud time;

               cout << "Введите ФИО студента: ";
                cin >> time.fio;

                cout << "введите номер группы: ";
               cin >> group;

               cout << "введите оценку по физике: ";
               cin >> gradef;
        
              cout << "введите оценку по математике: ";
               cin >> gradem;
        
              cout << "введите оценку по информатике: ";
              cin >> gradei;
        
             grade = (gradef + gradem + gradei)/3.;

                time.id = num2+i+1;
                time.group = group;
                time.grades[0] = gradef;
                time.grades[1] = gradem;
                time.grades[2] = gradei;
                time.grade = grade;
                // time.fio = fio;

                studs.push_back(time);
            }
            fprintf(fiel2, "%d\n", num1+num2);
            for(int i = 0; i < num1+num2; i++){
                fprintf(fiel2, "%d %s %6d %d %d %d %.1f\n", i, studs[i].fio, studs[i].group, studs[i].grades[0], studs[i].grades[1], studs[i].grades[2], studs[i].grade);
            }
            fclose(fiel2);
            break;
        }
        case 4:{
            FILE *fiel = fopen("stud.txt", "rw");
            vector <Stud> studs;
            char fio[50], gr[10], charId[10], phys[3], math[3], inf[3], average[5];
            char numy[10]; 
            fscanf(fiel, "%s", numy);
            int num = atoi(numy);
            for (int i = 0; i < num; i++){
                fscanf(fiel, "%s %s %s %s %s %s %s", charId, fio, gr, phys, math, inf, average);
                Stud time;
                time.id = atoi(charId);
                time.group = atoi(gr);
                time.grades[0] = atoi(phys);
                time.grades[1] = atoi(math);
                time.grades[2] = atoi(inf);
                time.grade = atof(average);

                studs.push_back(time);
            }
            
            for(int i = 0; i < num; i++){
                if(studs[i].grade >= 9.f)
                    cout << studs[i].id << " " << studs[i].fio << " " << studs[i].group << " phys: " << studs[i].grades[0] << " math: " << studs[i].grades[1] << " inf: " << studs[i].grades[2] << " average: " << studs[i].grade << endl;
            }

            fclose(fiel);
            break;
        }
        case 5:{
            FILE *fiel = fopen("stud.txt", "r");
            vector <Stud> studs;
            char fio[50], gr[10], charId[10], phys[3], math[3], inf[3], average[5];
            char numy[10]; 
            fscanf(fiel, "%s", numy);
            int num1;
            num1 = atoi(numy);
            for (int i = 0; i < num1; i++){
                Stud time;
                fscanf(fiel, "%s %s %s %s %s %s %s", charId, time.fio, gr, phys, math, inf, average);
                time.id = atoi(charId);
                time.group = atoi(gr);
                time.grades[0] = atoi(phys);
                time.grades[1] = atoi(math);
                time.grades[2] = atoi(inf);
                time.grade = atof(average);


                studs.push_back(time);
            }
            fclose(fiel);

            int idt;
            cout << "Введите id: ";
            cin >> idt;

        cout << "Введите ФИО студента: ";
        cin >> studs[idt].fio;

        cout << "введите номер группы: ";
        cin >> studs[idt].group;
        
        cout << "введите оценку по физике: ";
        cin >> studs[idt].grades[0];
        
        cout << "введите оценку по математике: ";
        cin >> studs[idt].grades[1];
        
        cout << "введите оценку по информатике: ";
        cin >> studs[idt].grades[2];
        
        studs[idt].grade = (studs[idt].grades[0] + studs[idt].grades[1] + studs[idt].grades[2])/3.;
        
        FILE *fiel2 = fopen("stud.txt", "w");

        fprintf(fiel2, "%d\n", studs.size());
            for(int i = 0; i < studs.size(); i++){
                fprintf(fiel2, "%d %s %6d %d %d %d %.1f\n", i, studs[i].fio, studs[i].group, studs[i].grades[0], studs[i].grades[1], studs[i].grades[2], studs[i].grade);
            }
            fclose(fiel2);
            break;
        }
        case 6:{
            FILE *fiel = fopen("stud.txt", "r");
            vector <Stud> studs;
            char fio[50], gr[10], charId[10], phys[3], math[3], inf[3], average[5];
            char numy[10]; 
            fscanf(fiel, "%s", numy);
            int num1;
            num1 = atoi(numy);
            for (int i = 0; i < num1; i++){
                Stud time;
                fscanf(fiel, "%s %s %s %s %s %s %s", charId, time.fio, gr, phys, math, inf, average);
                time.id = atoi(charId);
                time.group = atoi(gr);
                time.grades[0] = atoi(phys);
                time.grades[1] = atoi(math);
                time.grades[2] = atoi(inf);
                time.grade = atof(average);


                studs.push_back(time);
            }
            fclose(fiel);

            int idt;
            cout << "Введите id: ";
            cin >> idt;
            remove(studs, idt);
        
            FILE *fiel2 = fopen("stud.txt", "w");
            fprintf(fiel2, "%d\n", studs.size());
            for(int i = 0; i < studs.size(); i++){
                fprintf(fiel2, "%d %s %6d %d %d %d %.1f\n", i, studs[i].fio, studs[i].group, studs[i].grades[0], studs[i].grades[1], studs[i].grades[2], studs[i].grade);
            }
            fclose(fiel2);
            break;
        }
        case 7:{

            FILE *fiel = fopen("stud.txt", "r");
            vector <Stud> studs;
            char fio[50], gr[10], charId[10], phys[3], math[3], inf[3], average[5];
            char numy[10]; 
            fscanf(fiel, "%s", numy);
            int num1;
            num1 = atoi(numy);
            for (int i = 0; i < num1; i++){
                Stud time;
                fscanf(fiel, "%s %s %s %s %s %s %s", charId, time.fio, gr, phys, math, inf, average);
                time.id = atoi(charId);
                time.group = atoi(gr);
                time.grades[0] = atoi(phys);
                time.grades[1] = atoi(math);
                time.grades[2] = atoi(inf);
                time.grade = atof(average);


                studs.push_back(time);
            }
            fclose(fiel);

            bub(studs, studs.size());

            for(int i = 0; i < studs.size(); i++){
                cout << studs[i].id << " " << studs[i].fio << " " << studs[i].group << " phys: " << studs[i].grades[0] << " math: " << studs[i].grades[1] << " inf: " << studs[i].grades[2] << " average: " << studs[i].grade << endl;
            }
        }
        default:
            break;
        }
    return 0;
}
