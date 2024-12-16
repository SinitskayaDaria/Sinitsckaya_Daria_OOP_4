#ifndef SHIPMANAGER_H 
#define SHIPMANAGER_H

#include <vector> 
#include <iostream>

#include "ship.h" 
#include "console_io.h"

class ShipManager {
public:
    ShipManager();                                   // конструктор по умолчанию
    ShipManager(int count, std::vector<int> sizes);  // конструктор, принимающий количество кораблей и их размеры
    std::vector<Ship>& get_ships();                  // метод получения ссылки на массив кораблей
    Segment* find_segment_by_id(int id);             // метод нахождения сегмента по ID
    bool check_ships();                              // метод обновления состояния кораблей
    bool is_all_ships_destroyed();                   // метод проверки уничтожения всех кораблей
    void serialize(std::ostream& os);                // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);              // метод преобразования данных состояния игровой сессии из потока ввода

private:
    int destroyed_ships;      // счетчик уничтоженных кораблей
    std::vector<Ship> ships;  // массив всех кораблей
    ConsoleIO console;        // объект для работы с консолью
};

#endif 
