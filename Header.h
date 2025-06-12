#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cctype>
#include <fstream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <windows.h>
using namespace std;

class Stack {
private:
    vector<double> elem;

public:
    // Основные методы стека
    void push(double num); // добавление элемента в стек
    double pop(); // извлечение последнего элемента стека
    bool isEmpty(); // проверка стека на пустоту
    int getSize(); // размер стека
    void clear(); // очищение стека
};

// Функции проверки ввода
bool isInt(const string& str); // проверка на содержание недопустимого ввода в int значениях
bool isDouble(const string& str); // проверка на содержание недопустимого ввода в double значениях

// Функции для работы с выражением
double calculateExpression(Stack& stack); // функция для вычисления всего выражения
bool isOperator(double token); // проверка на то, что элемент является оператором
double calculation(double a, double b, double op); // вспомогательная функция, которая вычисляет результат каждого оператора

// Функции ввода данных
void inputFromConsole(Stack& stack); // функция для ввода выражения с консоли
void inputFromFile(Stack& stack); // функция для ввода выражения из файла
void inputFromRandom(Stack& stack); // функция для ввода выражения случайными значениями
