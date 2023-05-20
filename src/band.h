#pragma once
#include <iostream>
#include <string>
#include "node.h"

// Объявление класса ленты. Все реализации в band.cpp
class band
{
private:
    node *_cur;   // текущая позиция
    node *_start; // самая левая
    node *_end;   // самая правая

    void write_str_from_next(std::string str);

public:
    char default_sym; // символ по умолчанию для расширения ленты

    band();                        // конструктор без параметров
    band(char sym);                // конструктор с символом по умолчанию
    band(std::string s, char sym); // конструктор из строки и символа по умолчанию
    ~band();                       // Деструктор. Уничтожает все узлы связного списка


    // Функция
    // Возвращает всю ленту в виде строки
    // вход: нет
    // выход: строка
    // Не изменят поля класса
    std::string to_string() const;

    // Функция
    // Возвращает ленту слева от головки в виде строки
    // вход: нет
    // выход: строка
    // Не изменят поля класса
    std::string to_string_before() const;

    // Функция
    // Возвращает ленту справа от головки в виде строки (с текущим символом)
    // вход: нет
    // выход: строка
    // Не изменят поля класса
    std::string to_string_after_and_cur() const;

    // Функция
    // Возвращает ленту справа от головки в виде строки (без текущего символа)
    // вход: нет
    // выход: строка
    // Не изменят поля класса
    std::string to_string_after() const;

    // Функция
    // Возвращает символ под головкой
    // вход: нет
    // выход: символ
    // Не изменят поля класса
    char get() const;

    // Функция
    // Устанавливает символ под головкой
    // вход: символ
    // выход: нет
    void set(char ch);

    // Функция
    // Сдвигает головку влево на один символ
    // вход: нет
    // выход: нет
    void left();

    // Функция
    // Сдвигает головку вправо на один символ
    // вход: нет
    // выход: нет
    void right();

    // Функция
    // Сдвигает головку на самый левый символ
    // вход: нет
    // выход: нет
    void to_start();

    // Функция
    // Сдвигает головку на самый правый символ
    // вход: нет
    // выход: нет
    void to_end();

    // Оператор
    // перегруженный оператор вывода в поток для удобства
    friend std::ostream &operator<<(std::ostream &os, band &dt);
};