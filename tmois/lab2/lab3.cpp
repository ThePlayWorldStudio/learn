#include <vector>
#include <utility>
#include <iostream>

using namespace std;

int main(){
    vector <int> soot1[2];
    vector <pair<int, int> > rsoot1;
    vector <int> soot2[2];
    vector <pair<int, int> > rsoot2;
    
    int n, i, el, sw, t, fir ,sec, count;

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

        for(i = 0; i<rsoot1.size(); i++)
        {
            unitedr.emplace_back(rsoot1[i].first, rsoot1[i].second);
        }
        for(i = 0; i<rsoot2.size(); i++)
        {
            count = 0;
            for(t=0; t< unitedr.size(); t++){
                if(rsoot2[i].first == unitedr[i].first){
                    ++count;
                }
            }
            if(count==0){
                unitedr.emplace_back(rsoot2[i].first, rsoot2[i].second); 
                t = unitedr.size();
                count = 0;
            }
        }
        for(i = 0; i < unitedr.size(); i++){
            cout << " < " << unitedr[i].first << unitedr[i].second << " > ";
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