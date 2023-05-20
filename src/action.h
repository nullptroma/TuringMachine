#pragma once
#include "direction.h"

// Структура одной клетки в Эмуляторе Полякова. Новый символ, движение, новое состояние
struct action
{
    char sym;
    direction dir;
    int next_state;
};