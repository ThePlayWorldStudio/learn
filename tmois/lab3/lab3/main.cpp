#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(){
    vector< pair<int, int> > Rsoot1;
    vector<int> soot1[2];
    vector< pair<int, int> > Rsoot2;
    vector<int> soot2[2];
    
    int n, i, f, s, coun, j;
    
    for(i = 0; i < 2; i++){
        cout << "Введите мощность " << i+1 << " множества: ";
        cin >> n;
        cout << "Введите элементы " << i+1 << " множества: ";
        for(s = 0; s < n ; s++){
            cin >> f;
            soot1[i].emplace_back(f);
        }
    }
    
    cout << "введите мощность 1 графика: ";
    cin >> n;
    cout << "введите пары: ";
    for(i = 0; i < n; i++){
        cin >> f >> s;
        Rsoot1.emplace_back(f, s);
    }
    
    for(i = 0; i < 2; i++){
        cout << "Введите мощность " << i+1 << " множества: ";
        cin >> n;
        cout << "Введите элементы " << i+1 << " множества: ";
        for(s = 0; s < n ; s++){
            cin >> f;
            soot2[i].emplace_back(f);
        }
    }
    
    cout << "введите мощность 2 графика: ";
    cin >> n;
    cout << "введите пары: ";
    for(i = 0; i < n; i++){
        cin >> f >> s;
        Rsoot2.emplace_back(f, s);
    }
    
    cout << "Выберите операцию \n 1. Объединение \n 2. Пересечение \n 3. Разность \n 4. Инверсия \n ";
    cin >> s;
    
    switch (s) {
        case 1:{
            //union
            vector< pair<int, int> > Runion;
            vector<int> Union[2];
            
            for(i = 0; i < Rsoot1.size(); i++){
                Runion.emplace_back(pair<int, int>(Rsoot1[i].first, Rsoot1[i].second));
            }
            
            cout << "Объединение: \n";
            
            for(i = 0; i < Rsoot2.size(); i++){
                coun = 0;
                for(f = 0; f < Runion.size(); f++){
                    if(Rsoot2[i] == Runion[f]){
                        ++coun;
                    }
                }
                if(coun==0){
                    Runion.emplace_back(pair<int , int>(Rsoot2[i].first, Rsoot2[i].second));
                }
            }
            
            for(j = 0; j < 2; j++){
                cout << ", { ";
                for(i = 0; i < soot1[j].size(); i++){
                    Union[j].emplace_back(soot1[j][i]);
                }
                
                for(i = 0; i < soot2[j].size(); i++){
                    coun = 0;
                    for(f = 0; f < Union[j].size(); f++){
                        if(soot2[j][i] == Union[j][f]){
                            ++coun;
                        }
                    }
                    if(coun==0){
                        Union[j].emplace_back(soot2[j][i]);
                    }
                }
                for(i = 0; i < Union[j].size(); i++){
                    cout << Union[j][i] << " ";
                }
                cout << "} ";
            }
            
            cout << "{ ";
            for(i = 0; i < Runion.size(); i++){
                cout << " < " << Runion[i].first << " " << Runion[i].second << " > ";
            }
            cout << "} ";
            break;
        }
        case 2:{
            //union
            vector< pair<int, int> > Rcross;
            vector<int> Cross[2];
            
            for(i = 0; i < Rsoot1.size(); i++){
                for(j = 0; j < Rsoot2.size(); j++){
                    if(Rsoot2[j] == Rsoot1[i]){
                        Rcross.emplace_back(pair<int, int>(Rsoot1[i]));
                    }
                }
            }
            
            cout << "Пересечение: \n";
            
            
            
            for(f = 0; f < 2; f++){
                cout << "{ ";
                for(i = 0; i < soot1[f].size(); i++){
                    for(j = 0; j < Rsoot2.size(); j++){
                        if(soot2[f][j] == soot1[f][i]){
                            Cross[f].emplace_back(soot1[f][i]);
                        }
                    }
                }
                for(i = 0; i < Cross[f].size(); i++){
                    cout << Cross[f][i] << " ";
                }
                cout << "} ";
            }
            cout << "{ ";
            for(i = 0; i < Rcross.size(); i++){
                cout << " < " << Rcross[i].first << " " << Rcross[i].second << " > ";
            }
            cout << "} ";
            break;
        }
        case 3:{
            vector< pair<int, int> > Rminus;
            vector<int> minus[2];
            
            for(i = 0; i < Rsoot1.size(); i++)
            {
                for(j=0; j<Rsoot2.size(); j++){
                if(Rsoot1[i]==Rsoot2[j]){
                        break;
                    }
                    if(j==Rsoot2.size()-1){
                        Rminus.emplace_back(pair<int, int>(Rsoot1[i].first, Rsoot1[i].second));
                    }
                }
            }
            
            for(f = 0; f < 2; f++){
                for(i = 0; i < soot1[f].size(); i++)
                {
                    for(j=0; j<soot2[f].size(); j++){
                        if(soot1[f][i]==soot2[f][j]){
                            break;
                        }
                        if(j==soot2[f].size()-1){
                            minus[f].push_back(soot1[f][i]);
                        }
                    }
                }
            }
            
            for(f= 0; f < 2; f++){
                cout << "{ ";
                for(i = 0; i < minus[f].size(); i++){
                    cout << minus[f][i] << " ";
                }
                cout << " } ";
            }
            
            cout << "{ ";
            for(i = 0; i < Rminus.size(); i++){
                cout << "< " << Rminus[i].first << " " << Rminus[i].second << " > ";
            }
            cout << " }";
        
            break;
            }
        case 4:{
            vector< pair<int, int> > Rinv;
            vector<int> inv[2];
            
            for(i = 0; i < soot1[0].size(); i++){
                inv[1].emplace_back(soot1[0][i]);
            }
            for(i = 0; i < soot1[1].size(); i++){
                inv[0].emplace_back(soot1[1][i]);
            }
            for(i = 0; i < Rsoot1.size(); i++){
                swap(Rsoot1[i].first,Rsoot1[i].second);
                Rinv.emplace_back(pair<int, int>(Rsoot1[i].first, Rsoot1[i].second));
            }
            
            for(f= 0; f < 2; f++){
                cout << "{ ";
                for(i = 0; i < inv[f].size(); i++){
                    cout << inv[f][i] << " ";
                }
                cout << " } ";
            }
            cout << "{ ";
            for(i = 0; i < Rinv.size(); i++){
                cout << "< " << Rinv[i].first << " " << Rinv[i].second << " > ";
            }
            cout << " }";
            
            break;
        }
        case 5:{
            vector< pair<int, int> > Rcomp;
            vector<int> comp[2];
            
            for(i = 0; i < soot1[0].size(); i++){
                comp[0].emplace_back(soot1[0][i]);
            }
            for(i = 0; i < soot2[1].size(); i++){
                comp[1].emplace_back(soot2[1][i]);
            }
            
            for(i = 0; i < Rsoot1.size(); i++){
                for(j = 0; j < Rsoot2.size(); j++){
                            if(Rsoot1[i].second == Rsoot2[j].first){
                                Rcomp.emplace_back(Rsoot1[i].first, Rsoot2[j].second);
                            }
                        }
                    }
            
            for(f= 0; f < 2; f++){
                cout << "{ ";
                for(i = 0; i < comp[f].size(); i++){
                    cout << comp[f][i] << " ";
                }
                cout << " } ";
            }
            cout << "{ ";
            for(i = 0; i < Rcomp.size(); i++){
                cout << "< " << Rcomp[i].first << " " << Rcomp[i].second << " > ";
            }
            cout << " }";
            break;
        }
        default:
            break;
    }
    
    return 0;
}
