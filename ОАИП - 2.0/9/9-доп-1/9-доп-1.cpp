#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> // Для форматирования вывода
#include <limits>  // Для очистки ввода
using namespace std;

const int NUM_SUBJECTS = 5;

struct Student {
    string lastName;
    string firstName;
    string middleName;
    int birthYear;
    int course;
    string group;
    int grades[NUM_SUBJECTS];

    double getAverage() const {
        double sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        return sum / NUM_SUBJECTS;
    }
};

// Очистка буфера ввода
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Student addStudent() {
    Student s;
    cout << "\nДобавление нового студента:\n";

    cout << "Фамилия: ";
    getline(cin, s.lastName);

    cout << "Имя: ";
    getline(cin, s.firstName);

    cout << "Отчество: ";
    getline(cin, s.middleName);

    cout << "Год рождения: ";
    while (!(cin >> s.birthYear)) {
        cout << "Ошибка! Введите число: ";
        clearInput();
    }

    cout << "Курс: ";
    while (!(cin >> s.course) || s.course < 1 || s.course > 6) {
        cout << "Ошибка! Введите курс от 1 до 6: ";
        clearInput();
    }

    clearInput();
    cout << "Группа: ";
    getline(cin, s.group);

    cout << "Введите " << NUM_SUBJECTS << " оценок через пробел: ";
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        while (!(cin >> s.grades[i]) || s.grades[i] < 1 || s.grades[i] > 5) {
            cout << "Ошибка! Оценка должна быть от 1 до 5: ";
            clearInput();
        }
    }
    clearInput();

    return s;
}

void printStudent(const Student& s) {
    cout << s.lastName << " " << s.firstName << " " << s.middleName
        << ", " << s.birthYear << " г.р., курс " << s.course
        << ", группа " << s.group << "\nОценки: ";

    for (int grade : s.grades) {
        cout << grade << " ";
    }
    cout << "\nСредний балл: " << fixed << setprecision(2) << s.getAverage() << "\n\n";
}

bool compareStudents(const Student& a, const Student& b) {
    if (a.course != b.course) return a.course < b.course;
    if (a.lastName != b.lastName) return a.lastName < b.lastName;
    if (a.firstName != b.firstName) return a.firstName < b.firstName;
    return a.middleName < b.middleName;
}

void printAllStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Список студентов пуст!\n";
        return;
    }

    cout << "\nСписок студентов (" << students.size() << "):\n";
    for (const auto& s : students) {
        printStudent(s);
    }
}

void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), compareStudents);
    cout << "Список студентов отсортирован!\n";
}

void findOldestYoungest(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Список студентов пуст!\n";
        return;
    }

    const Student* oldest = &students[0];
    const Student* youngest = &students[0];

    for (const auto& s : students) {
        if (s.birthYear < oldest->birthYear) oldest = &s;
        if (s.birthYear > youngest->birthYear) youngest = &s;
    }

    cout << "\nСамый старший студент:\n";
    printStudent(*oldest);

    cout << "Самый младший студент:\n";
    printStudent(*youngest);
}

void calculateGroupAverages(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Список студентов пуст!\n";
        return;
    }

    vector<string> groups;
    for (const auto& s : students) {
        if (find(groups.begin(), groups.end(), s.group) == groups.end()) {
            groups.push_back(s.group);
        }
    }

    cout << "\nСредние баллы по группам:\n";
    for (const auto& group : groups) {
        double sums[NUM_SUBJECTS] = { 0 };
        int count = 0;

        for (const auto& s : students) {
            if (s.group == group) {
                for (int i = 0; i < NUM_SUBJECTS; i++) {
                    sums[i] += s.grades[i];
                }
                count++;
            }
        }

        cout << "\nГруппа " << group << " (студентов: " << count << "):\n";
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            cout << "Предмет " << i + 1 << ": " << fixed << setprecision(2) << sums[i] / count << "\n";
        }
    }
}

void findTopStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Список студентов пуст!\n";
        return;
    }

    vector<string> groups;
    for (const auto& s : students) {
        if (find(groups.begin(), groups.end(), s.group) == groups.end()) {
            groups.push_back(s.group);
        }
    }

    cout << "\nЛучшие студенты по группам:\n";
    for (const auto& group : groups) {
        const Student* topStudent = nullptr;
        double maxAvg = 0;

        for (const auto& s : students) {
            if (s.group == group) {
                double avg = s.getAverage();
                if (!topStudent || avg > maxAvg) {
                    topStudent = &s;
                    maxAvg = avg;
                }
            }
        }

        cout << "\nГруппа " << group << ":\n";
        printStudent(*topStudent);
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    vector<Student> students;
    while (true) {
        cout << "\n=== Меню управления студентами ===\n"
            << "1. Добавить студента\n"
            << "2. Показать всех студентов\n"
            << "3. Отсортировать студентов\n"
            << "4. Средние баллы по группам\n"
            << "5. Самый старший и младший\n"
            << "6. Лучшие студенты по группам\n"
            << "7. Выход\n"
            << "Выберите действие: ";

        int choice;
        cin >> choice;
        clearInput();

        switch (choice) {
        case 1: students.push_back(addStudent()); break;
        case 2: printAllStudents(students); break;
        case 3: sortStudents(students); break;
        case 4: calculateGroupAverages(students); break;
        case 5: findOldestYoungest(students); break;
        case 6: findTopStudents(students); break;
        case 7: return 0;
        default: cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }
}