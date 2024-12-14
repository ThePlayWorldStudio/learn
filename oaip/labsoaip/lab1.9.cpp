#include <iostream>
#include <math.h>
//lab 1  v9
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double x, y, z, c ;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    c = abs(pow(x, y/x)-cbrt(y/x))+(y-x)*(cos(y)-z/(y-x))/(1+pow(y-x, 2));

    cout << "ответ: \n" << c << "\n";
    return 0;
}