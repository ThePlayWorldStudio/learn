#include <iostream>
#include <math.h>
//lab 1  v14
#define _USE_MATH_DEFINES


using namespace std;

int main(){
    double x, y, z, u;
    cout << "введите x" << "\n";
    cin >> x;
    cout << "введите y" << "\n";
    cin >> y;
    cout << "введите z" << "\n";
    cin >> z;

    u = (cbrt(8+pow(abs(x-y), 2)+1))/(pow(x, 2)+pow(y, 2)+2)-exp(abs(x-y))*pow((pow(tan(z), 2)+1), x);

    cout << "ответ: \n" << u << "\n";
    return 0;
}
