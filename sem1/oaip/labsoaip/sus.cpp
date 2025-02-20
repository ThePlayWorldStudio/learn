#include <iostream>

using namespace std;

int main(){
    
    int x, i, k, coun;
    cout << "Введите порядок матрицы: ";
    cin >> x;

    int **matrix = new int*[x];
    for (i = 0; i < x; i++)
        matrix[i] = new int[x];

    cout << "Введите матрицу \n";
    for(i = 0; i < x; i++){
        for(k = 0; k < x; k++){
            cin >> matrix[i][k];
        }
    }

    int *sums = new int[2*x+2]{};

    for(i = 0; i < x; i++){
        for(k = 0; k < x; k++){
            sums[i] += matrix[i][k];
            sums[i+x] += matrix[k][i];
        }
    }

    for(i = 0; i < x; i++){
        sums[2*x] += matrix[i][i];
    }
    
    for(i = 0; i < x; i++){
        for(k = 0; k<x; k++){
            if(k + i == x-1)
                sums[2*x+1] += matrix[i][k];
        }
    }

    for(i =0; i<x*2+2; i++){
        if(sums[0]!=sums[i]){
            cout << "обычный квадрат \n\n";
            delete [] matrix;
            delete [] sums;
            return 0;
        }
    }
    cout << "оаоаоаоаоаооаоаоао магия \n\n";
    delete [] matrix;
    delete [] sums;

    return 0;
}
