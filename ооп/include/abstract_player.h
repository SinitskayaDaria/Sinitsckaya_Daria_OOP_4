#ifndef ABSTRACTPLAYER_H 
#define ABSTRACTPLAYER_H

#include <optional>

#include "ship_manager.h"    
#include "console_io.h"  
#include "board.h"        

// абстрактный класс представления игрока в игре
class AbstractPlayer {
public:
    AbstractPlayer(int field_size, int ships_count, const std::vector<int>& sizes);                                   // конструктор класса, инициализирующий игровое поле и менеджер кораблей
    virtual bool place_ships() = 0;                                                                                   // виртуальная функция размещения кораблей
    virtual bool make_shot(AbstractPlayer& opponent, std::optional<std::pair<char, int>> coords = std::nullopt) = 0;  // виртуальная функция выстрела по противнику
    virtual bool update();                                                                                            // виртуальная функция обновления состояния игрока
    virtual int get_damage();                                                                                         // метод получения значения урона игрока
    virtual void set_damage(int dmg);                                                                                 // метод установки значения урона игрока
    virtual Board& get_board();                                                                                       // виртуальный метод получения ссылки на игровое поле
    virtual ShipManager& get_ship_manager();                                                                          // виртуальный метод получения ссылки на менеджер кораблей игрока
    virtual bool is_lose();                                                                                           // виртуальная функция проверки проигрыша игрока
    void serialize(std::ostream& os);                                                                                 // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);                                                                               // метод преобразования данных состояния игровой сессии из потока ввода

protected:
    int damage;                  // урон
    Board board;                 // игровое поле игрока
    ShipManager ship_manager;    // менеджер кораблей игрока
};

#endif
