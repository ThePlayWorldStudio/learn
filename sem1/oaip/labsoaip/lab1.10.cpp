#include <iostream>
#include <math.h>
//lab 1  v10
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

    c = pow(2., -x)*sqrt(x+pow(abs(y), 1./4.))*cbrt(exp(x-1/sin(z)));

    cout << "ответ: \n" << c << "\n";
    return 0;
}