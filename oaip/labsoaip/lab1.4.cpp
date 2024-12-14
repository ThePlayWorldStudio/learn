#include <iostream>
#include <math.h>
//lab 1  v4
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double x, y, z, w;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    w = pow(abs(cos(x)-cos(y)), 1+2*pow(sin(y), 2))*(1+z+pow(z, 2)/2+pow(z, 3)/3+pow(z, 4)/4);

    cout << "ответ: \n" << w << "\n";
    return 0;
}