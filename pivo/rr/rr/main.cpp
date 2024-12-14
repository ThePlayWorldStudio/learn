#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(){
    
}

int main(){
    int x, y, req, i, j;
    stack <int> stas;
    
    vector<vector<int>> graph;
    vector<int> tv;
    
    cout << "Введите количество ребёр: ";
    cin >> x;
    
    cout << "Введите количество рёбер графа: ";
    cin  >> y;
    
    cout << "Введите граф: ";
    for(i = 0; i < y; i++){
        for(j = 0; j < x; j++){
            cin >> req;
            tv.push_back(req);
        }
        graph.push_back(tv);
        tv.erase(tv.begin(), tv.end());
    }
    
    for(i = 0; i < y; i++){
        for(j = 0; j < x; j++){
            cout << graph[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}
