#include <iostream>
#include <set> 
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    set<int> mySet;
    mySet.insert(5);
    mySet.insert(3);
    mySet.insert(8);
    mySet.insert(1);
    cout << "Элемент с минимальным значением множества: " << *mySet.begin();
    return 0;
}