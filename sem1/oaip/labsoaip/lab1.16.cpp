#include <iostream>
#include <math.h>
//lab 1  v16
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

    c = cbrt(pow(x, 6)+pow(log(y), 2))+(exp(abs(x-y))*pow(abs(x-y), x+y))/(atan(x)+atan(z));

    cout << "ответ: \n" << c << "\n";
    return 0;
}