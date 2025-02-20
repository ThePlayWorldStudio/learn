#include <iostream>
#include <math.h>
//lab 1  v14
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double t, x, y, z, t1, t2, t3, t4;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    t1 = 2*cos(x - M_PI/6);
    t2 = 0.5+pow(sin(y), 2);
    t3 = pow(z, 2);
    t4 = 3-pow(z, 2)/5;

    t= t1/t2*(1+t3/t4);

    //t = (2*cos(x-M_PI/6))/(0.5+pow(sin(y), 2))*(1+(pow(z, 2))/(3-pow(x,2)/5));

    cout << "ответ: \n" << t << "\n";
    return 0;
}
