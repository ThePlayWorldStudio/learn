#include <iostream>
#include <math.h>
//lab 1  v11
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

    c = pow(y, cbrt(abs(x)))+pow(cos(y), 3)*(abs(x-y)*(1+(pow(sin(z), 2))/sqrt(x+y)))/(exp(x-y)+x/2);

    cout << "ответ: \n" << c << "\n";
    return 0;
}