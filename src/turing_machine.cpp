#include "turing_machine.h"
#include "color.h"
#include <iomanip>

using namespace std;

turing_machine::turing_machine() : _table(1) {}

void turing_machine::add_action(int state, char ch, action act)
{
    while (_table.size() <= state) // увеличиваем размер таблицы, пока станет достаточно для нового состояния
        _table.push_back(map<char, action>());

    _table[state][ch] = act;
}

Color::Modifier f_blue(Color::FG_BLUE);
Color::Modifier f_green(Color::FG_GREEN);
Color::Modifier f_red(Color::FG_RED);
Color::Modifier f_def(Color::FG_DEFAULT);
std::ostream &operator<<(std::ostream &os, action a) // вывод действия для удобства
{
    os <<'('<< f_red<<"\'" << a.sym << "\'" << f_def << ", " <<setw(5) << std::left << (a.dir == -1 ? "left" : (a.dir == 1 ? "right" : "none")) << ", " << f_blue << "Q"<<setw(2)<<std::left<< a.next_state <<f_def<< ")";
    return os;
}

void turing_machine::print_info(int state, const band &b) const
{
    cout <<f_green<< b.to_string_before() << f_red << b.get() <<f_green<<b.to_string_after()<<f_def;
    cout << f_blue << "\tQ" << state << f_def;
    if (state <= _table.size() && _table[state].count(b.get())) // вывод действия, если оно есть
        cout << "\t\t(" << f_blue << "Q" <<setw(2)<<std::left<< state << f_def << "; " 
        << f_red << "\'" << b.get() << '\'' << f_def << "): "<< _table[state].at(b.get());
    cout << endl;
}

void turing_machine::step(int &cur_state, band &b) const
{
    // если состояние превышает доступные или если не задано действие, то состояние ошибки
    if (cur_state > _table.size() || _table[cur_state].count(b.get()) == 0)
    {
        cur_state = -1;
        return;
    }

    action act = _table[cur_state].at(b.get());
    b.set(act.sym);

    switch (act.dir)
    {
    case direction::Left:
        b.left();
        break;
    case direction::Right:
        b.right();
        break;
    default:
        break;
    }

    cur_state = act.next_state;
}

bool turing_machine::work(band &b, string &msg) const
{
    int cur_state = 1;
    while (cur_state > 0)
    {
        print_info(cur_state, b);
        step(cur_state, b);
    }
    print_info(cur_state, b);

    if (cur_state == 0)
    {
        msg = "Succes!";
        return true;
    }
    else
    {
        msg = "Error at runtime. Perhaps there are not enough actions in the table or the word does not match the format.";
        return false;
    }
}