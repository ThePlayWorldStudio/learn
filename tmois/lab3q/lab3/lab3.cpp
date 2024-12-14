#include <vector>
#include <utility>
#include <iostream>

using namespace std;

void inputf(int n, int num, vector <int> soot1[]){
    int el;
    for(int i = 0; i < n; i++){
        cin >> el;
        soot1[num].push_back(el);
    }
}

void unitedfr(vector<pair <int, int> > rsoot1, vector<pair <int, int> > rsoot2, vector<pair <int, int> > unitedr){
    for(int j = 0; j < rsoot1.size(); j++){
            for(int h = 0; h < rsoot2.size(); h++){
                if(rsoot1[j] != rsoot2[h]){
                    break;
                }
                if(h == rsoot1.size() - 1){
                    unitedr.push_back(rsoot1[j]);
                }
            }
            for(int h = 0; h < rsoot1.size(); h++){
                if(rsoot2[j] != rsoot1[h]){
                    break;
                }
                if(h == rsoot2.size() - 1){
                    unitedr.push_back(rsoot2[j]);
                }
            }
        }
}

int main(){

    vector <pair<int, int> > rsoot1;

    vector <pair<int, int> > rsoot2;
    
    int n, i, el, sw, j, fir ,sec;

    cout << "Введите мощность соответствия: ";
    cin >> n;

    cout << "Введите пары соответствия: ";

    for(i = 0; i < n; i++){
        cin >> fir >> sec;
        rsoot1.emplace_back(fir, sec);
    }

    cout << "Введите мощность соответствия: ";
    cin >> n;

    cout << "Введите пары соответствия: ";

    for(i = 0; i < n; i++){
        cin >> fir >> sec;
        rsoot1.emplace_back(fir, sec);
    }

    cout << ":";
    cin >> sw;

    switch (sw)
    {
    case 1:{
        // объединение
        vector<pair<int,int> > unitedr;
        unitedfr(rsoot1, rsoot2, unitedr);
        for(i = 0; i < unitedr.size()-1; i++){
            cout << "<" << unitedr[i].first << ' ' << unitedr[i].second << ">, ";
        }
        break;
    }
    case 2:{
        // пересечение
        break;
    }
    case 3:
        {// разность
        break;}
    case 4:{
        // инверсия
        break;
    }
    case 5:{
        // композиция
        break;
    }
    default:
        break;
    }
    return 0;
}
