#include <iostream>
#include <math.h>
//lab 1  v6
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double x, y, z, b, b1, b2, b3, b4, b5;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    b1 = cbrt(x)+pow(x, y+2.);
    b2 = sqrt(10.*b1);
    b3 = pow(asin(z), 2.);
    b4 = abs(x-y);
    b5 = b3-b4;
    b = b2*b5;
    // b = sqrt(10*(cbrt(x)+pow(x, y+2)))*(pow(asin(z), 2)-abs(x-y));

    cout << "ответ: \n" << b << "\n";
    return 0;
}