#include <iostream>
#include <math.h>
//lab 1  v3
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double x, y, z, v;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    v = (1+pow(sin(x+y), 2))/(x-(2*y)/(1+pow(x, 2)*pow(y, 2)))*pow(x, abs(y))+pow(cos(atan(1/z)), 2);

    cout << "ответ: \n" << v << "\n";
    return 0;
}