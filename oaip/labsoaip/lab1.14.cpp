#include <iostream>
#include <math.h>
//lab 1  v14 me

using namespace std;

int main(){
    double g, x, y, z;
    cout << "введите x \n";
    cin >> x;
    cout << "введите y \n";
    cin >> y;
    cout << "введите z \n";
    cin >> z;

    g = pow(y, x+1.0)/(cbrt(abs(y-2.0))+3.0) + (x+y/2.0)/(2.0*abs(x+y))*pow(x+1.0, -1.0/sin(z));

    cout << "ответ: \n" << g << "\n";
    return 0;
}
