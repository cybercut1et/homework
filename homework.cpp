#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

bool dfs(vector<vector<int>>& graph, vector<bool>& visited, int start, vector<int>& left_to_right) {
    // Для каждого соседа текущей вершины левого множества
    for (int neighbor : graph[start]) {
        // Если сосед еще не был посещен
        if (!visited[neighbor]) {
            // Помечаем сосед как посещенный
            visited[neighbor] = true;
            // Если сосед не сопоставлен ни с одной вершиной правого множества,
            // или если мы можем найти сопоставление для вершины, с которой сосед
            // был ранее сопоставлен
            if (left_to_right[neighbor] == -1 || dfs(graph, visited, left_to_right[neighbor], left_to_right)) {
                // Сопоставляем текущую вершину левого множества с соседом
                left_to_right[neighbor] = start;
                return true;
            }
        }
    }
    // Если не удалось найти сопоставление для текущей вершины левого множества
    return false;
}

vector<int> findMatchingDFS(vector<vector<int>>& graph) {
    int n = graph.size(); // Количество вершин левого множества
    int m = graph[0].size(); // Количество вершин правого множества
    // Инициализируем вектор для хранения результата сопоставления
    vector<int> left_to_right(m, -1);
    // Для каждой вершины левого множества
    for (int i = 0; i < n; i++) {
        // Инициализируем вектор посещенных вершин
        vector<bool> visited(m, false);
        // Выполняем DFS-поиск, начиная с текущей вершины левого множества
        dfs(graph, visited, i, left_to_right);
    }
    return left_to_right;
}

bool bfs(vector<vector<int>>& graph, vector<bool>& visited, int start, vector<int>& left_to_right) {
    // Создаем очередь для BFS-обхода
    queue<int> q;
    // Добавляем текущую вершину левого множества в очередь
    q.push(start);
    // Помечаем текущую вершину как посещенную
    visited[start] = true;

    // Пока очередь не пуста
    while (!q.empty()) {
        // Извлекаем вершину из очереди
        int curr = q.front();
        q.pop();

        // Для каждого соседа текущей вершины
        for (int neighbor : graph[curr]) {

            // Если сосед еще не был посещен
            if (!visited[neighbor]) {
                // Помечаем сосед как посещенный
                visited[neighbor] = true;
                // Если сосед не сопоставлен ни с одной вершиной правого множества,
                // или если мы можем найти сопоставление для вершины, с которой сосед
                // был ранее сопоставлен
                if (left_to_right[neighbor] == -1 || bfs(graph, visited, left_to_right[neighbor], left_to_right)) {
                    // Сопоставляем текущую вершину левого множества с соседом
                    left_to_right[neighbor] = curr;
                    return true;
                }
                // Добавляем сосед в очередь для дальнейшего обхода
                q.push(neighbor);
            }
        }
    }

    // Если не удалось найти сопоставление для текущей вершины левого множества
    return false;
}

vector<int> findMatchingBFS(vector<vector<int>>& graph) {
    int n = graph.size(); // Количество вершин левого множества
    int m = graph[0].size(); // Количество вершин правого множества
    // Инициализируем вектор для хранения результата сопоставления
    vector<int> left_to_right(m, -1);
    // Для каждой вершины левого множества
    for (int i = 0; i < n; i++) {
        // Инициализируем вектор посещенных вершин
        vector<bool> visited(m, false);
        // Выполняем BFS-поиск, начиная с текущей вершины левого множества
        bfs(graph, visited, i, left_to_right);
    }
    return left_to_right;
}

int main() {
    vector<vector<int>> graph = { {0, 1, 1, 0, 0, 0},
                                {1, 0, 0, 1, 0, 0},
                                {0, 0, 1, 0, 0, 1},
                                {0, 0, 0, 0, 1, 0} };

    // Поиск максимального паросочетания с помощью DFS-алгоритма
    vector<int> dfs_matching = findMatchingDFS(graph);

    cout << "DFS matching: ";
    for (int i = 0; i < dfs_matching.size(); i++) {
        if (dfs_matching[i] == -1) {
            cout << "- ";
        }
        else {
            cout << dfs_matching[i] + 1 << " ";
        }
    }
    cout << endl;

    // Поиск максимального паросочетания с помощью BFS-алгоритма
    vector<int> bfs_matching = findMatchingBFS(graph);

    cout << "BFS matching: ";
    for (int i = 0; i < bfs_matching.size(); i++) {
        if (bfs_matching[i] == -1) {
            cout << "- ";
        }
        else {
            cout << bfs_matching[i] + 1 << " ";
        }
    }
    cout << endl;

    return 0;
}

// Цель программы найти максимальное паросочетание - набор пар вершин,
// где каждая вершина левого множества сопоставлена ровно с одной вершиной правого множества,
// и наоборот. Цель алгоритма - найти такое максимальное паросочетание,
// при котором количество пар будет максимальным.
//
// Таким образом, оба алгоритма нашли максимальное паросочетание размера 2, состоящее из двух пар.
//
// Для небольших и плотных графов BFS-реализация, скорее всего, будет работать быстрее,
// а для больших разреженных графов DFS-реализация будет более эффективной.
// Однако точная производительность будет зависеть от конкретной структуры графа и данных.
// Поэтому важно проводить сравнительное тестирование для определения
// наилучшего подхода в каждом конкретном случае.
