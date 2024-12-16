#ifndef PLAYER_H 
#define PLAYER_H

#include "abstract_player.h"

// класс представления игрока в игре
class Player : public AbstractPlayer {
public:
    Player(int field_size, int ships_count, const std::vector<int>& sizes);                        // конструктор, принимающий размер поля, количество кораблей и их размеры
    bool place_ships() override;                                                                   // метод размещения кораблей
    bool make_shot(AbstractPlayer& opponent, std::optional<std::pair<char, int>> coords) override; // метод выстрела по противнику

private:
    ConsoleIO console;                                                                             // объект для работы с консольным вводом/выводом
};

#endif 
