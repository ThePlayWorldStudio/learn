#include <iostream>

using namespace std;

float drob(float n){
    float znam = 0;
    for(float i = 1; i<=n; i++){
        if(i==1)
            znam = i+0.5;
        else
            znam = i+(1/znam);
    }
    return znam;
}

float drobr(float znam, float n, float i){
    if(i == 1)
        znam = i+0.5;
    else
        znam = i+(1/znam);
    if(i==n)
        return znam;
    else
        return drobr(znam, n, i+1);
}

int main(){
    float n;
    
    cin >> n;
    
    cout << drob(n) << endl;
    cout << drobr(0, n, 1);
    return 0;
}
