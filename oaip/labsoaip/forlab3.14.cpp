#include <iostream>
#include <cmath>

using namespace std;

double funcY(double numx){
    return (exp(numx) - exp(-1 * numx)) / 2;
}

double funcS(double numx, double numk){
    return (numx * numx) / (2 * numk) / (2 * numk + 1);
}

int main()
{
    double x, a, b, h, Y, S, bsum;
    double eps = 0.0001;
    int k, counter;
    cout << "Введите a: ";
    cin >> a;
    cout << "\n";
    cout << "Введите b: ";
    cin >> b;
    cout << "\n";
    cout << "Введите h: ";
    cin >> h;
    cout << "\n";

    for(x = a; x <= b; x+=h){
        S = x;
        Y = funcY(x);
        bsum = x;
        for(k = 1; abs(S - Y) >= eps; k++){ 
            bsum *= funcS(x, k);
            S += bsum;
        }
        printf("итерация: %d \t x: %7.7f \t S(x): %7.7f \t Y(x): %7.7f \t |S(x)-Y(x)|: %7.7f \n", k, x, S, Y, fabs(S-Y));    
    }
    return 0;
}
