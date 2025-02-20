#include <iostream>

using namespace std;

int main(){
    
    int x, y, n, k, i;
    cout << "Введите порядок матрицы: ";
    cin >> x;

    double **matrix = new double*[x];
    for (i = 0; i < x; i++)
        matrix[i] = new double[x];

    y = x;
    cout << "Введите матрицу \n";
    for(n = 0; n < y; n++){
        for(k = 0; k < x; k++){
            cin >> matrix[n][k];
        }
    }

    double sum = 0;
    i = 0;
    for(n = 0; n < y; n++){
        for(k = 0; k < x; k++){
            if(!(k > i - 1 && k < x - i)){
                sum += matrix[n][k];
            }
        }
        i++;
    }

    double tim = 1;
    i = 0;
    for(n = 0; n < y; n++){
        for(k = 0; k < x; k++){
            if(!(k > i - 1 && k < x - i)){
                tim *= matrix[n][k];
            }
        }
        i++;
    }

    cout << "Сумма элементов: " << sum << ", произведение: " << tim << "\n\n";

    return 0;
}