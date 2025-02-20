#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(){
    vector<pair<double, double> > graph;
    vector<pair<double, double> > graph2;
    vector<pair<double, double> > compose;
    double  fir, sec, rev;
    int n, k, i, j, sw;

    cout << "Введите мощность графика: ";
    cin >> n;

    cout << "Введите пары графика: ";

    for(i = 0; i < n; i++){
        cin >> fir >> sec;
        graph.emplace_back(fir, sec);
    }

    cout << "Введите операцию, проводимую над графиком: \n\t 1. Инверсия \n\t 2. Композиция \n";
    cin >> sw;
    switch (sw)
    {
    case 1:
        for(i = 0; i < n; i++){
            swap(graph[i].first,graph[i].second);
        }
        cout << "Инверсия: { ";
        for(i = 0; i < n; i++){
            if(i < n-1){
                cout << "<" << graph[i].first << " " << graph[i].second << ">, ";
            }
            else{
                cout << "<" << graph[i].first << " " << graph[i].second << "> ";
            }
        }   
        cout << "} \n\n"; 
        break;
    case 2:
        cout << "Введите мощность второго графика: ";
        cin >> k;

        cout << "Введите пары графика: ";

        for(i = 0; i < k; i++){
            cin >> fir >> sec;
            graph2.emplace_back(fir, sec);
        }

        for(i = 0; i < n; i++){
            for(j = 0; j < k; j++){
                if(graph[i].second == graph2[j].first){
                    compose.emplace_back(graph[i].first, graph2[j].second);
                }
            }
        }

        cout << "Композиция: { ";
        for(i = 0; i < compose.size(); i++){
            if(i < compose.size()-1){
                cout << "<" << compose[i].first << " " << compose[i].second << ">, ";
            }
            else{
                cout << "<" << compose[i].first << " " << compose[i].second << "> ";
            }
        }   
        cout << "} \n\n";
        break;
    default:
        cout << ">:(\n\n";
    }

    return 0;
}