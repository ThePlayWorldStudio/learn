#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

// Глобальные переменные
vector<vector<int>> adj;          // Список смежности графа
vector<vector<int>> condensedAdj; // Список смежности конденсированного графа
vector<int> disc, low, component; // Время обнаружения, минимальное достижимое время, компоненты
vector<bool> inStack;             // Проверка нахождения вершины в стеке
stack<int> st;                    // Стек для алгоритма Тарьяна
int timer = 0;                    // Счетчик времени

// Функция для нахождения сильносвязных компонент (алгоритм Тарьяна)
void tarjanDFS(int v, vector<vector<int>>& sccs) {
    disc[v] = low[v] = ++timer;
    st.push(v);
    inStack[v] = true;

    for (int u : adj[v]) {
        if (disc[u] == -1) {
            tarjanDFS(u, sccs);
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
void buildCondensedGraph(int V, const vector<vector<int>>& sccs) {
    set<pair<int, int>> edges;

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

    vector<vector<int>> incidenceMatrix(V, vector<int>(E, 0));
    cout << "Введите матрицу инцидентности (вершины исходят из -1, входят в +1):" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < E; ++j) {
            cin >> incidenceMatrix[i][j];
        }
    }

    // Построение списка смежности из матрицы инцидентности
    adj.resize(V);
    for (int j = 0; j < E; ++j) {
        int from = -1, to = -1;
        for (int i = 0; i < V; ++i) {
            if (incidenceMatrix[i][j] == -1) from = i;
            if (incidenceMatrix[i][j] == 1) to = i;
        }
        if (from != -1 && to != -1) {
            adj[from].push_back(to);
        }
    }

    // Инициализация глобальных переменных
    disc.assign(V, -1);
    low.assign(V, -1);
    component.assign(V, -1);
    inStack.assign(V, false);
    vector<vector<int>> sccs;

    // Поиск сильносвязных компонент
    for (int i = 0; i < V; ++i) {
        if (disc[i] == -1) {
            tarjanDFS(i, sccs);
        }
    }

    // Построение конденсированного графа
    buildCondensedGraph(V, sccs);

    // Вывод сильносвязных компонент
    cout << "Сильносвязные компоненты:" << endl;
    for (const auto& scc : sccs) {
        for (int v : scc) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Вывод конденсированного графа
    cout << "Конденсированный граф (список смежности):" << endl;
    for (int i = 0; i < condensedAdj.size(); ++i) {
        cout << i << ": ";
        for (int v : condensedAdj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
