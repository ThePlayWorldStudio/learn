# Расчётная работа.

## Тема работы
Тема работы - основы теории графов, базовые алгоритмы на графах.

## Цель работы
- Ознакомиться с понятием графа.
- Ознакомится с основными типами графов.
- Ознакомиться с различными способами представления графов.
- Научиться решать теоретико-графовые задачи.

  ## Задачи
- Необходимо разработать и реализовать программу на С/С++, которая решает выданную преподавателем теоретико-графовую задачу и соответствует следующим требованиям:
    - Если преподаватель указал определенную структуру данных для представления графа, то в программе должна быть использована именно эта структура данных.
    - Использование глобальных переменных в программе недопустимо.
    - При своем запуске программа должна в автоматическом режиме стартовать 5 разнообразных примеров решения задачи и выводить результаты работы на консоль.
    - В программе должна оптимальным образом использоваться возможность языка программирования С/С++ по созданию функций.

 ## Вариант
 4.6 - Найти конденсированный граф для орграфа.

 ## Основные понятия

 `Граф` - математическая абстракция реальной системы любой природы, объекты которой обладают парными связями.

`Ориентированный граф (кратко орграф)` —  граф, рёбрам которого присвоено направление.

`Матрица инцидентности` - одна из форм представления графа, в которой указываются связи между инцидентными элементами графа (ребро(дуга) и вершина). Столбцы матрицы соответствуют ребрам, строки — вершинам. Ненулевое значение в ячейке матрицы указывает связь между вершиной и ребром (их инцидентность).

`Матрица смежности` - это вид представления графа в виде матрицы, когда пересечение столбцов и строк задаёт дуги.

`Компонента сильной связности орграфа` - его максимальная по включению сильно связный подграф. 

`Область сильной связности` - множество вершин компонентов сильной связности.

# Алгоритм решения

Инициализация: Создаем счетчик времени и стек для вершин.
1. Обход в глубину (DFS): Начинаем обход с любой непосещенной вершины. Для каждой вершины:
Помечаем ее посещенной, присваиваем ей метку времени и добавляем в стек.
Исследуем всех соседей. Если сосед не посещен, продолжаем обход в глубину.
Если сосед уже в стеке, обновляем метку времени текущей вершины.
2. Образование компонент: После завершения обхода, если текущая вершина является корневой для своей компоненты (ее метка времени равна начальной)
Выталкиваем вершины из стека до текущей, формируя сильную компоненту связности.
Повторение: Повторяем процесс для всех вершин графа.

1. Подключение библиотек и глобальных переменных
Код начинается с подключения стандартных библиотек C++ и объявления глобальных переменных, необходимых для работы алгоритмов:
cpp
```
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

vector<int> disc, low, component;
vector<bool> inStack;
stack<int> st;
int timer = 0;
```
2. Функция для нахождения сильносвязных компонент (SCC)
Функция Scc реализует алгоритм Тарьяна, который находит все сильносвязные компоненты в графе:
cpp
```
void Scc(int v, const vector<vector<int>>& adjMatrix, vector<vector<int>>& sccs) {
    disc[v] = low[v] = ++timer;
    st.push(v);
    inStack[v] = true;

    for (int u = 0; u < adjMatrix.size(); ++u) {
        if (adjMatrix[v][u] != 0) {
            if (disc[u] == -1) {
                Scc(u, adjMatrix, sccs);
                low[v] = min(low[v], low[u]);
            } else if (inStack[u]) {
                low[v] = min(low[v], disc[u]);
            }
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
```
Инициализация времени посещения: Вершина v получает время обнаружения и минимальное время.
Рекурсивное исследование соседей: Проверка каждого соседа вершины v. Если сосед не был посещен, рекурсивно вызывается Scc. Обновляется минимальное время для v.
Определение SCC: Если минимальное время вершины v равно её времени обнаружения, это означает, что вершина v является корнем SCC. Вершины извлекаются из стека и формируется SCC.
3. Функция для построения конденсированного графа
Функция CondGraph собирает рёбра между различными SCC и формирует конденсированный граф:
cpp
```
set<pair<int, int>> edges;

void CondGraph(int V, const vector<vector<int>>& adjMatrix, const vector<vector<int>>& sccs) {
    edges.clear();

    for (int v = 0; v < V; ++v) {
        for (int u = 0; u < adjMatrix.size(); ++u) {
            if (adjMatrix[v][u] != 0 && component[v] != component[u]) {
                edges.insert({component[v], component[u]});
            }
        }
    }
}
```
Очистка данных: Очистка множества рёбер.
Сбор рёбер: Проверка всех вершин и рёбер графа. Если ребро соединяет вершины из разных SCC, оно добавляется в множество.
4. Главная функция main
Главная функция осуществляет ввод данных, преобразование матрицы инцидентности, нахождение SCC, построение конденсированного графа и вывод матрицы инцидентности конденсированного графа:
```
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

    vector<vector<int>> adjMatrix(V, vector<int>(V, 0));
    for (int j = 0; j < E; ++j) {
        int from = -1, to = -1;
        for (int i = 0; i < V; ++i) {
            if (incidenceMatrix[i][j] == -1) from = i;
            if (incidenceMatrix[i][j] == 1) to = i;
        }
        if (from != -1 && to != -1) {
            adjMatrix[from][to] = 1;
        }
    }

    disc.assign(V, -1);
    low.assign(V, -1);
    component.assign(V, -1);
    inStack.assign(V, false);
    vector<vector<int>> sccs;

    for (int i = 0; i < V; ++i) {
        if (disc[i] == -1) {
            Scc(i, adjMatrix, sccs);
        }
    }

    CondGraph(V, adjMatrix, sccs);

    vector<vector<int>> condensedIncidence(sccs.size(), vector<int>(edges.size(), 0));
    int edgeIndex = 0;
    for (auto& edge : edges) {
        condensedIncidence[edge.first][edgeIndex] = -1;
        condensedIncidence[edge.second][edgeIndex] = 1;
        edgeIndex++;
    }

    cout << "Матрица инцидентности конденсированного графа:" << endl;
    for (int i = 0; i < condensedIncidence.size(); ++i) {
        for (int j = 0; j < condensedIncidence[i].size(); ++j) {
            cout << condensedIncidence[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
```
Ввод данных: Ввод количества вершин и рёбер, затем матрицы инцидентности.
Преобразование матрицы инцидентности: Преобразование матрицы инцидентности в матрицу смежности.
Инициализация векторов: Инициализация векторов для алгоритма Тарьяна.
Нахождение SCC: Вызов функции Scc для каждой вершины.
Построение конденсированного графа: Вызов функции CondGraph.
Формирование матрицы инцидентности: Создание и заполнение матрицы инцидентности для конденсированного графа.
Вывод результатов: Вывод матрицы инцидентности конденсированного графа.

## Вывод
В результате выполнения расчётной работы приобрёл следующие навыки:
- изучил основы теории графов
- изучил способы представления графов
- изучил базовые алгоритмы для работы с графами
- изучил базовые алгоритмы работы с векторами в C++

  ## Список литературы

  - https://ru.wikipedia.org/wiki/Алгоритм_Тарьяна
  - https://habr.com/ru/articles/831950/
  - https://ru.wikipedia.org/wiki/Матрица_инцидентности
  - https://graphonline.ru/wiki/Справка/МатрицаИнцидентности
  - https://graphonline.ru
  - https://programforyou.ru/graph-redactor
