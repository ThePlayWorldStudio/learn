#include <iostream>

using namespace std;

int fact(int x){
    int i = x;
    int f = 1;
    while (i>0)
    {
        f *= i;
        i--;
    }
    return f;
}
int frac(int x, int f){
    if(x!=0)
        f *= x;
    if(x>0){
        return frac(x-1, f);
    }
    else{
        return f;
    }
}

int main(){
    int n, k;
    int f = 1;
    cout << "Введите n: ";
    cin >> n;
    cout << "Введите k: ";
    cin >> k;
    cout << "Ответ: " << fact(n)/(fact(k)*fact(n-k)) << "\n";
    cout << "Ответ факториал: " << frac(n, f)/(frac(k, f)*frac(n-k, f)) << "\n\n";
    return 0;
}