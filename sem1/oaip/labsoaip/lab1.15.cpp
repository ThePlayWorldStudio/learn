#include <iostream>
#include <math.h>
//lab 1  v15
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

    c = (pow(x, y+1)+exp(y-1))/(1+x*abs(y-tan(z)))*(1+abs(y-x))+pow(abs(y-x), 2)/2 - pow(abs(y-x),3)/3;

    cout << "ответ: \n" << c << "\n";
    return 0;
}