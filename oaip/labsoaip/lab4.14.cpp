#include <iostream>

using namespace std;

int main(){
    int mass[100], n, k, coun, maxcoun;
    double maxval;

    cout << "Введите количество элементов массива: ";
    cin >> n;

    int i;
    cout << "Введите элементы массива: ";
    for(i = 0; i < n; i++){
        cin >> mass[i];
    }

    maxval = 0;
    maxcoun = 0;

    for(i = 0; i < n; i++){
        coun = 0;

        for(k = 0; k < n; k++){
            if(mass[i] == mass[k]){
                coun++;
            }
        }

        if(coun > maxcoun || (mass[i] < maxval && coun == maxcoun)){
            maxval = mass[i];
            maxcoun = coun;
        }

    }

    cout << "Наименьшее число " << maxval << ", повторяется " << maxcoun << " раз \n\n";

    return 0;
}