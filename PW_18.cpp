#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <windows.h>

using namespace std;  

class Employee {
private:
    int id;
    string name;
    string position;
    double monthlySalary;
    static double companyBudget;

public:
    Employee(int id, const string& name, const string& position, double monthlySalary)
        : id(id), name(name), position(position), monthlySalary(monthlySalary) {
        if (monthlySalary * 12 > companyBudget) {
            throw runtime_error("Бюджет компанії перевищено!");
        }
        companyBudget -= monthlySalary * 12; // Відразу враховуємо річну зарплату
    }

    // Отримання інформації про працівника
    string getInfo() const {
        return "ID: " + to_string(id) + ", Name: " + name +
            ", Position: " + position + ", Monthly Salary: " + to_string(monthlySalary);
    }

    // Розрахунок річної зарплати
    double getAnnualSalary() const {
        return monthlySalary * 12;
    }

    // Зміна місячної зарплати з перевіркою бюджету
    void setMonthlySalary(double newSalary) {
        double annualDifference = (newSalary - monthlySalary) * 12;
        if (annualDifference > companyBudget) {
            throw runtime_error("Зміна зарплати перевищує бюджет компанії!");
        }
        companyBudget -= annualDifference;
        monthlySalary = newSalary;
    }

    // Статична функція для встановлення початкового бюджету
    static void setCompanyBudget(double budget) {
        companyBudget = budget;
    }

    // Статична функція для отримання залишку бюджету
    static double getRemainingBudget() {
        return companyBudget;
    }
};

// Ініціалізація статичного члена
double Employee::companyBudget = 0.0;

int main() {
    try {
        SetConsoleOutputCP(1251);
        SetConsoleCP(1251);
        // Встановлюємо бюджет компанії
        Employee::setCompanyBudget(50000);

        // Створення вектора для зберігання працівників
        vector<Employee> employees;

        // Додаємо працівників у вектор
        employees.push_back(Employee(1, "Олексій", "Програміст", 3000));
        employees.push_back(Employee(2, "Анна", "Дизайнер", 2000));

        // Виведення інформації про кожного працівника
        for (const auto& emp : employees) {
            cout << emp.getInfo() << endl;
        }

        // Виведення залишку бюджету
        cout << "Залишок бюджету: " << Employee::getRemainingBudget() << endl;

        // Змінюємо зарплату першого працівника
        employees[0].setMonthlySalary(3500);
        cout << "Змінено зарплату Олексія." << endl;

        // Виведення оновленої інформації про першого працівника
        cout << employees[0].getInfo() << endl;
        cout << "Залишок бюджету: " << Employee::getRemainingBudget() << endl;

    }
    catch (const exception& ex) {
        cerr << "Помилка: " << ex.what() << endl;
    }

    return 0;
}
