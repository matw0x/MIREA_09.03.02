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

template <typename T> 
class Tree {
public:
    struct Node {
        std::vector<Node*> children;
        T value;

        Node(const T& v) : value(v) {} 
    };

private:
    Node *LAMBDA = nullptr, *root;

public:
    Tree() : root(nullptr) {}

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
        if (!root || !node) return LAMBDA;

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

    void MAKENULL() {
        for (auto it = begin(); it != end(); ) {
            const Node* current = it.current; 
            ++it;
            delete current;
        }

        root = nullptr;
    }

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
        for (auto it = B.begin(); it != B.end(); ++it) {
            A.push(*it);
        }
    }
};

const std::string stars(52, '*');

template <typename T>
void printPostorder(const Tree<T>& tree, const std::string& treeName) {
    std::cout << "POSTORDER TREE " << treeName << std::endl;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl << stars << std::endl;
}

void printTree(const std::vector<std::string>& treeLevels) {
    for (const auto& level : treeLevels) {
        std::cout << level << std::endl;
    }
    std::cout << stars << std::endl;
}

int main() {
    const std::vector<std::string> treeA = {
        "       5.0         ",
        "     /    \\       ",
        "    3      7       ",
        "   / \\   / \\     ",
        "  2   4  6   8     ",
        " /             \\   ",
        "1               9   ",
        "                 \\ ",
        "                  10"
    };

    std::cout << stars << std::endl;
    std::cout << "TREE A:\n";
    printTree(treeA);

    Tree<double> A;
    const double valuesA[10] = {5.0, 3.0, 7.0, 2.0, 4.0, 6.0, 1.0, 8.0, 9.0, 10.0};
    for (int i = 0; i != 10; ++i) {
        A.push(valuesA[i]);
    }

    printPostorder(A, "A");

    ///////////////////////

    const std::vector<std::string> treeB = {
        "        0.0         ",
        "     /      \\      ",
        "  -3.0       2.5    ",
        "   / \\     /  \\   ",
        "-4.0 -2.0  1.5 3.5  ",
        "  /    \\        \\ ",
        "-5.0   -1.0      4.5"
    };

    std::cout << "TREE B:\n";
    printTree(treeB);

    Tree<double> B;
    const double valuesB[] = {0.0, -3.0, 2.5, -4.0, -2.0, 1.5, 3.5, 4.5, -5.0, -1.0};
    for (int i = 0; i != 10; ++i) {
        B.push(valuesB[i]);
    }

    printPostorder(B, "B");

    ////////////////////////

    Tree<double>::myOperation(A, B);

    const std::vector<std::string> unionA_B = {
        "                           5.0                ",
        "                     /               \\       ",
        "                    3                 7       ",
        "               /       \\            / \\     ",
        "              2         4           6   8     ",
        "             /\\       / \\              \\   ",
        "            1 2.5     3.5 4.5             9   ",
        "           / \\                            \\ ",
        "          -5  1.5                           10",
        "            \\                                ",
        "             -4                               ",
        "               \\                             ",
        "                -1                            ",
        "                / \\                          ",
        "               -2  0                          ",
        "               /                              ",
        "              -3                              "
    };

    printTree(unionA_B);
    printPostorder(A, "UNION A and B");

    A.MAKENULL();
    B.MAKENULL();

    return 0;
}