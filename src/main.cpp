// ЮФУ, ИКТИБ, кафедра МОП ЭВМ
// Программирование и ОТА 2
// Индивидуальное задание 2
// Машина Тьюринга
// КТбо1-10 Пытков Роман Евгеньевич
// 07.05.2023

#include <iostream>
#include <string>
#include "turing_machine.h" //заголовок для машины
#include "direction.h"      //заголовок для перечисления направлений
#include "ansi_escapes.h"   //винда - не система

using namespace std;

// Функция
// Инициализирует переданную машину, занося таблицу действий
// вход: ссылка на переменную с машиной тьюринга
// выход: нет
// Изменяет переданное значение
void init_machine(turing_machine &tm)
{
    tm.add_action(1, '0', action{'0', direction::Left, 1});
    tm.add_action(1, '1', action{'1', direction::Left, 1});
    tm.add_action(1, '2', action{'2', direction::Left, 1});
    tm.add_action(1, '3', action{'3', direction::Left, 1});
    tm.add_action(1, '4', action{'4', direction::Left, 1});
    tm.add_action(1, '5', action{'5', direction::Left, 1});
    tm.add_action(1, '_', action{'#', direction::Right, 2});
    tm.add_action(2, '0', action{'0', direction::Right, 2});
    tm.add_action(2, '1', action{'1', direction::Right, 2});
    tm.add_action(2, '2', action{'2', direction::Right, 2});
    tm.add_action(2, '3', action{'3', direction::Right, 2});
    tm.add_action(2, '4', action{'4', direction::Right, 2});
    tm.add_action(2, '5', action{'5', direction::Right, 2});
    tm.add_action(2, '_', action{'_', direction::Left, 3});
    tm.add_action(3, '0', action{'5', direction::Left, 3});
    tm.add_action(3, '1', action{'0', direction::Left, 4});
    tm.add_action(3, '2', action{'1', direction::Left, 4});
    tm.add_action(3, '3', action{'2', direction::Left, 4});
    tm.add_action(3, '4', action{'3', direction::Left, 4});
    tm.add_action(3, '5', action{'4', direction::Left, 4});
    tm.add_action(3, '#', action{'#', direction::Right, 7});
    tm.add_action(4, '0', action{'0', direction::Left, 4});
    tm.add_action(4, '1', action{'1', direction::Left, 4});
    tm.add_action(4, '2', action{'2', direction::Left, 4});
    tm.add_action(4, '3', action{'3', direction::Left, 4});
    tm.add_action(4, '4', action{'4', direction::Left, 4});
    tm.add_action(4, '5', action{'5', direction::Left, 4});
    tm.add_action(4, '#', action{'#', direction::Left, 5});
    tm.add_action(5, '1', action{'1', direction::Left, 5});
    tm.add_action(5, '_', action{'1', direction::Right, 6});
    tm.add_action(6, '0', action{'0', direction::Right, 6});
    tm.add_action(6, '1', action{'1', direction::Right, 6});
    tm.add_action(6, '2', action{'2', direction::Right, 6});
    tm.add_action(6, '3', action{'3', direction::Right, 6});
    tm.add_action(6, '4', action{'4', direction::Right, 6});
    tm.add_action(6, '5', action{'5', direction::Right, 6});
    tm.add_action(6, '#', action{'#', direction::Right, 6});
    tm.add_action(6, '_', action{'_', direction::Left, 3});
    tm.add_action(7, '5', action{'0', direction::Right, 7});
    tm.add_action(7, '_', action{'_', direction::Left, 8});
    tm.add_action(8, '0', action{'0', direction::Left, 8});
    tm.add_action(8, '1', action{'1', direction::Left, 8});
    tm.add_action(8, '2', action{'2', direction::Left, 8});
    tm.add_action(8, '3', action{'3', direction::Left, 8});
    tm.add_action(8, '4', action{'4', direction::Left, 8});
    tm.add_action(8, '5', action{'5', direction::Left, 8});
    tm.add_action(8, 'a', action{'1', direction::Right, 9});
    tm.add_action(8, '#', action{'#', direction::Left, 8});
    tm.add_action(8, '_', action{'_', direction::Right, 9});
    tm.add_action(9, '1', action{'a', direction::Right, 10});
    tm.add_action(9, '#', action{'#', direction::Left, 12});
    tm.add_action(10, '0', action{'0', direction::Right, 10});
    tm.add_action(10, '1', action{'1', direction::Right, 10});
    tm.add_action(10, '2', action{'2', direction::Right, 10});
    tm.add_action(10, '3', action{'3', direction::Right, 10});
    tm.add_action(10, '4', action{'4', direction::Right, 10});
    tm.add_action(10, '5', action{'5', direction::Right, 10});
    tm.add_action(10, '#', action{'#', direction::Right, 10});
    tm.add_action(10, '_', action{'_', direction::Left, 11});
    tm.add_action(11, '0', action{'1', direction::Left, 8});
    tm.add_action(11, '1', action{'2', direction::Left, 8});
    tm.add_action(11, '2', action{'3', direction::Left, 8});
    tm.add_action(11, '3', action{'4', direction::Left, 8});
    tm.add_action(11, '4', action{'5', direction::Left, 8});
    tm.add_action(11, '5', action{'0', direction::Left, 11});
    tm.add_action(12, '1', action{'1', direction::Left, 12});
    tm.add_action(12, '_', action{'_', direction::Right, 0});
}

// Функция
// Проверяет переданную строку на соответсвие алфвавиту [0;5]
// вход: константная ссылка на строку
// выход: булево значение (true = valid)
bool is_valid_input(const string &str)
{
    for (char ch : str)
        if (ch < '0' || ch > '5')
            return false;
    return true;
}

// Функция
// Точка входа. Выводит информацию, создаёт Машину Тьюринга и управляет вводом.
// вход: нет
// выход: код возврата программы
int main()
{
    setupConsole();
    cout << "This Turing Machine converts numbers from the 6-digit number system to unary form, writing the result to the left of the original word through #." << endl;
    cout << "Valid input alphabet: { 0, 1, 2, 3, 4, 5 }" << endl;
    cout << "Technical alphabet: { #, a }" << endl;
    cout << "Output alphabet: { 0, 1, 2, 3, 4, 5, # }" << endl;
    cout << "Author: Pytkov Roman Evgenievich, KTbo1-10" << endl;
    string str;
    turing_machine tm;
    init_machine(tm);
    while (true)
    {
        cout << "Enter a word in the allowed alphabet (or exit): ";
        cin >> str;
        if (str == "exit")
            break;
        if (!is_valid_input(str))
        {
            cout << "The entered word does not match the input alphabet, please try again." << endl;
            continue;
        }
        band b(str, '_');
        b.right();
        string msg;
        if (tm.work(b, msg))
            cout << "Result: " << b << endl;
        cout << "Message from Turing Machine:" << endl
             << msg << endl
             << endl;
    }
    cout << "The End." << endl;
    restoreConsole();
    return 0;
}