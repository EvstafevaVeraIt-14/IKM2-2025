#include "Header.h"

int main() {
    Stack stack;
    int choice;
    string expression;
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do { // запуск программы, пока пользователь не остановит
        while (true) {
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Выберите способ ввода выражения в постфиксной записи:" << endl
                << "1 - Ввод с консоли" << endl
                << "2 - Загрузка из файла" << endl
                << "3 - Генерация случайного выражения" << endl
                << "0 - Выход" << endl;
            string choiceStr;
            getline(cin, choiceStr);
            if (isInt(choiceStr)) { // проверка на корректный выбор способа ввода
                choice = stoi(choiceStr);
                if (choice >= 0 && choice <= 3) break;
            }
            cout << endl << "Недопустимое значение." << endl;
        }

        switch (choice) {
        case 1:
            stack.clear();
            inputFromConsole(stack); // ввод с консоли
            break;

        case 2:
            stack.clear();
            inputFromFile(stack); // использование значения из файла
            break;

        case 3:
            stack.clear();
            inputFromRandom(stack); // генерирование случайного значения
            break;

        case 0:
            cout << "Программа завершена."; // выход из программы
            break;

        }
        if (stack.isEmpty() && (choice != 0)) { // проверка на необходимость предупредить о невозможности посчитать результат
            cout << endl << "В выражении нет допустимых элементов." << endl;
        }
        if (choice != 0 && !stack.isEmpty()) { // вычисление и вывод результата
            double result = calculateExpression(stack);
            if (result != 0) {
                cout << "Результат: " << result << endl;
            }
  
        }
    } while (choice != 0);

    return 0;
}
