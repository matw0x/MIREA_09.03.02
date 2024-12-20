/* Программа по деревьям
Название: оптимальное дерево двоичного поиска
Реализация: список сыновей
Обход: симметричный
Операция: C = A Uсим B
**********************************************
Группа: БСБО-16-23
Студент: Игнатьева М.С.
Вариант: 88
*/

#include <vector>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <functional>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <stack>

template <typename T>
class Tree {
private:
    struct Node {
        std::vector<Node*> children;
        T value;
        unsigned level;

        Node(const T& v) : value(v), level(1) {}
    };

    Node* root;
    std::unordered_map<T, size_t> frequencies;
    double P, W, H;

    void calculateP(const Node* node) {
        if (!node) return;

        if (!node->children.empty()) calculateP(node->children[0]);
        if (node->children.size() == 2) calculateP(node->children[1]);

        P += node->level * frequencies[node->value];
    }

    void calculateH() {
        calculateP(root);

        for (const auto& p : frequencies) W += p.second;

        if (W != 0) H = P / W;
    }

    void printWeights() const {
        std::vector<std::pair<T, size_t>> sortedFrequencies(frequencies.begin(), frequencies.end());
        std::sort(sortedFrequencies.begin(), sortedFrequencies.end(),
            [](const std::pair<T, size_t>& a, const std::pair<T, size_t>& b) { return a.second > b.second; });

        for (auto const& p : sortedFrequencies) std::cout << p.first << '(' << p.second << ')' << std::endl;
    }

public:
    double getH() {
        calculateH();

        return H;
    }

    void printTree() const {
        printWeights();

        std::function<void(const Node*, int, int, std::map<int, std::string>&)> buildTreeLines =
            [&](const Node* node, int depth, int position, std::map<int, std::string>& levels) {
            if (!node) return;

            std::ostringstream oss;
            oss << node->value;
            std::string value = oss.str();

            if (levels.count(depth) == 0) {
                levels[depth] = std::string(position, ' ') + value;
            }
            else {
                if (static_cast<int>(levels[depth].size()) < position) {
                    levels[depth] += std::string(position - levels[depth].size(), ' ') + value;
                } else {
                    levels[depth] += value;
                }
            }

            if (!node->children.empty()) {
                int spacing = std::max(2, 6 - depth);
                int leftPosition = position - spacing;
                int rightPosition = position + spacing;

                if (node->children.size() >= 1 && node->children[0]) {
                    if (static_cast<int>(levels[depth + 1].size()) < leftPosition) {
                        levels[depth + 1] += std::string(leftPosition - levels[depth + 1].size(), ' ') + "/";
                    }
                    else {
                        levels[depth + 1] += "/";
                    }
                    buildTreeLines(node->children[0], depth + 2, leftPosition, levels);
                }

                if (node->children.size() >= 2 && node->children[1]) {
                    if (static_cast<int>(levels[depth + 1].size()) < rightPosition) {
                        levels[depth + 1] += std::string(rightPosition - levels[depth + 1].size(), ' ') + "\\";
                    }
                    else {
                        levels[depth + 1] += "\\";
                    }
                    buildTreeLines(node->children[1], depth + 2, rightPosition, levels);
                }
            }
        };

        std::map<int, std::string> levels;
        buildTreeLines(root, 0, 40, levels);

        for (const auto& p : levels) {
            std::cout << p.second << std::endl;
        }
    }

private:
    void fillFreqs(const std::string& string) { for (const auto& symbol : string) ++frequencies[symbol]; }

    void push() {
        std::vector<std::pair<T, size_t>> sortedFrequencies(frequencies.begin(), frequencies.end());
        std::sort(sortedFrequencies.begin(), sortedFrequencies.end(),
            [](const std::pair<T, size_t>& a, const std::pair<T, size_t>& b) { return a.second > b.second; });

        for (const std::pair<T, size_t>& entry : sortedFrequencies) {
            Node* newNode = new Node(entry.first);

            if (!root) {
                root = newNode;
            }
            else {
                std::function<void(Node*&, unsigned)> insertNode = [&](Node*& node, const unsigned& currentLevel = 1) {
                    if (newNode->value < node->value) {
                        if (node->children.empty()) node->children.resize(2, nullptr);
                        if (!node->children[0]) {
                            newNode->level = currentLevel + 1;
                            node->children[0] = newNode;
                        }
                        else {
                            insertNode(node->children[0], currentLevel + 1);
                        }
                    }
                    else if (newNode->value > node->value) {
                        if (node->children.size() < 2) node->children.resize(2, nullptr);
                        if (!node->children[1]) {
                            newNode->level = currentLevel + 1;
                            node->children[1] = newNode;
                        }
                        else {
                            insertNode(node->children[1], currentLevel + 1);
                        }
                    }
                    };

                insertNode(root, 1);
            }
        }
    }

    static Tree CREATE(Node*& node, Tree<T>& T1, Tree<T>& T2) {
        Tree<T> newTree;
        if (!node) return newTree;

        newTree.root = node;

        if (T1.root) node->children.push_back(T1.root);
        if (T2.root) node->children.push_back(T2.root);

        return newTree;
    }

    void MAKENULL(Node*& node) {
        if (node) {
            if (!node->children.empty()) MAKENULL(node->children[0]);
            if (node->children.size() == 2) MAKENULL(node->children[1]);
            delete node;
            node = nullptr;
        }
    }

public:
    const Node* PARENT(const Node* node) const {
        if (!root || !node || node == root) return nullptr;

        std::function<const Node*(const Node*)> findParent = [&](const Node* current) -> const Node* {
            if (!current) return nullptr;

            if ((current->children.size() > 0 && current->children[0] == node) ||
                (current->children.size() > 1 && current->children[1] == node)) {
                return current;
            }

            if (current->children.size() > 0) {
                const Node* leftResult = findParent(current->children[0]);
                if (leftResult) return leftResult;
            }

            if (current->children.size() > 1) {
                return findParent(current->children[1]);
            }
        };

        return findParent(root);
    }

    const Node* RIGHT_SIBLING(const Node* node) const {
        if (!root || !node || root == node) return nullptr;

        const Node* parent = PARENT(node);
        if (!parent) return nullptr;
        if (parent->children.size() == 2 && parent->children[0] == node) return parent->children[1];

        return nullptr;
    }

    Node* LEFT_CHILD(const Node* node) const { return (root && node && !node->children.empty()) ? node->children[0] : nullptr; }
    T LABEL(const Node* node) const { return (root && node) ? node->value : T(); }
    Node* ROOT() const { return root; }

public:
    Tree(const std::string& input) : P(W = H = 0.0), root(nullptr) {
        fillFreqs(input);
        push();
    }

    Tree() : P(W = H = 0.0), root(nullptr) {}
    ~Tree() { MAKENULL(root); }

    void printInOrder(const Node* start) const {
        if (!start) return;

        std::function<void(const Node*)> inOrder = [&](const Node* current) {
            if (!current) return;

            if (!current->children.empty()) inOrder(current->children[0]);
            std::cout << current->value << ' ';
            if (current->children.size() == 2) inOrder(current->children[1]);
        };

        inOrder(start);
    }

    static void myOperation(const Tree<T>& A, const Tree<T>& B, Tree<T>& C) {
        if (!A.ROOT() || !B.ROOT()) return;

        std::string nodesFromB;
        std::function<void(const Node*)> inOrder = [&](const Node* current) {
            if (!current) return;

            if (!current->children.empty()) inOrder(current->children[0]);
            nodesFromB.push_back(current->value);
            if (current->children.size() == 2) inOrder(current->children[1]);
        };

        inOrder(B.ROOT());

        C.frequencies = A.frequencies;
        //C.push();
        //C.clearFreqs();
        C.fillFreqs(nodesFromB);
        C.push();
    }

private:
    class Iterator {
    public:
        const Node* current;
        std::stack<const Node*> nodes;

        Iterator(const Node* root) : current(nullptr) {
            pushLeft(root);
            moveToNext();
        }

        T operator*() const { return current->value; }

        Iterator& operator++() {
            moveToNext();
            return *this;
        }

        bool operator!=(const Iterator& other) const { return current != other.current; }

    private:
        void pushLeft(const Node* node) {
            while (node) {
                nodes.push(node);
                node = (node->children.empty() ? nullptr : node->children[0]);
            }
        }

        void moveToNext() {
            if (nodes.empty()) {
                current = nullptr;
                return;
            }

            current = nodes.top();
            nodes.pop();

            if (current->children.size() == 2) {
                pushLeft(current->children[1]);
            }
        }
    };

public:
    Iterator begin() const { return Iterator(root); }
    Iterator end() const { return Iterator(nullptr); }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Tree<char> A("РОВПОВАЕЕКУВИЛРКТОАНАНА");
    std::cout << "\t\t\t\tДерево из лекции (A):\n"; A.printTree();
    std::cout << "\nСимметричный обход: "; A.printInOrder(A.ROOT());
    std::cout << "\nСредневзвешенная высота = " << A.getH() << std::endl;

    std::cout << std::endl;

    Tree<char> B("КРАСИВАЯМУСЯ");
    std::cout << "\t\t\t\tМоё дерево (B):\n"; B.printTree();
    std::cout << "\nСимметричный обход: "; for (auto it = B.begin(); it != B.end(); ++it) std::cout << *it << ' ';
    std::cout << "\nСредневзвешенная высота = " << B.getH() << std::endl;

    std::cout << std::endl;

    Tree<char> C; Tree<char>::myOperation(A, B, C);
    std::cout << "\t\t\t\tРезультат (C):\n"; C.printTree();
    std::cout << "\nСимметричный обход: "; C.printInOrder(C.ROOT());
    std::cout << "\nСредневзвешенная высота = " << C.getH() << std::endl;

    return 0;
}