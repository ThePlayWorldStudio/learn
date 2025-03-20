#include <iostream>

using namespace std;

int max(int a, int b){
    return (a>b)? a: b;
}

int compare(int* mass, int n){
    int maxim = mass[0];
    for(int i = 0; i<n-1; i++){
        maxim = max(maxim, mass[i+1]);
    }
    return maxim;
}

int comparer(int* mass, int n, int maxin, int it){
    if(it<n){
        maxin = max(maxin, mass[it]);
        return comparer(mass, n, maxin, it+1);
    }
    else
        return maxin;
}

int main() {
    int n, i, a, maxim;
    cout << "введите кол-во чисел: ";
    cin >> n;
    cout << "введите числа: ";
    int* mass = new int[n];
    for(i = 0; i<n; i++){
        cin >> a;
        mass[i] = a;
    }
    maxim = compare(mass, n);
    cout << maxim << "\n";

    maxim = comparer(mass, n, mass[0], 1);
    cout << maxim << "\n";
    delete [] mass;
    return 0;
}
