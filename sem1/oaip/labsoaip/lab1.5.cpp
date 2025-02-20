#include <iostream>
#include <math.h>
//lab 1  v5
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double x, y, z, a;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    a = log(pow(y, -sqrt(abs(x))))*(x-y/2)+pow(sin(atan(z)), 2);

    cout << "ответ: \n" << a << "\n";
    return 0;
}