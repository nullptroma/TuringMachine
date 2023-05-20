#include "band.h"

using namespace std;

band::band() : band('_') {}
band::band(char default_sym) : band("", default_sym) {}
band::band(string str, char sym)
{
    default_sym = sym;

    _cur = new node{default_sym};
    _start = _cur;
    _end = _cur;
    write_str_from_next(str); // записать слово
    to_start();               // вернуться на начало
}

band::~band()
{
    while (_start)
    {
        node *p = _start->right;
        delete _start;
        _start = p;
    }
    _cur = _start = _end = nullptr;
}

void band::write_str_from_next(string str)
{
    for (char ch : str)
    {
        right();
        set(ch);
    }
}

string band::to_string() const
{
    string str;
    node *start = _start;
    while (start)
    {
        str += start->val;
        start = start->right;
    }
    return str;
}

string band::to_string_before() const
{
    string res;
    node *start = _start;
    while (start != _cur)
    {
        res += start->val;
        start = start->right;
    }
    return res;
}

string band::to_string_after_and_cur() const
{
    string res;
    node *start = _cur;
    while (start)
    {
        res += start->val;
        start = start->right;
    }
    return res;
}

string band::to_string_after() const
{
    string res;
    node *start = _cur->right;
    while (start)
    {
        res += start->val;
        start = start->right;
    }
    return res;
}

char band::get() const
{
    return _cur->val;
}

void band::set(char ch)
{
    _cur->val = ch;
    if (ch != default_sym)
    {
        left();
        right();
        right();
        left();
    }
}

void band::left()
{
    if (_cur->left == nullptr) // расширение влево
    {
        node *n = new node{default_sym};
        _start = n;

        _cur->left = n;
        n->right = _cur;

        _cur = _cur->left;
    }
    else
        _cur = _cur->left;
}

void band::right()
{
    if (_cur->right == nullptr) // расширение вправо
    {
        node *n = new node{default_sym};
        _end = n;

        _cur->right = n;
        n->left = _cur;

        _cur = _cur->right;
    }
    else
        _cur = _cur->right;
}

void band::to_start()
{
    _cur = _start;
}

void band::to_end()
{
    _cur = _end;
}

std::ostream &operator<<(std::ostream &os, band &b)
{
    os << "[";
    os << b.to_string();
    os << ']';
    return os;
}