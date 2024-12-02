#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

class Employee {
private:
    int id;
    std::string name;
    std::string position;
    double monthlySalary;
    static double companyBudget;

public:
    Employee(int id, const std::string& name, const std::string& position, double monthlySalary) 
        : id(id), name(name), position(position), monthlySalary(monthlySalary) {
        if (monthlySalary * 12 > companyBudget) {
            throw std::runtime_error("Бюджет компанії перевищено!");
        }
        companyBudget -= monthlySalary * 12; // Відразу враховуємо річну зарплату
    }

    // Отримання інформації про працівника
    std::string getInfo() const {
        return "ID: " + std::to_string(id) + ", Name: " + name + 
               ", Position: " + position + ", Monthly Salary: " + std::to_string(monthlySalary);
    }

    // Розрахунок річної зарплати
    double getAnnualSalary() const {
        return monthlySalary * 12;
    }

    // Зміна місячної зарплати з перевіркою бюджету
    void setMonthlySalary(double newSalary) {
        double annualDifference = (newSalary - monthlySalary) * 12;
        if (annualDifference > companyBudget) {
            throw std::runtime_error("Зміна зарплати перевищує бюджет компанії!");
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
  SetConsoleOutputCP(1251); 
    SetConsoleCP(1251);
    try {
        // Встановлюємо бюджет компанії
        Employee::setCompanyBudget(50000);

        // Створюємо працівників
        Employee emp1(1, "Олексій", "Програміст", 3000);
        Employee emp2(2, "Анна", "Дизайнер", 2000);

        // Виводимо інформацію про працівників
        std::cout << emp1.getInfo() << std::endl;
        std::cout << emp2.getInfo() << std::endl;

        // Виводимо залишок бюджету
        std::cout << "Залишок бюджету: " << Employee::getRemainingBudget() << std::endl;

        // Змінюємо зарплату працівника
        emp1.setMonthlySalary(3500);
        std::cout << "Змінено зарплату Олексія." << std::endl;

        // Виводимо оновлену інформацію
        std::cout << emp1.getInfo() << std::endl;
        std::cout << "Залишок бюджету: " << Employee::getRemainingBudget() << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Помилка: " << ex.what() << std::endl;
    }

    return 0;
}
