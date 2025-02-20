#include <iostream>
#include <math.h>
#include <string>

//using namespace std;

int pr(string whch){
    double vvod;
    std::cout << "vvedite " << whch;
    std::cin >> vvod;
    return vvod;
}

int main() 
{
    double x, y, z, b, c, h;
    x = pr('x');
    std::cout << x;
    return 0;
}