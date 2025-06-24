#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int key;
    string info;
    Node* left;
    Node* right;
};

Node* createNode(int key, string info) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->info = info;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int key, string info) {
    if (root == nullptr)
        return createNode(key, info);
    if (key < root->key)
        root->left = insert(root->left, key, info);
    else if (key > root->key)
        root->right = insert(root->right, key, info);
    return root;
}

bool treeSearch(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (root->key == key)
        return true;
    if (key < root->key)
        return treeSearch(root->left, key);
    else
        return treeSearch(root->right, key);
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "(" << root->key << ", " << root->info << ") ";
        inorderTraversal(root->right);
    }
}

void findAndPrintNearestPath(Node* root, int key) {
    if (root == nullptr) {
        cout << "Дерево пустое." << endl;
        return;
    }
    queue<pair<Node*, vector<Node*>>> q;
    vector<Node*> initPath;
    initPath.push_back(root);
    q.push({ root, initPath });
    while (!q.empty()) {
        auto frontPair = q.front();
        q.pop();
        Node* current = frontPair.first;
        vector<Node*> path = frontPair.second;
        if (current->key == key) {
            cout << "Найден путь до вершины с ключом " << key << ":\n";
            for (auto node : path)
                cout << "(" << node->key << ", " << node->info << ") ";
            cout << "\nКоличество ветвей: " << path.size() - 1 << "\n";
            return;
        }
        if (current->left != nullptr) {
            vector<Node*> newPath = path;
            newPath.push_back(current->left);
            q.push({ current->left, newPath });
        }
        if (current->right != nullptr) {
            vector<Node*> newPath = path;
            newPath.push_back(current->right);
            q.push({ current->right, newPath });
        }
    }
    cout << "Вершина с ключом " << key << " не найдена." << endl;
}

Node* buildTreeFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Ошибка открытия файла " << filename << endl;
        return nullptr;
    }
    Node* root = nullptr;
    int num;
    while (infile >> num)
        root = insert(root, num, "");
    infile.close();
    return root;
}

void inorderToFile(Node* root, ofstream& ofs) {
    if (root != nullptr) {
        inorderToFile(root->left, ofs);
        ofs << root->key << "\n";
        inorderToFile(root->right, ofs);
    }
}

void writeTreeInorderToFile(Node* root, const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "Ошибка открытия файла " << filename << endl;
        return;
    }
    inorderToFile(root, outfile);
    outfile.close();
    cout << "Дерево записано в файл " << filename << endl;
}

int countRightLeaves(Node* node, bool isRight) {
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return isRight ? 1 : 0;
    return countRightLeaves(node->left, false) + countRightLeaves(node->right, true);
}

// Исправленная версия функции структурированного вывода дерева
void printTree(Node* root, int space = 0, int gap = 4) {
    if (root == nullptr)
        return;
    printTree(root->right, space + gap, gap);
    for (int i = 0; i < space; i++)
        cout << " ";
    cout << root->key;
    if (!root->info.empty())
        cout << " (" << root->info << ")";
    cout << "\n";
    printTree(root->left, space + gap, gap);
}

int main() {
    setlocale(LC_ALL, "RU");
    Node* root = nullptr;
    int choice;
    int key;
    string info;
    string filename;

    do {
        cout << "\n--- Меню ---\n";
        cout << "1. Вставить элемент в дерево\n";
        cout << "2. Поиск элемента в дереве\n";
        cout << "3. Вывести дерево (inorder обход)\n";
        cout << "4. Доп-1: Путь от корня до ближайшей вершины с заданным ключом\n";
        cout << "5. Построить дерево из файла\n";
        cout << "6. Записать дерево в файл (inorder порядок)\n";
        cout << "7. Основное задание: Вывести количество листьев, являющихся правыми дочерними вершинами\n";
        cout << "8. Вывести дерево в структурированном представлении\n";
        cout << "9. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите строку: ";
            cin.ignore(); // очищаем буфер ввода
            getline(cin, info);
            root = insert(root, key, info);
            cout << "Узел добавлен в дерево.\n";
            break;
        case 2:
            cout << "Введите ключ для поиска: ";
            cin >> key;
            if (treeSearch(root, key))
                cout << "Элемент с ключом " << key << " найден!\n";
            else
                cout << "Элемент с ключом " << key << " не найден!\n";
            break;
        case 3:
            cout << "Обход дерева (inorder): ";
            inorderTraversal(root);
            cout << endl;
            break;
        case 4:
            cout << "Введите ключ для поиска пути: ";
            cin >> key;
            findAndPrintNearestPath(root, key);
            break;
        case 5:
            cout << "Введите имя файла для построения дерева: ";
            cin >> filename;
            root = buildTreeFromFile(filename);
            break;
        case 6:
            cout << "Введите имя файла для записи дерева (inorder порядок): ";
            cin >> filename;
            writeTreeInorderToFile(root, filename);
            break;
        case 7: {
            int count = countRightLeaves(root, false);
            cout << "Количество листьев, являющихся правыми дочерними вершинами: " << count << endl;
            break;
        }
        case 8:
            cout << "Структурированное представление дерева:\n";
            printTree(root);
            break;
        case 9:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}
