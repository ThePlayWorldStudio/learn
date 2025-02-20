#include <iostream>
#include <cmath>

using namespace std;


double funcS(double numx, double numy, int k, double sum, double bsum){
    if (k == 0)
        bsum = numx;
    else
        bsum *= (numx * numx) / (2 * k) / (2 * k + 1);
    
    sum += bsum;
    
    return (fabs(sum - numy) < 0.00001) ? sum : funcS(numx, numy, k + 1, sum, bsum);
}

double funcY(double numx){
    return (exp(numx) - exp(-1 * numx)) / 2;
}

int main()
{
    double a, b, h;
    double fact = 1.;
    cout << "Введите a: ";
    cin >> a;
    cout << "\n";
    cout << "Введите b: ";
    cin >> b;
    cout << "\n";
    cout << "Введите h: ";
    cin >> h;
    cout << "\n";
    for(double x = a; x <= b; x+=h){
        double Y = funcY(x);
        double S = funcS(x, Y, 0, 0, 0);
        printf("x: %7.2f \t S(x): %7.7f \t Y(x): %7.7f \t |S(x)-Y(x)|: %7.7f \n", x, S, Y, fabs(S-Y));
    }
    return 0;
}
