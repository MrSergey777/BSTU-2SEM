#include <iostream>
using namespace std;

struct Item {
    int data;
    Item* next;
};

Item* head = nullptr;
Item* tail = nullptr;

bool isNull() {
    return (head == nullptr);
}

void enqueuePriority(int x) {
    Item* newItem = new Item;
    newItem->data = x;
    newItem->next = nullptr;
    if (isNull()) {
        head = tail = newItem;
        return;
    }
    // Если новый элемент имеет приоритет выше, чем head (x > head->data),
    // вставляем его в начало очереди.
    if (x > head->data) {
        newItem->next = head;
        head = newItem;
        return;
    }
    // Проходим по очереди, чтобы найти место вставки:
    // двигаемся до первого элемента, чей приоритет меньше x.
    // Для элементов с равным значением условие (>=) заставляет пройти блок одинаковых значений.
    Item* prev = head;
    Item* curr = head->next;

    while (curr != nullptr && curr->data >= x) {
        prev = curr;
        curr = curr->next;
    }

    // Вставляем новый узел между prev и curr
    newItem->next = curr;
    prev->next = newItem;

    // Если вставили в конец, обновляем tail
    if (curr == nullptr)
        tail = newItem;
}
void deleteFirst() {
    if (isNull()) {
        cout << "Очередь пуста" << endl;
        return;
    }
    Item* tmp = head;
    head = head->next;
    delete tmp;
    if (head == nullptr) {
        tail = nullptr;
    }
}
void getFromHead() {
    if (isNull()) {
        cout << "Очередь пуста" << endl;
    }
    else {
        cout << "Элемент с наивысшим приоритетом: " << head->data << endl;
    }
}
void printQueue() {
    if (isNull()) {
        cout << "Очередь пуста" << endl;
        return;
    }
    Item* cursor = head;
    cout << "Очередь: ";
    while (cursor != nullptr) {
        cout << cursor->data;
        if (cursor->next != nullptr)
            cout << " -> ";
        cursor = cursor->next;
    }
    cout << " -> NULL" << endl;
}
void clearQueue() {
    while (!isNull()) {
        deleteFirst();
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    int choice = 1, z;

    head = tail = nullptr; 

    while (choice != 0) {
        cout << "\nМеню:\n";
        cout << "1 - Добавить элемент в очередь\n";
        cout << "2 - Получить элемент с наивысшим приоритетом\n";
        cout << "3 - Удалить элемент с наивысшим приоритетом\n";
        cout << "4 - Вывести элементы очереди\n";
        cout << "5 - Очистить очередь\n";
        cout << "0 - Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите элемент: ";
            cin >> z;
            enqueuePriority(z);
            printQueue();
            break;
        case 2:
            getFromHead();
            break;
        case 3:
            deleteFirst();
            break;
        case 4:
            printQueue();
            break;
        case 5:
            clearQueue();
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте ещё раз." << endl;
        }
    }

    // Очистка очереди перед завершением программы
    clearQueue();
    return 0;
}