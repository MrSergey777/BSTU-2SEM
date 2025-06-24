#include "List.h"
using namespace std;

bool Object::Insert(void* data)  // ������� � ������
{
    bool rc = false;
    if (Head == NULL)
    {
        Head = new Element(NULL, data, Head);
        rc = true;
    }
    else
    {
        Head = (Head->Prev = new Element(NULL, data, Head));
        rc = true;
    }
    return rc;
}
//-----------------------------------------------------------
Element* Object::Search(void* data)  // ����� ��������� ��������
{
    Element* rc = Head;
    while ((rc != NULL) && (rc->Data != data))
        rc = rc->Next;
    return rc;
}
//-----------------------------------------------------------
void Object::PrintList(void(*f)(void*))  // ����� ������
{
    Element* e = Head;
    while (e != NULL)
    {
        f(e->Data);
        e = e->GetNext();
    }
}
//-----------------------------------------------------------
void Object::PrintList(void(*f)(void*), Element* e)
{
    f(e->Data);
}
//-----------------------------------------------------------
bool Object::Delete(Element* e)  // �������� �� ������
{
    bool rc = false;
    if (e != NULL)
    {
        rc = true;
        if (e->Next != NULL)
            e->Next->Prev = e->Prev;
        if (e->Prev != NULL)
            e->Prev->Next = e->Next;
        else
            Head = e->Next;
        delete e;
    }
    return rc;
}
//-----------------------------------------------------------
bool Object::Delete(void* data)  // �������� �� ��������
{
    return Delete(Search(data));
}
//-----------------------------------------------------------
Element* Object::GetLast()
{
    Element* e = Head, * rc = e;
    while (e != NULL)
    {
        rc = e;
        e = e->GetNext();
    }
    return rc;
}
//-----------------------------------------------------------
int Object::CountList()  // ������� ����� ��������� ������
{
    int count = 0;
    Element* current = Head;
    while (current != NULL)
    {
        count++;
        current = current->GetNext();
    }
    return count;
}
//-----------------------------------------------------------
bool Object::DeleteList()  // �������� ����� ������
{
    Element* current = Head;
    while (current != NULL)
    {
        Element* next = current->Next;
        delete current;
        current = next;
    }
    Head = NULL;
    return true;
}
//-----------------------------------------------------------
bool Object::InsertEnd(void* data)  // ���������� �������� � ����� ������
{
    if (Head == NULL) {
        Head = new Element(NULL, data, NULL);
        return true;
    }
    Element* last = GetLast();
    last->Next = new Element(last, data, NULL);
    return true;
}
//-----------------------------------------------------------
bool Object::DeleteDouble()  // �������� ��� �������� ����������� ���������
{
    return false;
}
//-----------------------------------------------------------
Object Create()
{
    return *(new Object());
}
