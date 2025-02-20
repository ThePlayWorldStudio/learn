#include <iostream>

using namespace std;

double func(int n){
    double ch = 2;
    double zn = 1;
    double otv = 1;
    for(int i = 1; i <= n; i++){
        otv *= ch/zn;
        if(i%2!=0)
            zn += 2;
        if (i%2==0){
            ch += 2;
        }
    }
    return otv;
}

double recu(int n, double ch, double zn, double otv, int sch){
    otv *= ch/zn;
    if(sch == n)
        return otv;
    if(sch%2!=0)
        zn += 2;
    if (sch%2==0){
        ch += 2;
    }
    return recu(n, ch, zn, otv, sch+1);
}

int main() {
    int n;
    while(1){
        cin >> n;
        if(n%2==0)
            break;
        else
            cout << "Число не четное! \n";
    }
    
    cout << func(n) << "\n";
    
    cout << recu(n, 2, 1, 1, 1) << "\n";
    return 0;
}
