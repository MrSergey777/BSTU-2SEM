#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;
struct Address
{
    char name[NAME_SIZE];
    char city[CITY_SIZE];
    Address* next;
    Address* prev;
};
int menu(void);
void insert(Address* e, Address** phead, Address** plast);
Address* setElement();
void outputList(Address** phead, Address** plast);
void find(char name[NAME_SIZE], Address** phead);
void delet(char name[NAME_SIZE], Address** phead, Address** plast);
void writeToFile(Address** phead);
void readFromFile(Address** phead, Address** plast);
void deleteKFirst(int k, Address** phead, Address** plast);
void deleteKLast(int k, Address** phead, Address** plast);
void findMinByName(Address** phead);
int main(void)
{
    Address* head = NULL;
    Address* last = NULL;
    setlocale(LC_CTYPE, "Rus");

    while (true)
    {
        switch (menu())
        {
        case 1:
            insert(setElement(), &head, &last);
            break;
        case 2:
        {
            char dname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(dname, NAME_SIZE - 1, '\n');
            cin.ignore(cin.rdbuf()->in_avail());
            cin.sync();
            delet(dname, &head, &last);
        }
        break;
        case 3:
            outputList(&head, &last);
            break;
        case 4:
        {
            char fname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(fname, NAME_SIZE - 1, '\n');
            cin.ignore(cin.rdbuf()->in_avail());
            cin.sync();
            find(fname, &head);
        }
        break;
        case 5:
            writeToFile(&head);
            break;
        case 6:
            readFromFile(&head, &last);
            break;
        case 7:
            return 0;
        case 8: 
            int k;
            cout << "Введите количество элементов для удаления: ";
            cin >> k;
            cin.ignore(); 
            deleteKFirst(k, &head, &last);
            break;
        case 9: 
            int a;
            cout << "Введите количество элементов для удаления: ";
            cin >> a;
            cin.ignore(); 
            deleteKLast(a, &head, &last);
            break;
        case 10:
            findMinByName(&head);
            break;
        default:
            exit(1);
        }
    }
    return 0;
}

int menu(void)
{
    char s[80];  int c;
    cout << endl;
    cout << "1. Ввод имени" << endl;
    cout << "2. Удаление имени" << endl;
    cout << "3. Вывод на экран" << endl;
    cout << "4. Поиск" << endl;
    cout << "5. Запись в файл" << endl;
    cout << "6. Чтение из файла" << endl;
    cout << "7. Выход" << endl;
    cout << "8. Удалить первые K элементов" << endl;
    cout << "9. Удалить последние K элементов" << endl;
    cout << "10. Найти минимальный элемент по имени" << endl;
    cout << endl;
    do
    {
        cout << "Ваш выбор: ";
        cin.sync();
        gets_s(s);
        cout << endl;
        c = atoi(s);
    } while (c < 0 || c > 10);
    return c;
}
void insert(Address* e, Address** phead, Address** plast)
{
    Address* p = *plast;
    if (*plast == NULL)
    {
        e->next = NULL;
        e->prev = NULL;
        *plast = e;
        *phead = e;
        return;
    }
    else
    {
        p->next = e;
        e->next = NULL;
        e->prev = p;
        *plast = e;
    }
}

Address* setElement()
{
    Address* temp = new Address();
    if (!temp)
    {
        cerr << "Ошибка выделения памяти памяти";
        return NULL;
    }
    cout << "Введите имя: ";
    cin.getline(temp->name, NAME_SIZE - 1, '\n');
    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();
    cout << "Введите город: ";
    cin.getline(temp->city, CITY_SIZE - 1, '\n');
    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void outputList(Address** phead, Address** plast)
{
    Address* t = *phead;
    while (t)
    {
        cout << t->name << ' ' << t->city << endl;
        t = t->next;
    }
    cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead)
{
    Address* t = *phead;
    while (t)
    {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
        cout << t->name << ' ' << t->city << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast)
{
    struct Address* t = *phead;
    while (t)
    {
        if (!strcmp(name, t->name))  break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
    {
        if (*phead == t)
        {
            *phead = t->next;
            if (*phead)
                (*phead)->prev = NULL;
            else
                *plast = NULL;
        }
        else
        {
            t->prev->next = t->next;
            if (t != *plast)
                t->next->prev = t->prev;
            else
                *plast = t->prev;
        }
        delete t;
        cout << "Элемент удален" << endl;
    }
}
void writeToFile(Address** phead)       
{
    struct Address* t = *phead;
    FILE* fp;
    errno_t err = fopen_s(&fp, "9.txt", "wb");
    if (err)
    {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    cout << "Сохранение в файл 9.txt" << endl;
    while (t)
    {
        fwrite(t, sizeof(struct Address), 1, fp);
        t = t->next;
    }
    fclose(fp);
}
void readFromFile(Address** phead, Address** plast)   
{
    struct Address* t;
    FILE* fp;
    errno_t err = fopen_s(&fp, "9.txt", "rb");
    if (err)
    {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    while (*phead)
    {
        *plast = (*phead)->next;
        delete* phead;
        *phead = *plast;
    }
    *phead = *plast = NULL;
    cout << "Загрузка из файла 9.txt" << endl;
    while (!feof(fp))
    {
        t = new Address();
        if (!t)
        {
            cerr << "Ошибка выделения памяти" << endl;
            return;
        }
        if (1 != fread(t, sizeof(struct Address), 1, fp)) break;
        insert(t, phead, plast);
    }
    fclose(fp);
}
void deleteKFirst(int k, Address** phead, Address** plast) {
    if (*phead == NULL) {
        cerr << "Список пуст!" << endl;
        return;
    }

    if (k <= 0) {
        cerr << "Количество элементов для удаления должно быть положительным!" << endl;
        return;
    }

    int count = 0;
    Address* current = *phead;
    while (current != NULL && count < k) {
        Address* temp = current;
        current = current->next;

        if (current != NULL) {
            current->prev = NULL;
        }

        delete temp;
        count++;
    }
    *phead = current;
    if (*phead == NULL) {
        *plast = NULL;
    }
    cout << "Удалено " << count << " элементов." << endl;
}
void deleteKLast(int k, Address** phead, Address** plast) {
    if (*plast == NULL) {
        cerr << "Список пуст!" << endl;
        return;
    }

    if (k <= 0) {
        cerr << "Количество элементов для удаления должно быть положительным!" << endl;
        return;
    }

    int count = 0;
    Address* current = *plast;
    while (current != NULL && count < k) {
        current = current->prev;
        count++;
    }
    if (current == NULL) {
        while (*phead != NULL) {
            Address* temp = *phead;
            *phead = (*phead)->next;
            delete temp;
        }
        *plast = NULL;
    }
    else {
        Address* temp = current->next;
        current->next = NULL;

        while (temp != NULL) {
            Address* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        *plast = current;
    }
    cout << "Удалено " << (count > k ? k : count) << " последних элементов." << endl;
}
void findMinByName(Address** phead) {
    if (*phead == NULL) {
        cerr << "Список пуст!" << endl;
        return;
    }
    Address* current = *phead;
    Address* minNode = current;
    while (current != NULL) {
        if (strcmp(current->name, minNode->name) < 0) {
            minNode = current;
        }
        current = current->next;
    }
    cout << "Элемент с минимальным именем: " << endl;
    cout << "Имя: " << minNode->name << endl;
    cout << "Город: " << minNode->city << endl;
}