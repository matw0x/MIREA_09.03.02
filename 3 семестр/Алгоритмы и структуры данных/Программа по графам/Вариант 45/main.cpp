// Алгоритм: Вывести на экран все существующие пути в ациклическом орграфе
// Способ представления графа: Матрица смежности
// Студент: Вариант 45 - Альзоаби Адель, БСБО-16-23 

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <iomanip>

struct Vertex {
    std::string name;
    bool visited; // mark
    size_t index;

    Vertex(const std::string& n, const bool& v, const size_t& i) : 
    name(n), visited(v), index(i) {}

    Vertex() : name(""), visited(false), index(size_t(-1)) {}

    bool operator == (const Vertex& other) const {
        return this->name == other.name;
    }
};

struct Edge {
    Vertex start, end;
    float cost;

    Edge(const Vertex& v, const Vertex& w, const float& c = 0.0) : start(v), end(w), cost(c) {}
};

struct GraphData {
    std::vector<std::vector<bool>> adjacencyMatrix;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};

class Graph {
private:
    GraphData data;

    bool isVertexExists(const Vertex& vertex) {
        return findVertexByName(vertex.name) != nullptr;
    }

    bool isVertexExists(const std::string& name) {
        return findVertexByName(name) != nullptr;
    }

    bool isVertexExists(const Vertex* vertex) const {
        return vertex != nullptr;
    }

    Vertex* findVertexByName(const std::string& name) {
        for (auto& vertex : data.vertices) {
            if (vertex.name == name) {
                return &vertex;
            }
        }

        return nullptr;
    }

    void findAllPaths(const size_t& current, std::vector<std::string>& path, 
    std::vector<std::vector<std::string>>& allPaths) {
        data.vertices[current].visited = true;
        path.push_back(data.vertices[current].name);

        bool isLeaf = true;

        for (size_t next = 0; next != data.adjacencyMatrix[current].size(); ++next) {
            if (data.adjacencyMatrix[current][next] && !data.vertices[next].visited) {
                isLeaf = false;
                findAllPaths(next, path, allPaths);
            }
        }

        if (isLeaf) {
            allPaths.push_back(path);
        }

        data.vertices[current].visited = false;
        path.pop_back();
    }

public:
    void ADD_V(const std::string& name, const bool& mark) {
        if (isVertexExists(name)) {
            std::cerr << "Can't add a vertex " << name << " : already exists!\n";
            return;
        }

        data.vertices.push_back(Vertex(name, mark, data.vertices.size()));
        for (auto& row : data.adjacencyMatrix) {
            row.push_back(false);
        }
        data.adjacencyMatrix.emplace_back(data.vertices.size(), false);
    }

    void DEL_V(const std::string& name) {
        Vertex* toDelete = findVertexByName(name);

        if (!isVertexExists(toDelete)) {
            std::cerr << "Can't delete a vertex " << name << " : does not exists!\n";
            return;
        }

        size_t index = toDelete->index;
        data.vertices.erase(data.vertices.begin() + index);
        data.adjacencyMatrix.erase(data.adjacencyMatrix.begin() + index);

        for (auto& row : data.adjacencyMatrix) {
            row.erase(row.begin() + index);
        }

        for (size_t i = 0; i != data.vertices.size(); ++i) {
            data.vertices[i].index = i;
        }
    }

    void ADD_E(const std::string& v, const std::string& w) {
        Vertex *start = findVertexByName(v), *end = findVertexByName(w);

        if (!isVertexExists(start)) {
            std::cerr << "Vertex " << v << " does not exist!\n";
            return;
        }

        if (!isVertexExists(end)) {
            std::cerr << "Vertex " << w << " does not exist!\n";
            return;
        }

        if (data.adjacencyMatrix[start->index][end->index]) {
            std::cerr << "Edge " << v << " -> " << w << " already exists!\n";
            return;
        }

        data.adjacencyMatrix[start->index][end->index] = true;
        data.edges.push_back(Edge(*start, *end));
    }

    void DEL_E(const std::string& v, const std::string& w) {
        Vertex *start = findVertexByName(v), *end = findVertexByName(w);

        if (!isVertexExists(start)) {
            std::cerr << "Vertex " << v << " does not exist!\n";
            return;
        }

        if (!isVertexExists(end)) {
            std::cerr << "Vertex " << w << " does not exist!\n";
            return;
        }

        if (!data.adjacencyMatrix[start->index][end->index]) {
            std::cerr << "Edge " << v << " -> " << w << "does not exists!\n";
            return;
        }

        data.adjacencyMatrix[start->index][end->index] = false;

        for (auto edge = data.edges.begin(); edge != data.edges.end(); ++edge) {
            if (edge->start == *start && edge->end == *end) {
                data.edges.erase(edge);
                break;
            }
        }
    }

    void EDIT_V(const std::string& name, const bool& mark) {
        Vertex* vertex = findVertexByName(name);

        if (!isVertexExists(vertex)) {
            std::cerr << "Can't edit a vertex " << name << " : does not exists!\n";
            return;
        }

        vertex->visited = mark;
    }

    void EDIT_E(const std::string& v, const std::string& w, const float& c) {
        Vertex *start = findVertexByName(v), *end = findVertexByName(w);

        if (!isVertexExists(start)) {
            std::cerr << "Vertex " << v << " does not exist!\n";
            return;
        }

        if (!isVertexExists(end)) {
            std::cerr << "Vertex " << w << " does not exist!\n";
            return;
        }

        if (!data.adjacencyMatrix[start->index][end->index]) {
            std::cerr << "Can't edit an edge : does not exists!\n";
            return;
        }

        for (auto edge = data.edges.begin(); edge != data.edges.end(); ++edge) {
            if (edge->start == *start && edge->end == *end) {
                edge->cost = c;
            }
        }
    }

    size_t FIRST(const Vertex& v) {
        if (!isVertexExists(v)) {
            std::cerr << "A vertex does not exists!\n";
            return data.vertices.size();
        }

        for (size_t i = 0; i != data.adjacencyMatrix.size(); ++i) {
            if (data.adjacencyMatrix[v.index][i]) {
                for (size_t j = 0; j != data.vertices.size(); ++j) {
                    if (data.vertices[j].index == i) {
                        return j;
                    }
                }
            }
        }

        return data.vertices.size();
    }

    size_t NEXT(const Vertex& v, const size_t& i) {
        if (!isVertexExists(v)) {
            std::cerr << "A vertex does not exists!\n";
            return data.vertices.size();
        }

        for (size_t j = i + 1; j < data.adjacencyMatrix[v.index].size(); ++j) {
            if (data.adjacencyMatrix[v.index][j]) {
                return j;
            }
        }

        return data.vertices.size();
    }

    Vertex VERTEX(const Vertex& v, const size_t& i) {
        if (!isVertexExists(v)) {
            std::cerr << "A vertex does not exists!\n";
            return Vertex();
        }

        for (size_t j = 0, adjacentIndex = 0; j != data.adjacencyMatrix[v.index].size(); ++j) {
            if (data.adjacencyMatrix[v.index][j]) {
                if (adjacentIndex == i) {
                    return data.vertices[j];
                }

                ++adjacentIndex;
            }
        }

        return Vertex();
    }

    void showVertices() const {
        std::cout << "\nVertices\n";

        for (auto it = data.vertices.begin(); it != data.vertices.end(); ++it) {
            std::cout << it->name << ' '; 
        }
        
        std::cout << std::endl;
    }

    void showAdjacencyMatrix() const {
        std::cout << "\nAdjacency Matrix:\n";

        size_t columnWidth = 0;
        for (const auto& vertex : data.vertices) {
            columnWidth = std::max(columnWidth, vertex.name.size());
        }
        columnWidth = std::max(columnWidth, size_t(2));

        std::cout << std::setw(columnWidth + 4) << " ";
        for (const auto& vertex : data.vertices) {
            std::cout << std::setw(columnWidth + 2) << vertex.name;
        }
        std::cout << std::endl;

        for (size_t i = 0; i < data.adjacencyMatrix.size(); ++i) {
            std::cout << std::setw(columnWidth + 2) << data.vertices[i].name << " |";

            for (size_t j = 0; j < data.adjacencyMatrix[i].size(); ++j) {
                std::cout << std::setw(columnWidth + 2) << data.adjacencyMatrix[i][j];
            }

            std::cout << std::endl;
        }
    }

    void runSolving() {
        if (data.vertices.empty()) {
            std::cerr << "Have no vertices!\n";
            return;
        }

        if (data.edges.empty()) {
            std::cerr << "Have no edges!\n";
            return;
        }

        std::vector<std::vector<std::string>> allPaths;

        for (size_t start = 0; start != data.vertices.size(); ++start) {
            std::vector<std::string> path;
            findAllPaths(start, path, allPaths);
        }

        std::cout << "\n\n\t\tANSWER:\n";
        for (const auto& path : allPaths) {
            for (const auto& vertex : path) {
                std::cout << vertex << ' ';
            }
            std::cout << std::endl;
        }
    }
};

void run(Graph& graph, const int& countVertices, const std::string& allEdges) {
    for (int i = 1; i <= countVertices; ++i) {
        graph.ADD_V(std::to_string(i), false);
    }

    std::istringstream iss(allEdges);
    std::string start, end;

    while (iss >> start >> end) {
        graph.ADD_E(start, end);
    }

    graph.showVertices();
    graph.showAdjacencyMatrix();
    graph.runSolving();
}

int main() {
    Graph graph1;
    const std::string edges1 = R"(
        1 3
        1 5
        1 6
        2 5
        2 6
        3 4
        3 5
        5 6
    )";

    Graph graph2;
    const std::string edges2 = R"(
        1 3
        1 5
        1 6
        2 5
        2 6
        3 4
        3 5
        5 6
        4 18
        18 20
        20 8
        8 11
        11 7
        7 16
        8 7
        7 2
        2 9
        9 16
        15 10
        10 12
        12 1
        1 13
        13 17
        14 19
        17 3
        1 19
        15 6
        12 4
        20 17
    )";

    run(graph1, 6, edges1);
    run(graph2, 20, edges2);

    return 0;
}