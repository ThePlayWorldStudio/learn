#include <iostream>
#include <math.h>

using namespace std;

double min(double num1, double num2){
    if(num1 < num2) return num1;
    if(num2 < num1) return num2;
}

double max(double num1, double num2){
    if(num1 > num2) return num1;
    if(num2 > num1) return num2;
}

int main()
{
    double x, y;

    cout << "Введите x \n";
    cin >> x;

    cout << "введите y \n";
    cin >> y;

    if(y>= 0){
        if(x>=0)
            cout << max(x, y+sqrt(x)) << "\n ";
        else
            cout << "x не может быть меньше 0 \n";
    }if(x<0) cout << min(x, y) + pow(sin(x), 2) - pow(cos(y), 2) << "\n"; 
    else cout << 0.5*x+exp(y) << "\n \n";

    return 0;
}
