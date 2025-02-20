#include <iostream>

using namespace std;

int main(){
    int num, i, ref, massnum;
    int c = 0;
    int it = 0;
    cin >> num;
    ref = num;
    while (ref>0){
        ref/=10;
        c++;
    }
    int *mass = new int[c];

    for(i = 0; num>0; i++){
        if(num%10==3 || num%10==6 || num%10==9) {
            mass[i] = num%10;
            it++;
        }
        num /= 10;
    }

    cout << "[ ";
    for(i = 0; i<it; i++){
        if(i != it-1)
            cout << mass[i] << ", ";
        else
            cout << mass[i];
    }
    cout << " ]";
    delete [] mass;
    return 0;
}