#include <iostream>
#include <math.h>
//lab 1  v7 fs


using namespace std;

int main(){
    double x, y, z, c, h1, h2, h3, h4, h5, h6;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    h1 = fabs(x-y);
    h2 = pow(x, 2);
    h3 = 5.*atan(x);
    h4 = 1./4.*acos(x);
    h5 = x+3*h1+h2;
    h6 = h1*z+h2;

    c = h3-h4*h5/h6;

    cout << "ответ: \n" << c << "\n \n";
    return 0;
    //0.1722 6.33 3.25e-4
}