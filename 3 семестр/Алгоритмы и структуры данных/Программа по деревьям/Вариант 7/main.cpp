/* Программа по деревьям
Группа: БСБО-16-23
Студент: Крашенинников М. В.
Вариант: 7
----------------------------------------
Название дерева: Дерево двоичного поиска
Реализация дерева: Список сыновей
Обход: обратный
Операция: А = A ⋃обр. B
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_set>
#include <functional>
#include <map>
#include <sstream>

const std::string stars(52, '*');

template <typename T> 
class Tree {
private:
    struct Node {
        std::vector<Node*> children;
        T value;

        Node(const T& v) : value(v) {}
    };

    Node *LAMBDA = nullptr, *root;

public:
    Tree() : root(nullptr) {}
    ~Tree() { MAKENULL(); }

    class Iterator {
    public:
        const Node* current;
        std::stack<const Node*> nodes;
        std::unordered_set<const Node*> visited;

        Iterator(const Node* root) : current(nullptr) {
            if (root) nodes.push(root);
            moveToNext();
        }

        T operator*() { return current->value; }

        Iterator& operator++() {
            moveToNext();
            return *this;
        }

        bool operator!=(const Iterator& other) const { return current != other.current; }

    private:
        void moveToNext() {
            while (!nodes.empty()) {
                const Node* node = nodes.top();

                if (visited.find(node) == visited.end()) {
                    visited.insert(node);

                    if (node->children.size() == 2 && node->children[1]) nodes.push(node->children[1]);
                    if (node->children.size() >= 1 && node->children[0]) nodes.push(node->children[0]);
                } else {
                    current = node;
                    nodes.pop();
                    return;
                }
            }

            current = nullptr;
        }
    };

    Iterator begin() const { return Iterator(root); }
    Iterator end() const { return Iterator(nullptr); }

    Node* PARENT(const Node* node) const {
        if (!root || !node || node == root) return LAMBDA;

        for (Iterator it = begin(); it != end(); ++it) {
            const Node* current = it.current;

            if (!current) continue;

            for (const Node* child : current->children) {
                if (child == node) {
                    return const_cast<Node*>(current);
                }
            }
        }

        return LAMBDA;
    }

    Node* LEFT_CHILD(const Node* node) const {
        return (!root || !node || node->children.empty()) ? LAMBDA : node->children[0];
    }

    Node* RIGHT_SIBLING(const Node* node) const {
        if (!root || !node) return LAMBDA;

        Node* parent = PARENT(node);
        if (!parent) return LAMBDA;

        if (parent->children.size() == 2 && parent->children[0] == node) {
            return parent->children[1];
        }

        return LAMBDA;
    }

    T LABEL(const Node* node) const { return !node ? T() : node->value; }

    static Tree<T> CREATE(Node*& node, Tree<T>& T1, Tree<T>& T2) {
        Tree<T> newTree;
        if (!node) return newTree;

        newTree.root = node;
        
        if (T1.root) node->children.push_back(T1.root);
        if (T2.root) node->children.push_back(T2.root);

        T1.root = T2.root = nullptr;

        return newTree;
    }

    Node* ROOT() const { return root; }

    void push(const T& key) {
        if (!root) {
            root = new Node(key);
            return;
        }

        Node* current = root;

        while (true) {
            if (key < current->value) {
                if (current->children.empty()) current->children.resize(2, nullptr);
                if (!current->children[0]) {
                    current->children[0] = new Node(key);
                    break;
                } else {
                    current = current->children[0];
                }
            } else if (key > current->value) {
                if (current->children.size() < 2) current->children.resize(2, nullptr);
                if (!current->children[1]) {
                    current->children[1] = new Node(key);
                    break;
                } else {
                    current = current->children[1];
                }
            } else {
                break;
            }
        }
    }

    static void myOperation(Tree<T>& A, const Tree<T>& B) {
        for (auto it = B.begin(); it != B.end(); ++it) A.push(*it);
    }

    void printPostorder(const std::string& treeName) const {
        if (!root) {
            std::cout << treeName << " is empty :(\n";
            return;
        }

        std::cout << "POSTORDER PRINT " << treeName << std::endl;

        for (auto it = begin(); it != end(); ++it) {
            std::cout << *it << ' ';
        }

        std::cout << std::endl << stars << std::endl;
    }

    void printTree(const std::string& treeName) const {
        std::cout << stars << std::endl;

        if (!root) {
            std::cout << treeName << " is empty :(\n";
            return;
        }

        std::cout << treeName << ":\n";

        std::function<void(const Node*, int, int, std::map<int, std::string>&)> buildTreeLines = 
            [&](const Node* node, int depth, int position, std::map<int, std::string>& levels) {
                if (!node) return;

                std::ostringstream oss;
                oss << node->value;
                std::string value = oss.str();

                if (levels.count(depth) == 0) {
                    levels[depth] = std::string(position, ' ') + value;
                } else {
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
                        } else {
                            levels[depth + 1] += "/";
                        }
                        buildTreeLines(node->children[0], depth + 2, leftPosition, levels);
                    }

                    if (node->children.size() >= 2 && node->children[1]) {
                        if (static_cast<int>(levels[depth + 1].size()) < rightPosition) {
                            levels[depth + 1] += std::string(rightPosition - levels[depth + 1].size(), ' ') + "\\";
                        } else {
                            levels[depth + 1] += "\\";
                        }
                        buildTreeLines(node->children[1], depth + 2, rightPosition, levels);
                    }
                }
            };

        std::map<int, std::string> levels;
        buildTreeLines(root, 0, 40, levels);

        for (const auto& [_, line] : levels) {
            std::cout << line << std::endl;
        }
    }

private:
    void MAKENULL() {
        for (auto it = begin(); it != end(); ) {
            const Node* current = it.current; 
            ++it;
            delete current;
        }

        root = nullptr;
    }
};

int main() {
    Tree<double> A;
    const double valuesA[10] = {5.0, 3.0, 7.0, 2.0, 4.0, 6.0, 1.0, 8.0, 9.0, 10.0};
    for (int i = 0; i != 10; ++i) A.push(valuesA[i]);
    A.printTree("A");
    A.printPostorder("A");

    Tree<double> B;
    const double valuesB[10] = {0.0, -3.0, 2.5, -4.0, -2.0, 1.5, 3.5, 4.5, -5.0, -1.0};
    for (int i = 0; i != 10; ++i) B.push(valuesB[i]);
    B.printTree("B");
    B.printPostorder("B");

    Tree<double>::myOperation(A, B);
    A.printTree("UNION A and B");
    A.printPostorder("UNION A and B");

    return 0;
}