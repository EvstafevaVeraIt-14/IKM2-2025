#include "Header.h"

// Основные методы стека
void Stack::push(double value) { elem.push_back(value); } // добавление элемента в стек

double Stack::pop() { // извлечение последнего элемента стека
    if (isEmpty()) return 0.0;
    double num = elem.back();
    elem.pop_back();
    return num;
}

bool Stack::isEmpty() { return elem.empty(); } // проверка стека на пустоту

int Stack::getSize() { return elem.size(); } // размер стека

void Stack::clear() { elem.clear(); } // очищение стека

// Функции проверки ввода
bool isInt(const string& str) { // проверка на содержание недопустимого ввода в int значениях
    int begin = str.find_first_not_of(" \t");
    if (begin == string::npos) return false;
    int end = str.find_last_not_of(" \t");
    string str1 = str.substr(begin, end - begin + 1); // удаление лишних пробелов и проверка на пустую строку

    if (str1.empty()) return false;
    if (str1.length() > 10) return false;
    int dotCount = 0;
    int start = (str1[0] == '+') ? 1 : 0;
    if (start == 1 && str1.length() == 1) return false;
    for (int i = start; i < str1.length(); ++i) {
        if (!isdigit(str1[i])) return false;
    }
    return true;
}

bool isDouble(const string& s) { // проверка на содержание недопустимого ввода в double значениях
    if (s.empty()) return false;
    string str = s;
    replace(str.begin(), str.end(), ',', '.'); // для корректного чтения вещественных значений через '.'
    istringstream sstr(str);
    double num;
    sstr >> num;
    if (sstr.fail() ) {
        return false;
    }
    if (num < 0) {
        return false;
    }
    char remaining;
    while (sstr >> remaining) {
        if (!isspace(remaining)) {
            return false;
        }
    }
    return true;
}

// Функции для работы с выражением
double calculateExpression(Stack& stack) { // функция для вычисления всего выражения
    Stack tempStack; //вспомогательный стек для хранения изначального набора элементов
    bool hasError = false;
    while (!stack.isEmpty()) {
        tempStack.push(stack.pop());
    }
    while (!tempStack.isEmpty() && !hasError) {
        double element = tempStack.pop();
        if (isOperator(element)) {
            if (stack.getSize() < 2) {
                cout << "Недостаточно операндов для оператора '"
                    << static_cast<char>(element) << "'" << endl; // static_cast<char> для корректного чтения строки как оператора
                hasError = true;
                break;
            }
            double b = stack.pop();
            double a = stack.pop();
            double result = calculation(a, b, element);
            if (result == 0 && (
                (element == '/' && b == 0) ||
                !isOperator(element)
                )) {
                hasError = true;
                break;
            }
            stack.push(result);
        }
        else {
            stack.push(element);
        }
    }
    if (hasError) {
        stack.clear();
        return 0;
    }
    if (stack.getSize() != 1) {
        cout << "Некорректное выражение. В стеке осталось "
            << stack.getSize() << " элементов" << endl;
        stack.clear();
        return 0;
    }
    return stack.pop();
}

bool isOperator(double element) { // проверка на то, что элемент является оператором
    char c = static_cast<char>(element); // static_cast<char> для корректного чтения строки как оператора
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double calculation(double a, double b, double op) { // вспомогательная функция, которая вычисляет результат каждого оператора
    switch (static_cast<char>(op)) { // static_cast<char> для корректного чтения строки как оператора
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            cout << "Деление на 0 невозможно." << endl;
            return 0;
        }
        return a / b;
    default:
        cout << "Недопустимый оператор: " << static_cast<char>(op) << endl; // static_cast<char> для корректного чтения строки как оператора
        return 0;
    }
}


// Функции ввода данных
void inputFromConsole(Stack& stack) { // функция для ввода выражения с консоли
    cout << "Введите выражение в постфиксной записи: ";
    string line;
    getline(cin, line);
    cout << "Прочитанное выражение: " << line << endl;
    istringstream str(line);
    string element;
    while (str >> element) {
        if (isDouble(element)) {
            replace(element.begin(), element.end(), '.', ','); // для корректного чтения вещественных значений через '.'
            stack.push(stod(element));
        }
        else if (element.size() == 1 && isOperator(static_cast<double>(element[0]))) { // static_cast<char> для корректного чтения строки как оператора
            stack.push(static_cast<double>(element[0])); 
        }
        else {
            cout << "Пропущен недопустимый элемент: '" << element << "'\n";
        }
    }

}
void inputFromFile(Stack& stack) { // функция для ввода выражения из файла
    ifstream file("expression.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }
    string line;
    getline(file, line);
    cout << "Выражение из файла: " << line << endl;
    istringstream str(line);
    string element;
    while (str >> element) {
        if (isDouble(element)) {
            replace(element.begin(), element.end(), '.', ','); // для корректного чтения вещественных значений через '.'
            stack.push(stod(element));
        }
        else if (isOperator(static_cast<double>(element[0]))) { // static_cast<char> для корректного чтения строки как оператора
            stack.push(element[0]);
        }
        else {
            cout << "Недопустимый элемент '" << element << "' пропущен." << endl;
        }
    }
    file.close();
}

void inputFromRandom(Stack& stack) { // функция для ввода выражения случайными значениями
    int maxLength = 10;
    vector<string> operators = { "+", "-", "*", "/" };
    vector<string> expression;
    vector<int> operandCounts;
    srand(time(nullptr));
    int length = 2 + (rand() % (maxLength - 2));
    for (int i = 0; i < length; ++i) {
        bool add;
        if (operandCounts.empty()) {
            add = true;
        }
        else if (operandCounts.back() < 2) {
            add = true;
        }
        else {
            add = (rand() % 2 == 0) && (expression.size() < length - 1);
        }
        if (add) {
            double num = 0.1 + (rand() % 200) * 0.1; // 0.1-20.0
            ostringstream oss;
            oss << fixed << setprecision(1 + rand() % 1) << num;
            string numStr = oss.str();
            expression.push_back(numStr);
            if (!operandCounts.empty()) {
                operandCounts.back()++;
            }
            else {
                operandCounts.push_back(1);
            }
        }
        else {
            string op = operators[rand() % operators.size()];
            expression.push_back(op);

            if (!operandCounts.empty()) {
                operandCounts.back() -= 2;
                if (operandCounts.back() <= 0) {
                    operandCounts.pop_back();
                }
                if (!operandCounts.empty()) {
                    operandCounts.back()++;
                }
                else {
                    operandCounts.push_back(1);
                }
            }
        }
    }
    while (operandCounts.size() > 1 || (!operandCounts.empty() && operandCounts.back() > 1)) {
        string op = operators[rand() % operators.size()];
        expression.push_back(op);

        if (!operandCounts.empty()) {
            operandCounts.back() -= 2;
            if (operandCounts.back() <= 0) {
                operandCounts.pop_back();
            }
            if (!operandCounts.empty()) {
                operandCounts.back()++;
            }
            else {
                operandCounts.push_back(1);
            }
        }
    }
    string result;
    for (string element : expression) {
        result += element + " ";
        if (isDouble(element)) {
            replace(element.begin(), element.end(), '.', ','); // для корректного чтения вещественных значений через '.'
            stack.push(stod(element));
        }
        else if (isOperator(static_cast<double>(element[0]))) { // static_cast<char> для корректного чтения строки как оператора
            stack.push(element[0]);
        }
        else {
            cout << "Элемент '" << element << "' пропущен. ";
        }
    }
    cout << "Сгенерировано выражение: " << result << endl;
}
