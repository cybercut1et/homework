#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring>

using namespace std;

const int MAX_V = 1000; // максимальное количество вершин

// структура для представления ребра
struct Edge {
    int to, rev;
    int cap, flow;
    Edge(int to, int rev, int cap) : to(to), rev(rev), cap(cap), flow(0) {}
};

// список смежности для представления графа
vector<Edge> graph[MAX_V]; // эта конструкция создает вектор, внутри которого MAX_V векторов типа Edge
int level[MAX_V]; // уровни для поиска пути из источника в сток
int start, sink; // источник и сток

// функция для добавления ребра в граф
void add_edge(int from, int to, int cap) {
    graph[from].emplace_back(to, graph[to].size(), cap);
    graph[to].emplace_back(from, graph[from].size() - 1, 0);
}
// используем emplace_back, т. к. push_back сначала создает временный объект
// затем копирует его в вектор, а emplace_back создает объект непосредственно в векторе

// функция для поиска пути из источника в сток с помощью BFS
bool bfs() {
    memset(level, -1, sizeof(level));
    level[start] = 0;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (const Edge& e : graph[v]) {
            int u = e.to;
            if (level[u] == -1 && e.flow < e.cap) {
                level[u] = level[v] + 1;
                q.push(u);
            }
        }
    }

    return level[sink] != -1;
}

// функция для поиска пути и обновления потока
int dfs(int v, int min_cap) {
    if (v == sink)
        return min_cap;

    int flow = 0;
    for (Edge& e : graph[v]) {
        int u = e.to;
        if (level[u] == level[v] + 1 && e.flow < e.cap) {
            int pushed = dfs(u, min(min_cap, e.cap - e.flow));
            e.flow += pushed;
            graph[u][e.rev].flow -= pushed;
            flow += pushed;
        }
    }

    return flow;
}

// функция для нахождения максимального потока (алгоритм Форда-Фалкерсона)
int max_flow() {
    int flow = 0;
    while (bfs()) {
        flow += dfs(start, numeric_limits<int>::max());
    }
    return flow;
}

int main() {
    int n = 6, m = 8; // количество вершин и ребер
    start = 0, sink = 5; // источник и сток

    // Готовый граф для быстрого теста
    add_edge(0, 1, 16);
    add_edge(0, 2, 13);
    add_edge(1, 2, 10);
    add_edge(1, 3, 12);
    add_edge(2, 1, 4);
    add_edge(2, 4, 14);
    add_edge(3, 2, 9);
    add_edge(3, 5, 20);
    add_edge(4, 3, 7);
    add_edge(4, 5, 4);

    cout << "Max flow: " << max_flow() << endl;

    return 0;
}
