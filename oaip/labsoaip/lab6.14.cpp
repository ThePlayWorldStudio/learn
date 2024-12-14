#include <iostream>

using namespace std;

int main(){
    int i, cnum;
    int coun = 0;
    int n =100;


    char str[100]{};

    setlocale(LC_ALL,"ru");

    cout << "введите строку (до 100 символов): \n";
    cin.getline(str,100);

    i = 0;
    while(str[i] == ' ')
        ++i;
    ++i;

    for(; i < n; i++){
        // if((str[i-1] == ' ' && str[i] != ' ')||(str[i-1] == '-' && str[i] != ' ')){
        if((str[i-1] == ' ' || str[i-1] == '-')&&str[i]!=' '){
            coun++;
            if(coun%2 == 1){
                str[i] = '?';
            }
        }
    }

    for(i = 0; i < n; i++){
        cout << str[i];
    }
    cout << "\n\n";
    return 0;
}