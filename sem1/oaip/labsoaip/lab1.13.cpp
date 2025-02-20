#include <iostream>
#include <math.h>
//lab 1  v13
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

    c = (pow(y+cbrt(x-1), 1./4.))/(abs(x-y)*(pow(sin(z), 2)+tan(z)));

    cout << "ответ: \n" << c << "\n";
    return 0;
}