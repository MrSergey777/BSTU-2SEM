#include <iostream>
#include <iomanip>
#include <clocale>

using namespace std;

#define MAX_SIZE 100  
struct Heap {
    int arr[MAX_SIZE]; 
    int size;         
    Heap() {
        size = 0;
    }
    void swap(int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    void insert(int value) {
        if (size >= MAX_SIZE) {
            cout << "Куча переполнена!" << endl;
            return;
        }
        arr[size] = value;
        int current = size;
        size++;

        while (current != 0 && arr[current] > arr[(current - 1) / 2]) {
            swap(current, (current - 1) / 2);
            current = (current - 1) / 2;
        }
    }
    int extractMax() {
        if (size <= 0) {
            cout << "Куча пуста!" << endl;
            return -1;
        }
        if (size == 1) {
            size--;
            return arr[0];
        }
        int maxValue = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapify(0);
        return maxValue;
    }

    // Удаление элемента по индексу
    int removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Неверный индекс!" << endl;
            return -1;
        }
        int removedValue = arr[index];
        arr[index] = arr[size - 1];
        size--;

        if (index > 0 && arr[index] > arr[(index - 1) / 2]) {
            int current = index;
            while (current > 0 && arr[current] > arr[(current - 1) / 2]) {
                swap(current, (current - 1) / 2);
                current = (current - 1) / 2;
            }
        }
        else {
            heapify(index);
        }
        return removedValue;
    }
    int removeMin() {
        if (size <= 0) {
            cout << "Куча пуста!" << endl;
            return -1;
        }
        if (size == 1)
            return extractMax();

        int start = size / 2;   
        int minIndex = start;
        for (int i = start + 1; i < size; i++) {
            if (arr[i] < arr[minIndex])
                minIndex = i;
        }
        int minValue = arr[minIndex];
        removeAt(minIndex);
        return minValue;
    }
    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] > arr[largest])
            largest = left;
        if (right < size && arr[right] > arr[largest])
            largest = right;
        if (largest != i) {
            swap(i, largest);
            heapify(largest);
        }
    }
    void buildHeap() {
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapify(i);
        }
    }
    void mergeHeaps(Heap& other) {
        if (size + other.size > MAX_SIZE) {
            cout << "Ошибка: Объединение превышает максимальный размер кучи!" << endl;
            return;
        }
        for (int i = 0; i < other.size; i++) {
            arr[size++] = other.arr[i];
        }
        buildHeap();
        other.size = 0;
    }
    void scan(int i) const {
        int probel = 20;
        std::cout << "\n";
        if (size == 0) {
            std::cout << "Куча пуста";
        }
        else {
            for (int u = 0, y = 0; u < size; u++) {
                std::cout << std::setw(probel + 10) << std::setfill(' ');
                std::cout << arr[u];
                if (u == y) {
                    std::cout << "\n";
                    if (y == 0)
                        y = 2;
                    else
                        y += y * 2;
                }
                probel /= 2; 
            }
        }
        std::cout << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "Ru");

    Heap heap1, heap2;
    int choice = 0, n, value, index;

    do {
        cout << "\nМеню:\n";
        cout << "1. Вставить элементы в первую кучу\n";
        cout << "2. Вставить элементы во вторую кучу\n";
        cout << "3. Показать первую кучу (в виде дерева)\n";
        cout << "4. Показать вторую кучу (в виде дерева)\n";
        cout << "5. Извлечь максимум из первой кучи\n";
        cout << "6. Извлечь минимум из первой кучи\n";
        cout << "7. Удалить i-й элемент из первой кучи\n";
        cout << "8. Объединить две кучи (вторая в первую)\n";
        cout << "9. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Сколько элементов хотите добавить в первую кучу? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Введите элемент " << i + 1 << ": ";
                cin >> value;
                heap1.insert(value);
            }
            break;

        case 2:
            cout << "Сколько элементов хотите добавить во вторую кучу? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Введите элемент " << i + 1 << ": ";
                cin >> value;
                heap2.insert(value);
            }
            break;

        case 3:
            cout << "Первая куча (в виде дерева):\n";
            heap1.scan(0);
            break;

        case 4:
            cout << "Вторая куча (в виде дерева):\n";
            heap2.scan(0);
            break;

        case 5: {
            int maxVal = heap1.extractMax();
            cout << "Извлечённый максимум из первой кучи: " << maxVal << endl;
            break;
        }
        case 6: {
            int minVal = heap1.removeMin();
            cout << "Удалённый минимум из первой кучи: " << minVal << endl;
            break;
        }

        case 7:
            cout << "Введите индекс удаляемого элемента (начиная с 0): ";
            cin >> index;
            value = heap1.removeAt(index);
            cout << "Удалённый элемент: " << value << endl;
            break;

        case 8:
            cout << "Объединяем вторую кучу с первой..." << endl;
            heap1.mergeHeaps(heap2);
            cout << "Объединение выполнено.\n";
            cout << "Первая куча после объединения (в виде дерева):\n";
            heap1.scan(0);
            break;

        case 9:
            cout << "Выход из программы." << endl;
            break;

        default:
            cout << "Неверный выбор. Повторите ввод." << endl;
        }

    } while (choice != 9);

    return 0;
}
