#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Максимальное количество вершин в графе
const int MAX_V = 100;

// Часть 1: Представление графа (Список смежности)
// Массив векторов. graph[i] хранит список соседей вершины i.
vector<int> graph[MAX_V];
bool visited[MAX_V]; // Массив для отметки посещенных вершин
int V; // Текущее количество вершин

// Функция для добавления ребра (неориентированного)
void addEdge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u); // Т.к. граф неориентированный
}
void printGraph() {
    cout << "Список смежности графа:" << endl;
    for (int i = 0; i < V; i++) {
        cout << "Вершина " << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

// Часть 2: обход графа (DFS и BFS)

// DFS (рекурсивный) + подсчет вершин
int dfs(int v) {
    visited[v] = true; // Отмечаем вершину
    int count = 1;     // Считаем саму вершину

    // Идем по всем соседям
    for (int i = 0; i < graph[v].size(); i++) {
        int neighbor = graph[v][i];
        if (!visited[neighbor]) {
            count += dfs(neighbor); // Рекурсивно идем дальше
        }
    }
    return count;
}

// BFS + подсчет вершин
int bfs(int start) {
    // Очищаем массив visited перед запуском
    for (int i = 0; i < V; i++) visited[i] = false;

    queue<int> q;
    q.push(start);
    visited[start] = true;
    int count = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        count++; // Считаем текущую вершину

        for (int i = 0; i < graph[v].size(); i++) {
            int neighbor = graph[v][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return count;
}

// Часть 3: применение обходов

// 3.1 Поиск компонент связности
void findComponents() {
    for (int i = 0; i < V; i++) visited[i] = false;
    int compCount = 0;

    cout << "Компоненты связности:" << endl;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            compCount++;
            cout << "Компонента " << compCount << ": ";

            // Запускаем BFS для сбора вершин компоненты
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cout << v << " ";

                for (int j = 0; j < graph[v].size(); j++) {
                    int neighbor = graph[v][j];
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            cout << endl;
        }
    }
}

// 3.2 Кратчайший путь (BFS)
void shortestPath(int start, int end) {
    for (int i = 0; i < V; i++) visited[i] = false;

    vector<int> parent(V, -1); // Массив для запоминания предков
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (v == end) break; // Дошли до цели

        for (int i = 0; i < graph[v].size(); i++) {
            int neighbor = graph[v][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = v; // Запоминаем, откуда пришли
                q.push(neighbor);
            }
        }
    }

    // Восстановление пути
    if (!visited[end]) {
        cout << "Пути из " << start << " в " << end << " нет." << endl;
        return;
    }

    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    cout << "Кратчайший путь (BFS) из " << start << " в " << end << ": ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    // Задаем граф из примера (7 вершин: 0..6)
    V = 7;

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(0, 5);
    addEdge(5, 4);
    addEdge(4, 6);
    addEdge(2, 6); // Пунктирная линия

    // Вывод части 1
    cout << " Часть 1: Представление графа " << endl;
    printGraph(); 

    cout << " Часть 2: Обходы из вершины 0 " << endl;

    // DFS
    for (int i = 0; i < V; i++) visited[i] = false;
    int countDFS = dfs(0);
    cout << "DFS: посещено вершин = " << countDFS << endl;

    // BFS
    int countBFS = bfs(0);
    cout << "BFS: посещено вершин = " << countBFS << endl;

    cout << "\n Часть 3: Применение " << endl;

    // Компоненты связности
    findComponents();

    // Кратчайший путь
    shortestPath(0, 3);

    return 0;
}
