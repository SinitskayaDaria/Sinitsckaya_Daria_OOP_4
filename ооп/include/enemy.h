#ifndef ENEMY_H 
#define ENEMY_H

#include "abstract_player.h" 

#include <random>       

// класс противника
class Enemy : public AbstractPlayer {
public:
    Enemy(int field_size, int ships_count, const std::vector<int>& sizes);                          // конструктор, принимающий размер поля, количество кораблей и массив размеров кораблей
    bool place_ships() override;                                                                    // метод размещения кораблей противника
    bool make_shot(AbstractPlayer& opponent, std::optional<std::pair<char, int>> coords) override;  // метод выстрела противника по игроку

private:
    std::uniform_int_distribution<> orient_range; // генератор случайных числе для выбора ориентации корабля
    std::uniform_int_distribution<> letter_range; // генератор случайных чисел для выбора буквы (столбца) на поле
    std::uniform_int_distribution<> digit_range;  // генератор случайных чисел для выбора цифры (строки) на поле
};

#endif 
