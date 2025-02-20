#include <iostream>

using namespace std;

int main() {
    int col, i;
//    cout << "введите количество символов: \n";
//    cin >> col;
//
//    if (col < 20) {
//        cout << "Количество символов должно быть не менее 20!\n";
//        return 1;
//    }

    char str[100]{};

    cout << "введите строку (не менее 20 символов): \n";
    cin.getline(str, 100);
    col=strlen(str);

    cout << "\n от 5 символа до 15: \n";
    for (i = 4; i < 16 && str[i] != '\0'; i++) {
        cout << str[i];
    }
    
    
    for(i = col - 1; i > 0; i--){
        if(str[i] == ' '){
            break;
        }
    }
    
    cout << "\n от последнего пробела: \n";
    for(; i < col; i++){
        cout << str[i];
    }
    cout << "\n";
    

    return 0;
}
