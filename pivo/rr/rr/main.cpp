#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> condensedAdj;
vector<int> disc, low, component;
vector<bool> inStack;
stack<int> st;
int timer = 0;

// Функция для нахождения сильносвязных компонент (алгоритм Тарьяна)
void Scc(int v, vector<vector<int>>& sccs) {
    disc[v] = low[v] = ++timer;
    st.push(v);
    inStack[v] = true;

    for (int u : adj[v]) {
        if (disc[u] == -1) {
            Scc(u, sccs);
            low[v] = min(low[v], low[u]);
        } else if (inStack[u]) {
            low[v] = min(low[v], disc[u]);
        }
    }

    if (low[v] == disc[v]) {
        vector<int> scc;
        while (true) {
            int u = st.top();
            st.pop();
            inStack[u] = false;
            scc.push_back(u);
            component[u] = sccs.size();
            if (u == v) break;
        }
        sccs.push_back(scc);
    }
}

// Построение конденсированного графа
set<pair<int, int>> edges;
void CondGraph(int V, const vector<vector<int>>& sccs) {
    edges.clear(); // Очистка предыдущих данных

    for (int v = 0; v < V; ++v) {
        for (int u : adj[v]) {
            if (component[v] != component[u]) {
                edges.insert({component[v], component[u]});
            }
        }
    }

    condensedAdj.resize(sccs.size());
    for (auto& edge : edges) {
        condensedAdj[edge.first].push_back(edge.second);
    }
}

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(E, 0));
    cout << "Введите матрицу инцидентности (вершины исходят из -1, входят в +1):" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < E; ++j) {
            cin >> graph[i][j];
        }
    }

    adj.resize(V);
    for (int j = 0; j < E; ++j) {
        int from = -1, to = -1;
        for (int i = 0; i < V; ++i) {
            if (graph[i][j] == -1) from = i;
            if (graph[i][j] == 1) to = i;
        }
        if (from != -1 && to != -1) {
            adj[from].push_back(to);
        }
    }

    disc.assign(V, -1);
    low.assign(V, -1);
    component.assign(V, -1);
    inStack.assign(V, false);
    vector<vector<int>> sccs;

    for (int i = 0; i < V; ++i) {
        if (disc[i] == -1) {
            Scc(i, sccs);
        }
    }

    // Построение конденсированного графа
    CondGraph(V, sccs);

    // Формирование матрицы инцидентности для конденсированного графа
    vector<vector<int>> condensedIncidence(condensedAdj.size(), vector<int>(edges.size(), 0));
    int edgeIndex = 0;
    for (auto& edge : edges) {
        condensedIncidence[edge.first][edgeIndex] = -1;
        condensedIncidence[edge.second][edgeIndex] = 1;
        edgeIndex++;
    }

    // Вывод матрицы инцидентности конденсированного графа
    cout << "Матрица инцидентности конденсированного графа:" << endl;
    for (int i = 0; i < condensedIncidence.size(); ++i) {
        for (int j = 0; j < condensedIncidence[i].size(); ++j) {
            cout << condensedIncidence[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
