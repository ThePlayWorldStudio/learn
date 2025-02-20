#include <iostream>
#include <math.h>
//lab 1  v12
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

    c = pow(2, pow(y, x))+pow(3, x * y)-(y*(atan(z)-M_PI/6))/(abs(x)+(1)/(pow(y, 2)+1));

    cout << "ответ: \n" << c << "\n";
    return 0;
}