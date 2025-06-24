#include <iostream>
#include <cmath>
using namespace std;
struct queqe {
    int a;
    queqe* next;
};
int massage() {
    setlocale(LC_ALL, "ru");
    int choice;
    cout << endl << "Выберите команду:" << endl;
    cout << "1 - Добавление элементов в очередь" << endl;
    cout << "2 - Вывод всех элементов очереди" << endl;
    cout << "3 - Найти количество элементов между максимальным и минимальным элементами очереди" << endl;
    cout << "4 - Удаление элемента" << endl;
    cout << "5 - ДОП -2 Разработать функцию, которая удаляет из очереди первый отрицательный элемент, если такой есть" << endl;
    cout << "0 - Выход" << endl;
    cin >> choice;
    return choice;
} 
void in( queqe **begin, queqe **end) {
    int b;
    setlocale(LC_ALL, "ru");
    cout << "Введите цело число: ";
    cin >> b;
    queqe* t = new queqe;
    (*t).next = NULL;
    (*t).a = b;
    if (*begin == NULL) {
        *begin = *end = t;
    }
    else {
        (**end).next = t;
        *end = t;
    }
}
void out(queqe** begin) {
    setlocale(LC_ALL, "ru");
    if (*begin == NULL) {               
        cout << "Может введем элемент)?" << endl;
        return;
    }
    queqe* temp = *begin;
    cout << "Элементы очереди ";
    while (temp != NULL) {
        cout << (*temp).a;
        if ((*temp).next != NULL) cout << " ----> ";
        temp = (*temp).next;
    }
}
void serchminmax(queqe** begin) {
    int min = INT_MAX;
    int max = INT_MIN;
    int minp = 0;
    int maxp = 0;
    setlocale(LC_ALL, "ru");
    if (*begin == NULL) {
        cout << "Может введем элементы?" << endl;
        return;
    }
    queqe* temp = *begin;
    int i = 1;
    while (temp != NULL) {
        if ((*temp).a > max) {
            max = (*temp).a;
            maxp = i;
        }
        if ((*temp).a < min) {
            min = (*temp).a;
            minp = i;
        }
        temp = (*temp).next;
        ++i;
    }
    cout << abs(maxp - minp-1);
}
void delet(queqe** begin, queqe** end) {
    setlocale(LC_ALL, "ru");
    if (*begin == NULL) {
        cout << "Очередь пуста, нечего удалять!" << endl;
        return;
    }
    cout << "Введите элемент очереди, который хотите удалить: ";
    int q;
    cin >> q;
    queqe* temp = *begin;
    queqe* pred = NULL;
    bool found = false;
    while (temp != NULL) {
        if ((*temp).a == q) {
            found = true;
            if (pred == NULL) {
                *begin = (*temp).next;
                if (*begin == NULL) {
                    *end = NULL;
                }
            }
            else {
                (*pred).next = (*temp).next;
                if ((*temp).next == NULL) {
                    *end = pred;
                }
            }
            queqe* toDelete = temp;
            temp = (*temp).next;
            delete toDelete;
        }
        else {
            pred = temp;
            temp = (*temp).next;
        }
    }
    if (!found) {
        cout << "Элемент " << q << " не найден в очереди!" << endl;
    }
    else {
        cout << "Элемент(ы) " << q << " успешно удалены!" << endl;
    }
}
void removeFirstNegative(queqe** begin, queqe** end) {
    setlocale(LC_ALL, "ru");
    if (*begin == NULL) {
        cout << "Очередь пуста!" << endl;
        return;
    }
    queqe* temp = *begin;
    queqe* pred = NULL;
    int count = 0;
    bool found = false;
    queqe* counter = *begin;
    while (counter != NULL) {
        count++;
        counter = (*counter).next;
    }
    while (temp != NULL && !found) {
        if ((*temp).a < 0) {
            found = true;
            if (pred == NULL) {
                *begin = (*temp).next;
                if (*begin == NULL) {
                    *end = NULL;
                }
            }
            else {
                (*pred).next = (*temp).next;
                if ((*temp).next == NULL) {
                    *end = pred;
                }
            }
            delete temp;
            count--;
            cout << "Удален первый отрицательный элемент. Осталось элементов: " << count << endl;
        }
        else {
            pred = temp;
            temp = (*temp).next;
        }
    }
    if (!found) {
        cout << "Отрицательных элементов не найдено. Всего элементов: " << count << endl;
    }
}
int main()
{
    queqe* begin = NULL, * end, * pr;
    setlocale(LC_ALL, "ru");
    int n;
    cout << "Введите максимальный размер очереди n ";
    cin >> n;
    int choiice = INT_MAX;
    while (choiice != 0) {
        choiice = massage();
        if (choiice == 1) in(&begin, &end);
        if (choiice == 2) out(&begin);
        if (choiice == 3) serchminmax(&begin);
        if (choiice == 4) delet(&begin, &end);
        if (choiice == 5) removeFirstNegative(&begin, &end);
    }
}

