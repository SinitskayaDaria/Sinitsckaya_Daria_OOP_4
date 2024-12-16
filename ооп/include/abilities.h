#ifndef ABILITIES_H
#define ABILITIES_H

#include <optional>
#include <random>
#include <memory>

#include "board.h"
#include "ship_manager.h"
#include "abstract_player.h" 

// класс способностей
class Ability {
public:
    virtual void use() = 0;                 // метод использования способностей
    virtual std::string get_name() = 0;     // функция возвращающая имя способности
};

#endif