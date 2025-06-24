#pragma once
#include <cstddef>   // Для определения NULL

struct Element  // Элемент списка
{
    Element* Prev;    // указатель на предыдущий элемент
    Element* Next;    // указатель на следующий элемент
    void* Data;       // данные
    Element(Element* prev, void* data, Element* next)
    {
        Prev = prev;
        Data = data;
        Next = next;
    }
    Element* GetNext()  // Получить следующий элемент
    {
        return Next;
    }
    Element* GetPrev()  // Получить предыдущий элемент
    {
        return Prev;
    }
};

//-----------------------------------------------------------
struct Object  // Блок управления списком
{
    Element* Head;  // указатель на начало списка
    Object()
    {
        Head = NULL;
    }
    Element* GetFirst()  // Получить первый элемент списка
    {
        return Head;
    }
    Element* GetLast();
    Element* Search(void* data);   // Поиск элемента по данным
    bool Insert(void* data);       // Добавление элемента в начало
    bool InsertEnd(void* data);    // Добавление элемента в конец
    bool Delete(Element* e);       // Удаление по адресу элемента
    bool Delete(void* data);       // Удаление по значению
    bool DeleteList();             // Очистка списка
    void PrintList(void(*f)(void*));
    void PrintList(void(*f)(void*), Element*);
    int CountList();               // Количество элементов списка
    bool DeleteDouble();           // Удаление дубликатов (заглушка)
};

Object Create();
